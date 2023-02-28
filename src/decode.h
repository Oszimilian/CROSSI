#ifndef DECODE_DBC_H
#define DECODE_DBC_H

#include <string>
#include <memory>
#include <dbcppp/Network.h>



namespace dcu
{
    class DCU_Handler;

    class DBC_Decode
    {
        private:
            std::string dbc_path;
            std::ifstream *dbc_stream;
            std::unique_ptr<dbcppp::INetwork> net;
            std::unordered_map<uint64_t, const dbcppp::IMessage*> dbc_msg;
            DCU_Handler *handler;
            std::string socket_name;

            //std::vector<ring<struct can_frame> *> capture_decode_ring;


            ring<can_frame>::Node *ring_node;
            ring<struct can_frame> *caputre_decode_ring;
            struct can_frame *frame;


            template<typename pointer_input> 
            void dbc_handle_error(pointer_input *input);

        public:
            DBC_Decode(std::string dbc_path, std::string socket_name, ring<struct can_frame> *caputre_decode_ring);
            int dbc_decode_msg();    

            void print_can_frame(const char *socket_name, struct can_frame *frame);

    };
}



#endif