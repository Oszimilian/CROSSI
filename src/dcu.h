#ifndef CAN_RECIEVE_H
#define CAN_RECEIVE_H

#include <string>
#include <vector>
#include <map>
#include <mutex>
#include <thread>
#include <functional>
#include "ring.h"

#include <net/if.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#include <condition_variable>

#include <linux/can.h>
#include <linux/can/raw.h>



#define SIGNLE_THREAD_CAPTURE "Single_Thread"
#define MULTI_THREAD_CAPTURE "Multi_Thread"
#define ASYNC_THREAD "Async_Thread"


#include "list.h"
#include "config.h"

namespace dcu
{
    
    class CAN;
    class DBC_Decode;

    class DCU_Handler : public Config
    {
        private:


            std::map<int, dcu::CAN*> capture_instance;
            std::map<int, dcu::DBC_Decode*> decode_instance;

            std::map<int, std::thread*> capture_thread;
            std::map<int, std::thread*> decode_thread;

            std::map<int, std::function<void(dcu::DCU_Handler*)>> capture_callback;
            std::map<int, std::function<void(dcu::DCU_Handler*)>> decode_callback;

            std::vector<int> multithread_caputre_list;
            std::vector<int> singlethread_caputre_list;

            std::vector<int> multithread_decode_list;
            std::vector<int> singlethread_decode_list;
            
            std::vector<ring<struct can_frame> *> capture_decode_ring;

            std::vector<std::condition_variable*> cv;
            std::vector<std::mutex*> emtx;

    
            void handler_init_capture_instance();
            void handler_init_decode_instance();

            void handler_init_capure_callback();
            void handler_init_decode_callback();

            void handler_init_caputre_thread();
            void handler_init_decode_thread();

            void handler_join_caputre_thread();
            void handler_join_decode_thread();

            void handler_close_capture_thread();
            void handler_close_decode_thread();

            void handler_init_lock_thread();

            void handler_init_caputre_decode_ring();
    
        public:

            DCU_Handler(int argc, char **argv);
            ~DCU_Handler();

            void handler_start_cros();

            


    };
}


#endif

