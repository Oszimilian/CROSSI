#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <thread>
#include <mutex>
#include <regex>
#include <string.h>

#include <fstream>
#include <dbcppp/Network.h>

#include "dcu.h"
#include "decode.h"
#include "list.h"
#include "ring.h"

#include "crossiPublisher.h"

using namespace dcu;


dcu::DBC_Decode::DBC_Decode(std::string dbc_path, std::string socket_name, ring<struct can_frame> *caputre_decode_ring) 
                    : dbc_path(dbc_path), socket_name(socket_name), caputre_decode_ring(caputre_decode_ring)
{
    
    dbc_stream = new std::ifstream(this->dbc_path);
    net = dbcppp::INetwork::LoadDBCFromIs(*dbc_stream);  
    dbc_handle_error(net.get());
    for (const dbcppp::IMessage &msg : net->Messages())
    {
        dbc_msg.insert(std::make_pair(msg.Id(), &msg));
    }

    std::cout << "DBC_Decode started with Channel: \t" << socket_name << " \t\t DBC_Decode_Path: " << dbc_path << std::endl << std::endl;
}

template<typename pointer_input> 
void dcu::DBC_Decode::dbc_handle_error(pointer_input *input)
{
    if (input == nullptr)
    {
        std::cerr << "Error in DBC_Decode" << std::endl;
        exit(-1);
    }
}

int dcu::DBC_Decode::dbc_decode_msg()
{

    

    this->ring_node = this->caputre_decode_ring->pop_node();



    if (this->ring_node)
    {
        

        frame = this->ring_node->payload;

            
            print_can_frame(this->socket_name.c_str(), frame);

            auto itterator = this->dbc_msg.find(frame->can_id);


            if (itterator != dbc_msg.end())
            {
                this->can_decoded_msg.clear();

                const dbcppp::IMessage *msg = itterator->second;
                std::cout << "Received Message: " << msg->Name() << std::endl;

                for (const dbcppp::ISignal &sig : msg->Signals())
                {
                    const dbcppp::ISignal *mux_sig = msg->MuxSignal();
                        if (sig.MultiplexerIndicator() != dbcppp::ISignal::EMultiplexer::MuxValue ||
                        (mux_sig && mux_sig->Decode(frame->data) == sig.MultiplexerSwitchValue()))
                        {
                            std::cout << sig.Name() << " = " << sig.RawToPhys(sig.Decode(frame->data)) << sig.Unit() << std::endl;

                            this->can_decoded_msg.push_back(static_cast<float>(sig.RawToPhys(sig.Decode(frame->data))));
                        }
                }

                std::string msg_name = msg->Name();

                ros_msg_functions[msg->Name()](&msg_name, &this->can_decoded_msg, get_Crossi_Publisher_ptr());

                this->caputre_decode_ring->reuse_node(ring_node);

                return true;
            } else {
                return false;
            }
        
    }

    return false;

}

void dcu::DBC_Decode::print_can_frame(const char *socket_name, can_frame *frame)
{
    if (frame != nullptr)
    {
        printf("%s: 0x%03X [%d] ", socket_name, frame->can_id, frame->can_dlc);
        for (int i = 0; i < CAN_MAX_DLEN; i++)
        {
            printf("%02X ", frame->data[i]);
        }
        printf("\n");
    }
}


