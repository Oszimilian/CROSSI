#include <mutex>
#include <vector>
#include <iostream>
#include <thread>
#include <chrono>


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

#include "list.h"


using namespace dcu;

/**
 * @brief Konstruktor der CAN_Message_List
 * 
 * -# Erzeugen von einer CAN-Message und einer Buffer-Message(Strukturwiderverwertung) Liste
 * -# Die CAN-Message-List wird mit MSG_BUFFER_LEANGH vielen Listen-Elementen gefüllt
 * -# Der "volle" Inhalt der CAN-Message-List wird mit dem "leeren" Inhalt der Buffer-Message-List getauscht.
 *    Dadurch entsteht ein Vorrat an Listenelementen die nichtmehr zur Laufzeit auf dem Heap dynamisch vom OS erzeugt werden müssen
*/
dcu::Msg_List::Msg_List()
{
    this->can_msg = list_create();
    this->buf_msg = list_create();
    list_setup(this->can_msg);
    list_setup(this->buf_msg);

    for (int i = 0; i < MSG_BUFFER_LEANGH; i++)
    {
        list_append(this->can_msg, list_pick_Node(), &this->local_frame, "buffer");
    }

    this->backup = this->can_msg;
    this->can_msg = this->buf_msg;
    this->buf_msg = this->backup;
    
}

/**
 * @brief Setup der Liste
 * 
 * -# Initialisierung des Head und Tail pointer auf NULL
 * -# Setzen der default Start-Länge = 0
*/
void dcu::Msg_List::list_setup(Msg_List::List *list)
{
    list->head = nullptr;
    list->tail = nullptr;
    list->leangh = 0;
}

/**
 * @brief Liste Erzeugen
 * @return Pointer auf die erzeugte Listenstruktur
 * 
 * -# Listenstruktur wird dynamisch auf dem Heap erzeugt
 * -# Pointer auf diese Listenstruktur wird zurückgegeben
*/
dcu::Msg_List::List *dcu::Msg_List::list_create()
{
    struct List *list = (struct List*) malloc(sizeof(struct List));
    return(list_check_error(list)) ? nullptr : list;
}

/**
 * @brief Errorhändling funktion
 * @param element void Pointer eines Elements
 * @return boolean (abhängig ob element* gleich NULL oder nicht)
 * 
 * -# Funktion überprüft ob der übergebenen Pointer gleich NULL ist
*/
bool dcu::Msg_List::list_check_error(void *element)
{
    if (element == nullptr)
    {
        std::cerr << "Error in List_Can_Message" << std::endl;
        return true;
    } else {
        return false;
    }
}

/**
 * @brief Node (Daten-Element) erzeugen
 * @return Pointer auf die erzeugte Node-Struktur
 * 
 * -# Die Funktion erzeugt ein Node-Struktur auf dem Heap und gibt den Pointer auf diese Struktur zurück
*/
//dcu::Node *dcu::Msg_List::list_create_Node()
dcu::Msg_List::Node *dcu::Msg_List::list_create_Node()
{
    Node *node = nullptr;
    node = (struct Node *) malloc(sizeof(struct Node));
    return (list_check_error(node)) ? nullptr : node;
}

/**
 * @brief Entscheidet woher das Node-Struktur-Element kommen soll
 * @return Pointer auf das Node-Struktur-Element
 * 
 * -# Diese Funktion entscheidet ob das Angeforderte Listen-Element von der Buffer-Liste entnommen werden soll
 *    oder ob es neu dynamisch auf dem Heap erzeugt werden soll
 * -# Ist noch mindestens ein Listen-Element im Buffer, so wird immer aus Effizienzgründen das Element von dort entnommen
*/
dcu::Msg_List::Node *dcu::Msg_List::list_pick_Node()
{
    if (this->buf_msg->leangh > 0)
    {
        return list_pop_last_element(this->buf_msg);
    } else {
        return list_create_Node();
    }
}

/**
 * @brief Erzeugen von Standart-CAN-Frame auf dem Heap
 * @return Pointer auf das erzeugte CAN-Frame 
 * 
 * -# Erzeugt CAN-Frame dynamisch auf dem Heap
 * -# Gibt Pointer auf diese Struktur zurück
*/
can_frame *dcu::Msg_List::list_create_Can_Frame()
{
    can_frame *frame = nullptr;
    frame = (struct can_frame*) malloc(sizeof(struct can_frame));
    return (list_check_error(frame)) ? nullptr : frame;
}

/**
 * @brief Liste Element hinzufügen
 * @param list Listenpointer der Liste, welcher ein Element hinzgefügt werden soll
 * @param node Pointer auf das einzufügende Element
 * @param frame_pr Pointer auf das CAN-Frame, der in das Listen-Element kopiert werden soll
 * @param socket_name Name des Socket als String
 * @return Indikator ob die Funktion erfolgreich war
 * 
 * TODO: socket_name durch einen int Wert ersetzen um schneller zu werden
 * TODO: Mutex-Lock-guard durch Atomic-Lock-guard ersetzten
 * TODO: CAN-FRAME Buffer einbauen
 * 
 * -# Die Funktion ist mit einem Mutex-Lock-guard abgesichert
 * -# list_pick_Node() stellt ein neues Listenelement zu verfügung
 * -# Listenelement wird der Liste hinzugefügt 
 * -# Ein neues CAN-Frame wird erzeugt
 * -# Inhalt des Übergebenen CAN-Fram wird in den neu erzeugten Kopiert
*/

