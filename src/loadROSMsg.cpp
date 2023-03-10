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
    std::string start = "#CROSSI_IMPORT_ROS_MSG_START";
    std::string end = "#CROSSI_IMPORT_ROS_MSG_END";

    read_old_ros_msg_cmake(&start, &end);
    delete_old_ros_msg_cmake();
    //print_new_cmake_file();
    create_new_ros_msg_in_cmake(&start, &end);
}

void dcu::Load_ROS_Msg::read_old_ros_msg_cmake(const std::string *start, const std::string *end)
{
    std::cout << *config_get_cmake_path() << std::endl;

    std::ifstream file(*config_get_cmake_path(), std::ios::in | std::ios::out);
    if (!file.is_open())
    {
        std::cerr << "Error: CMakeLists.txt could not open to delete ros-msg!" << std::endl;
        exit(-1);
    }

    std::string str;
    this->cmake_insert_point = 0;

    while(std::getline(file, str))
    {
        //std::cout << str << std::endl;
        this->cmake_file.push_back(str);
        this->cmake_insert_point++;
        if (str.find(*start) != std::string::npos) break;
    }

    while(std::getline(file, str))
    {
        //std::cout << "->" << str << std::endl;
        if (str.find(*end) != std::string::npos)
        {
            this->cmake_file.push_back(str);
            break;
        }
    }

    while(std::getline(file, str))
    {
        //std::cout << str << std::endl;
        this->cmake_file.push_back(str);
    }


    file.close();

}

void dcu::Load_ROS_Msg::delete_old_ros_msg_cmake()
{
    //std::fstream erase(*config_get_cmake_path(), std::ofstream::trunc);
    //erase.close(); 

    std::ofstream file(*config_get_cmake_path(), std::ios::out | std::ios::trunc);

    if (file.is_open())
    {
        file.clear();
        file.close();
    }
}

void dcu::Load_ROS_Msg::create_new_ros_msg_in_cmake(const std::string *start, const std::string *end)
{
    std::ofstream file(*config_get_cmake_path(), std::ios::app | std::ios::out);
    if (!file.is_open())
    {
        std::cerr << "Error: Creating new CMakeLists.txt faild: " << *config_get_cmake_path() << std::endl;
        exit(-1);
    }

    int i = 0;
    for (i = 0; i < cmake_insert_point; i++)
    {
        file << cmake_file.at(i) << std::endl;
    }

    if (ros_msg_ptr != nullptr)
    {
        for (auto i : *ros_msg_ptr)
        {
            file << i << std::endl;
        }
 
    }


    for (int m = i ; m < cmake_file.size(); m++)
    {
        file << cmake_file.at(m) << std::endl;
    } 

}

void dcu::Load_ROS_Msg::print_new_cmake_file()
{
    int i = 0;
    for (i = 0; i < cmake_insert_point; i++)
    {
        std::cout << cmake_file.at(i) << std::endl;
    }

    if (ros_msg_ptr != nullptr)
    {
        for (auto i : *ros_msg_ptr)
        {
            std::cout << i << std::endl;
        }
 
    }


    for (int m = i ; m < cmake_file.size(); m++)
    {
        std::cout << cmake_file.at(m) << std::endl;
    } 
}