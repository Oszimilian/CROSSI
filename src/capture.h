#ifndef DCU_CAN_H
#define DCU_CAN_H

#include <string>
#include <net/if.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#include <linux/can.h>
#include <linux/can/raw.h>

#include "ring.h"




namespace dcu
{
    class DCU_Handler;

    class CAN
    {
        private:
            /**
             * @brief Name des Sockets
            */
            std::string can_socket_name;



            /**
             *  @brief Socket-Adress-Structur für CAN
            */
            struct sockaddr_can can_addresse;

            /**
             * @brief Interface-Request-Struktur
            */
            struct ifreq ifr;

            /**
             * @brief Standart CAN-Frame
            */
            struct can_frame frame;

            /**
             * Pointer auf das Receive-Handler-Objekt
            */
            DCU_Handler *handler;

            bool new_node;

            ring<can_frame>::Node *ring_node;

            ring<struct can_frame> *caputre_decode_ring;

            void can_open_socket();
            void can_init_io();
            void can_init_socket_address();
            void can_adress_socket();
            void can_disable_block_read();
            void can_print_socket_info();

        public:
            CAN(std::string name, DCU_Handler *handler, ring<struct can_frame> *caputre_decode_ring);
            ~CAN();

            void start_multithread_receive();
            void start_singlethread_recieve();

            /**
             * @brief ID des Sockets
            */
            int can_socket_id;
            
            

    };
}



#endif