bool dcu::Msg_List::list_append(Msg_List::List *list, Msg_List::Node *node, can_frame *frame_ptr, const char *socket_name)
{
    std::lock_guard<std::mutex> lock(this->mtx);

    if (list == nullptr || node == nullptr || frame_ptr == nullptr) return false;

    if (list_insert_head(list, node) != true) return false;

    node->frame = list_create_Can_Frame();
    if(list_check_error(node->frame)) return false;
    memcpy(node->frame, frame_ptr, sizeof(struct can_frame));

    strncpy(node->socket_name, socket_name, MAX_SOCKET_NAME_LEANGH);

    list->leangh++;

    return true;
}

/**
 * @brief Fügt Listen-Element am Kopf der Liste ein
 * @param list Pointer auf die Liste
 * @param node Pointer auf das einzufügende Element 
 * @return Einfügen erfolgreich (ja/nein)
*/
bool dcu::Msg_List::list_insert_head(Msg_List::List *list, Msg_List::Node *node)
{

    if (list == nullptr || node == nullptr) return false;

    if (list->head == nullptr || list->tail == nullptr)
    {
        list->head = node;
        list->tail = node;
        node->next = nullptr;
        node->prev = nullptr;
    } else {
        list->head->prev = node;
        node->next = list->head;
        list->head = node;
        node->prev = nullptr;
    }

    return true;
}
/**
 * @brief Entfernen des Letzten Elementes eienr Liste
 * @param list Pointer auf die Liste, in welcher das letzte Element entfernt werden soll
 * @return Pointer auf das entfernte letzte Element
 * 
 * -# Die Funktion ist mit einem Mutex-Lock-guard abgesichert
 * -# Wenn die Liste noch mindestens ein Listenelement besitzt wird dieses aus der Liste herrausgelöst und der Funktion zurückgegeben
 * -# Die Länge der Liste wird decrementiert
*/
dcu::Msg_List::Node *dcu::Msg_List::list_pop_last_element(Msg_List::List *list)
{
    std::lock_guard<std::mutex> lock(this->mtx);

    struct Node *node_backup = nullptr;

    if(list->head != nullptr && list->tail != nullptr)
    {
        if(list->tail->prev == nullptr)
        {
            node_backup = list->tail;
            list->tail = nullptr;
            list->head = nullptr;
            node_backup->next = nullptr;
            node_backup->prev = nullptr;
        } else {
            node_backup = list->tail;
            list->tail = list->tail->prev;
            list->tail->next = nullptr;
            node_backup->prev = nullptr;
        }
        list->leangh--;

        return node_backup;
    } else {
        
        return nullptr;
    }
}

/**
 * @brief Löschen eines Listen-Elements
 * @param node Pointer auf das Listen-Element
*/
void dcu::Msg_List::list_delete_node(struct Node *node)
{
    if (node != nullptr) free(node);
}


/**
 * @brief Ausgabe der Kompleten Liste
 * @param list Pointer auf die auszugebende Liste
*/
void dcu::Msg_List::list_print(Msg_List::List *list)
{
    std::lock_guard<std::mutex> lock(this->mtx);

    struct Node *node = list->head;

    while(node != nullptr)
    {
        printf("%s: 0x%03X [%d] ", node->socket_name, node->frame->can_id, node->frame->can_dlc);
        for (int i = 0; i < CAN_MAX_DLEN; i++)
        {
            printf("%02X ", node->frame->data[i]);
        }
        printf("\n");

        node = node->next;
    }
    
}

/**
 * @brief Ausgabe eines einzelnen Listen-Elements
 * @param node Pointer auf das auszugebende Liste-Element
*/
void dcu::Msg_List::list_print_node(struct Node *node)
{
    std::lock_guard<std::mutex> lock(this->mtx);

    if (node != NULL)
    {
        printf("%s: 0x%03X [%d] ", node->socket_name, node->frame->can_id, node->frame->can_dlc);
        for (int i = 0; i < CAN_MAX_DLEN; i++)
        {
            printf("%02X ", node->frame->data[i]);
        }
        printf("\n");
    }
}

/**
 * @brief Verbrauchtes Listen-Element der einer Liste Anhängen
 * @param list Pointer auf die Liste der das Listen-Element angehängt werden soll
 * @param list Pointer auf das Listen-Element das der Liste Angängt werden soll
 * 
 * -# Ist die Liste oder das Listen-Element nicht Null wird das Listen-Element der Liste Angehängt 
 * -# Länge der Liste wird inkrementiert um eins
*/
void dcu::Msg_List::list_revert_node(Msg_List::List *list, Msg_List::Node *node)
{
    std::lock_guard<std::mutex> lock(this->mtx);
    
    if (node == nullptr || list == nullptr) return;

    if (list->head == nullptr || list->tail == nullptr)
    {
        list->head = node;
        list->tail = node;
        node->next = nullptr;
        node->prev = nullptr;
    } else {
        list->head->prev = node;
        node->next = list->head;
        list->head = node;
        node->prev = nullptr;
    }

    list->leangh++;
}


