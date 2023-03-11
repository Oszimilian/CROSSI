#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <functional>
#include <sstream>
#include <iostream>

#include "fileHasher.h"
#include "msgBuilder.h"
#include "config.h"
#include "dcu.h"
#include "loadROSMsg.h"
#include "msggen.h"
#include "headerBuilder.h"

dcu::Msggen::Msggen()
{
    
}

void dcu::Msggen::start_message_generation()
{
    if (changes_notified() || config_get_ros_msg_force())
    {
        start_creating_ros_msg();
        Msg_Builder::print_info();
        update_ros_msg_files_in_cmake(builder_get_ros_msg_vec());
        update_ros_msg_header(builder_get_ros_msg_vec());
        Header_Builder::print_info();
    } 
}


