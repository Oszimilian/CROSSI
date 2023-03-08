#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <iostream>
#include <iterator>
#include <filesystem>

#include "msgBuilder.h"
#include "dcu.h"



dcu::Msg_Builder::Msg_Builder(std::vector<std::string> *file_paths, dcu::DCU_Handler *handler) :
    file_paths(file_paths),
    handler(handler)
{

}

void dcu::Msg_Builder::start_creating_ros_msg()
{
    init_ros_msg_folder();

    for (auto i : *this->file_paths)
    {
        analyse_file_with_filter(&i, "BO_", "SG_");
    }
}

void dcu::Msg_Builder::analyse_file_with_filter(std::string *file_path, std::string filter_1, std::string filter_2)
{
    std::ifstream file(*file_path);
    if (!file.is_open())
    {
        std::cerr << "Error: Can't open file for ROS-Msg-Builder: " << *file_path << std::endl;
        exit(-1);
    }

    std::string line;

    std::istringstream iss;
    std::istream_iterator<std::string> iter(iss);
    std::istream_iterator<std::string> end;

    int count = 0; 
    int socket = this->handler->config_get_socket_from_path(*file_path);
    bool skip_dbc_msg = false;

    

    std::string data_typ = "float32";
    std::string var_name;
    std::ofstream *file_ptr = nullptr;
    
    while(std::getline(file, line))
    {
        
        iss.clear();
        iss.str(line);
        iter = std::istream_iterator<std::string>(iss);

        if (*iter == filter_1)
        {
            close_new_ros_msg(file_ptr);
            do
            {
                skip_dbc_msg = (this->handler->config_validate_dbc_msg(socket, &(*iter))) ? true : false;
                if (skip_dbc_msg) break;
                file_ptr = (count == 2) ? create_new_ros_msg(&(*iter)) : file_ptr;
                //std::cout << *iter << " ";
                iter++;
                skip_dbc_msg = false;
                count++;
            } while ( (*iter != filter_2) && (iter != end));
            count = 0;
            //std::cout << std::endl;
        }

        if (*iter == filter_2 && !skip_dbc_msg && file_ptr != nullptr)   
        {
            //std::cout << "\t";
            do
            {
                if (count == 1) add_ros_msg_sig(file_ptr, &data_typ, &(*iter));
                //std::cout << *iter << " ";
                iter++;
                count++;
            } while( (*iter != filter_1) && (*iter != filter_2) && (iter != end));
            //std::cout << std::endl;
            count = 0;
        }
        
    }

    file.close();
}

std::ofstream *dcu::Msg_Builder::create_new_ros_msg(const std::string *msg_name)
{
    std::filesystem::path p(ROS_MSG_PATH);
    if (!std::filesystem::exists(p))
    {
        std::cerr << "Error: can not open directory: " << ROS_MSG_PATH << std::endl;
        exit(-1);
    }

    std::string new_msg_name = msg_name->substr(0, msg_name->size() - 1) + ".msg";

    std::ofstream *file = new std::ofstream(ROS_MSG_PATH + new_msg_name, std::ios::out | std::ios::app);
    if (!file->is_open())
    {
        std::cerr << "Error: can not create ros-msg-file: " << *msg_name << std::endl;
        exit(-1);
    }

    p.clear(); 

    return file;
}

void dcu::Msg_Builder::close_new_ros_msg(std::ofstream *file)
{
    if (file == nullptr) return;
    file->close();
    delete file;
}

void dcu::Msg_Builder::add_ros_msg_sig(std::ofstream *file, const std::string *data_typ, const std::string *var_name)
{
    if (file == nullptr) return;
    *file << *data_typ << " " << *var_name << std::endl;
}

void dcu::Msg_Builder::init_ros_msg_folder()
{
    std::string cmd = "rm -rf ";
    cmd += ROS_MSG_PATH;
    cmd += "*.msg";
    std::system(cmd.c_str());
}