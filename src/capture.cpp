#include <string>
#include <vector>
#include <iostream>

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

#include <condition_variable>
#include <mutex>

#include "capture.h"
#include "dcu.h"

#include "ring.h"



dcu::CAN::CAN(std::string name, ring<struct can_frame> *caputre_decode_ring) 
            : can_socket_name(name), caputre_decode_ring(caputre_decode_ring)
{
    

    can_open_socket();
    can_init_io();
    can_init_socket_address();
    can_adress_socket();
    can_disable_block_read();

    can_print_socket_info();

    this->new_node = true;
}

dcu::CAN::~CAN()
{
    if (close(this->can_socket_id) < 0) 
    {
        perror("Close");
        exit(-1);
    }
}

void dcu::CAN::can_print_socket_info()
{
    std::cout << "\t Setup Socket: "<< std::endl;
    std::cout << "+-->ID: " << this->can_socket_id << std::endl;
    std::cout << "+-->Name: " << this->can_socket_name << std::endl;
    std::cout << std::endl;
}

void dcu::CAN::can_open_socket()
{
    this->can_socket_id = socket(PF_CAN, SOCK_RAW, CAN_RAW);

    if (this->can_socket_id < 0)
    {
        std::cerr << "ERROR in opening a Socket! Socket_ID: " << this->can_socket_id << std::endl;
        exit(-1); 
    }
}

void dcu::CAN::can_init_io()
{
    strcpy(this->ifr.ifr_name, this->can_socket_name.c_str());

    if (ioctl(this->can_socket_id, SIOCGIFINDEX, &this->ifr) == -1)
    {
        std::cerr << "ERROR in initialicing the IO" << std::endl;
    }
}


void dcu::CAN::can_init_socket_address()
{
    memset(&this->can_addresse, 0, sizeof(can_addresse));
    can_addresse.can_family = AF_CAN;
    can_addresse.can_ifindex = this->ifr.ifr_ifindex;

}

void dcu::CAN::can_adress_socket()
{
    if (bind(this->can_socket_id, ((struct sockaddr*)(&this->can_addresse)), sizeof(can_addresse)) <  0)
    {
        std::cerr << "ERROR in bind the socket" << std::endl;
        exit(-1);
    }
}


void dcu::CAN::can_disable_block_read()
{
    fcntl(this->can_socket_id, F_SETFL, fcntl(this->can_socket_id, F_GETFL, 0) | O_NONBLOCK);
}




void dcu::CAN::start_singlethread_recieve()
{
    int nbytes;

    if (new_node == true)
    {
        this->ring_node = this->caputre_decode_ring->get_new_node();
        this->new_node = false;
    }

    nbytes = read(this->can_socket_id, this->ring_node->payload, sizeof(struct can_frame));

    if (nbytes > 0)
    {
        this->ring_node->socket_name = can_socket_name;
        this->caputre_decode_ring->push_node(this->ring_node);
        this->new_node = true;
    }
}


 






