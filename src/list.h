#ifndef CAN_MESSAGE_H
#define CAN_MESSAGE_H


#include <mutex>
#include <net/if.h>
#include <sys/ioctl.h>
#include <sys/socket.h>

#include <net/if.h>
#include <sys/ioctl.h>
#include <sys/socket.h>

#include <linux/can.h>
#include <linux/can/raw.h>

#define MAX_SOCKET_NAME_LEANGH 32
#define MSG_BUFFER_LEANGH 32

namespace dcu
{
    class DCU_Handler;

    class Msg_List
    {
        private:

            /**
             * @brief Listen-Element-Struktur
             * 
             * -# *frame = Pointer auf das CAN-Empfangspacket
             * -# *next = Pointer auf das nächste Listen-Element
             * -# *prev = Pointer auf das vorrandgegangene Listen-Element
             * -# socket_name = Name des CAN-Sockets von dem die CAN-Nachricht kommt
            */
            struct Node
            {
                struct can_frame *frame;
                struct Node *next;
                struct Node *prev;
                char socket_name[MAX_SOCKET_NAME_LEANGH];
            };

            /**
             * @brief Liste die CAN-Messages an den Message-Filter transportiert
             * 
             * -# *head = Pointer auf den Kopf der Liste
             * -# *tail = Pointer auf den "Tail" der Liste
             * -# leangh = Länge der liste
            */ 
            struct List
            {
                struct Node *head;
                struct Node *tail;
                int leangh;
            };

            /**
             * @brief Backup Liste
            */
            struct List *backup;

            /**
             * @brief Can-Frame auf den Stack zum Initialsieren von Buffer-Listen-Elemente
            */
            struct can_frame local_frame;
            
            /**
             *  @brief MUTEX
            */
            std::mutex mtx;

            
            struct List *list_create();
            void list_setup(struct List *list);
            bool list_check_error(void *element);
            struct Node *list_create_Node();
            
            struct can_frame *list_create_Can_Frame();
            void list_delete_node(struct Node *node);

            friend class DBC_Decode;

        public:

            /**
             * @brief Liste für CAN-Messages
            */
            struct List *can_msg; 

            /**
             * @brief Liste für alte ListenElemente die bei der nächsten CAN-Message wiederverwendet werden können
            */
            struct List *buf_msg;

            Msg_List();

            bool list_append(struct List *list, struct Node *node, struct can_frame *frame_ptr, const char *socket_name);
            struct Node *list_pop_last_element(struct List *list);
            void list_revert_node(struct List *list, struct Node *node);
            void list_print_node(struct Node *node);
            void list_print(struct List *list);

            struct can_frame *list_get_can_frame();

            bool list_insert_head(struct List *list, struct Node *node);
            struct Node *list_pick_Node();
    };
}





#endif