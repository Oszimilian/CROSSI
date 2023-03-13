#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <iostream>
#include <iterator>
#include <filesystem>

#include "headerBuilder.h"
#include "config.h"
#include "Fixed.h"


dcu::Header_Builder::Header_Builder()
{
    
}

dcu::Header_Builder::~Header_Builder()
{
    delete this->fixed_space;
}

void dcu::Header_Builder::update_ros_msg_header(std::vector<std::string> *ros_msg)
{
    if (ros_msg != nullptr)
    {
        this->ros_msg_vec_ptr = ros_msg;

        this->fixed_space = new Fixed;
        fixed_space->init_file(*config_get_rosmsg_header_path());
        fixed_space->reset();

        if (!delete_ros_msg_header())
        {
            std::cerr << "Error: Update headers could not delete old headerfile with includes" << std::endl;
            exit(-1);
        }

        if(!build_ros_msg_header())
        {   
            std::cerr << "Error: Update headers could not open to create the headers" << std::endl;
            exit(-1);
        }


    } else {
        std::cerr << "Error: Update headers has no ROS messages provided" << std::endl;
        exit(-1);
    }
}

bool dcu::Header_Builder::delete_ros_msg_header()
{
    std::ofstream file(*config_get_rosmsg_header_path(), std::ios::out | std::ios::trunc);

    if (file.is_open())
    {
        file.clear();
        file.close();
        return true;
    } else {
        return false;
    }
}

bool dcu::Header_Builder::build_ros_msg_header()
{
    std::ofstream file(*config_get_rosmsg_header_path(), std::ios::out | std::ios::app);
    if (!file.is_open()) return false;

    for (auto i : *this->fixed_space->get_vec())
    {
        file << i << std::endl;
    }

    for (auto i : *ros_msg_vec_ptr)
    {
        file << "#include " << "\"crossi/" << i.substr(0, i.find(".")) << ".h\"" << std::endl;
    }

    for (auto i : *this->fixed_space->get_vec())
    {
        file << i << std::endl;
    }
    file << std::endl;


    file.close();

    return true;

}

std::string dcu::Header_Builder::get_header_name()
{
    std::string header_name;
    
    header_name += "#include \"";
    header_name += config_get_rosmsg_header_path()->substr(0, config_get_rosmsg_header_path()->find("."));
    header_name += ".h";
    header_name += "\"";

    return header_name;
}

void dcu::Header_Builder::print_info()
{
    std::cout << "\t CREATE ROS MSG HEADER" << std::endl;
    std::cout << "ROS_MSG_HED_AMOUNT: " << this->ros_msg_vec_ptr->size() << std::endl;
    std::cout << "ROS_MSG_HEAD_DIR: " << *this->config_get_rosmsg_header_path() << std::endl;
    std::cout << std::endl;
}