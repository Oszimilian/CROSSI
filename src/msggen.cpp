#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <functional>
#include <sstream>
#include <iostream>

#include "fileHasher.h"
#include "msgBuilder.h"
#include "dcu.h"

dcu::Msggen::Msggen(dcu::DCU_Handler *handler) : 
        handler(handler), 
        File_Hasher(handler->config_get_pathnames(), DEFAULT_DBC_CHANGE_PATH),
        Msg_Builder(handler->config_get_pathnames(), handler)
{
    if (changes_notified() || handler->config_get_ros_msg_force())
    {
        std::cout << "Changes in .dbc-Files notified" << std::endl;
        start_creating_ros_msg();
    } 

}



