#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <iostream>
#include <iterator>
#include <filesystem>

#include "loadROSMsg.h"

dcu::Load_ROS_Msg::Load_ROS_Msg()
{
    
}


void dcu::Load_ROS_Msg::update_ros_msg_files_in_cmake(std::vector<std::string> *ros_msg_ptr)
{
    this->ros_msg_ptr = ros_msg_ptr;
    this->fixed_area = new Fixed;
    this->fixed_area->init_file(*config_get_cmake_path(), "#START_CUSTOM_AREA", "#END_CUSTOM_AREA");
    this->fixed_area->reset();

    if (!delete_old_ros_msg_cmake())
    {
        std::cerr << "Error: can not delete / clear cmake-file" << std::endl;
        exit(-1);
    }

    if(!create_new_ros_msg_in_cmake())
    {
        std::cerr << "Error: failed to build new CMakeLists.txt" << std::endl;
        exit(-1);
    }
}

bool dcu::Load_ROS_Msg::delete_old_ros_msg_cmake()
{
    std::ofstream file(*config_get_cmake_path(), std::ios::out | std::ios::trunc);
    if (!file.is_open()) return false;

    file.clear();
    file.close();

    return true;
}

bool dcu::Load_ROS_Msg::create_new_ros_msg_in_cmake()
{
    std::ofstream file(*config_get_cmake_path(), std::ios::app | std::ios::out);
    if (!file.is_open()) false;

    for (auto i : *this->fixed_area->get_vec())
    {
        file << i << std::endl;
    }

    if (ros_msg_ptr != nullptr)
    {
        for (auto i : *ros_msg_ptr)
        {
            file << i << std::endl;
        }
    }

    for (auto i : *this->fixed_area->get_vec())
    {
        file << i << std::endl;
    }

    return true;
}
