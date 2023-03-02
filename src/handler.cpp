#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <thread>
#include <mutex>
#include <regex>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#include <net/if.h>
#include <sys/ioctl.h>
#include <sys/socket.h>

#include <linux/can.h>
#include <linux/can/raw.h>


#include <fstream>
#include <dbcppp/Network.h>

#include <condition_variable>


#include "dcu.h"
#include "capture.h"
#include "list.h"
#include "decode.h"
#include "ring.h"
#include "msggen.h"



dcu::DCU_Handler::DCU_Handler(int argc, char **argv) :  Config(argc, argv), Msggen(this)
{
    handler_init_caputre_decode_ring();

    handler_init_lock_thread();

    handler_init_capture_instance();
    handler_init_decode_instance();

    handler_init_capure_callback();
    handler_init_decode_callback();



}


dcu::DCU_Handler::~DCU_Handler()
{
   
    handler_close_capture_thread();
    handler_close_decode_thread();
}

void dcu::DCU_Handler::handler_start_cros()
{
    handler_init_caputre_thread();
    handler_init_decode_thread();

    handler_join_caputre_thread();
    handler_join_decode_thread();
}



void dcu::DCU_Handler::handler_init_capture_instance()
{
    for (int i = 0; i < config_get_can_count(); i++)
    {
        this->capture_instance.insert(std::make_pair(i, new CAN(config_get_socketname(i), this->capture_decode_ring[i])));
    }
}

void dcu::DCU_Handler::handler_init_decode_instance()
{
    for (int i = 0; i < config_get_can_count(); i++)
    {
        this->decode_instance.insert(std::make_pair(i, new DBC_Decode(config_get_dbc_path(i), config_get_socketname(i), this->capture_decode_ring[i])));
    }
}

void dcu::DCU_Handler::handler_init_capure_callback()
{
    int i = 0;

    for (i = 0; i <  config_get_can_count(); i++)
    {
        if (config_get_capture_mode(i) == MULTI_THREAD_CAPTURE)
        {
            this->multithread_caputre_list.push_back(i);
        } 
        else if (config_get_capture_mode(i) == SIGNLE_THREAD_CAPTURE)
        {
            this->singlethread_caputre_list.push_back(i);
        }
    }

    for (i = 0; i < multithread_caputre_list.size(); i++)
    {
        if (config_get_capture_mode(i) == MULTI_THREAD_CAPTURE)
        {
            this->capture_callback.insert(std::make_pair(i, [this, i](dcu::DCU_Handler *handler) {

                while(true)
                {
                    this->capture_instance[i]->start_singlethread_recieve();

                    if(this->capture_decode_ring.at(i)->get_size() != 0)
                    {
                        
                        {
                            std::lock_guard<std::mutex> lock(*(this->emtx.at(i)));
                        }

                        this->cv.at(i)->notify_one();
                    } 

                }
            }));
        }
    }

    if (singlethread_caputre_list.size() > 0)
    {
        this->capture_callback.insert(std::make_pair(multithread_caputre_list.size(), [this, i](dcu::DCU_Handler *handler) {
            while(true)
            {
                for (int i = 0; i <  this->singlethread_caputre_list.size(); i++)
                {
                    this->capture_instance[i]->start_singlethread_recieve();
                }

                if(this->capture_decode_ring.at(i)->get_size() != 0)
                {
                    {
                        std::lock_guard<std::mutex> lock(*(this->emtx.at(i)));
                    }

                    this->cv.at(i)->notify_one();
                } 
            }
        }));
    }
}

void dcu::DCU_Handler::handler_init_decode_callback()
{
    int i = 0;

    for (i = 0; i <  config_get_can_count(); i++)
    {
        if (config_get_decode_mode(i) == MULTI_THREAD_CAPTURE)
        {
            this->multithread_decode_list.push_back(i);
        } 
        else if (config_get_decode_mode(i) == SIGNLE_THREAD_CAPTURE)
        {
            this->singlethread_decode_list.push_back(i);
        }
    }

    for (i = 0; i < multithread_decode_list.size(); i++)
    {
        if (config_get_decode_mode(i) == MULTI_THREAD_CAPTURE)
        {
            this->decode_callback.insert(std::make_pair(i, [this, i](dcu::DCU_Handler *handler) {

                while (true)
                {
                    std::unique_lock<std::mutex> lock(*(emtx.at(i)));

                    cv.at(i)->wait(lock);

                    this->decode_instance[this->multithread_decode_list[i]]->dbc_decode_msg();
                    
                }
            }));
        }
    }

    if (singlethread_decode_list.size() > 0)
    {
        this->decode_callback.insert(std::make_pair(multithread_decode_list.size(), [this, i](dcu::DCU_Handler *handler) {
  
            while(true)
            {
                std::unique_lock<std::mutex> lock(*(emtx.at(i)));

                cv.at(i)->wait(lock);

                for (auto &i : this->singlethread_decode_list)
                {
                    this->decode_instance[i]->dbc_decode_msg();
                }

            }
        }));

    }
}

void dcu::DCU_Handler::handler_init_caputre_thread()
{
    for (int i = 0; i < capture_callback.size(); i++)
    {
        this->capture_thread.insert(std::make_pair(i, new std::thread(capture_callback.at(i), this)));
        std::cout << "-> Capture Thread Started: " << i << std::endl;
    }
}

void dcu::DCU_Handler::handler_init_decode_thread()
{
    for (int i = 0; i <  decode_callback.size(); i++)
    {
        this->decode_thread.insert(std::make_pair(i, new std::thread(decode_callback.at(i), this)));
        std::cout << "-> Decode Thread Started: " << i << std::endl;
    }
}

void dcu::DCU_Handler::handler_join_caputre_thread()
{
    for (auto &i : capture_thread)
    {
        i.second->join();
    }
}

void dcu::DCU_Handler::handler_join_decode_thread()
{
    for (auto &i : decode_thread)
    {
        i.second->join();
    }
}

void dcu::DCU_Handler::handler_close_capture_thread()
{
    for (auto &i : capture_thread)
    {
        delete i.second;
    }
}

void dcu::DCU_Handler::handler_close_decode_thread()
{
    for (auto &i : decode_thread)
    {
        delete i.second;
    }
}

void dcu::DCU_Handler::handler_init_caputre_decode_ring()
{
    std::cout << "\t SETUP RING:" << std::endl;
    for (int i = 0; i < config_get_can_count(); i++)
    {
        this->capture_decode_ring.push_back(new ring<struct can_frame>(30));
        std::cout << "-> Caputre_Docode_Ring Started: " << i << std::endl;
    }
    std::cout << std::endl;
}

void dcu::DCU_Handler::handler_init_lock_thread()
{
    for (int i = 0; i < config_get_can_count(); i++)
    {
        cv.push_back(new std::condition_variable);
        emtx.push_back(new std::mutex);
    }
}
