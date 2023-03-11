#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <iostream>
#include <iterator>
#include <filesystem>

#include "msgBuilder.h"
#include "dcu.h"
#include "config.h"


dcu::Msg_Builder::Msg_Builder() : Config()
{
    file_paths = config_get_pathnames();
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
    int socket = config_get_socket_from_path(*file_path);
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
                skip_dbc_msg = (config_validate_dbc_msg(socket, &(*iter))) ? true : false;
                if (skip_dbc_msg) break;
                file_ptr = (count == 2) ? create_new_ros_msg(&(*iter)) : file_ptr;
                iter++;
                skip_dbc_msg = false;
                count++;
            } while ( (*iter != filter_2) && (iter != end));
            count = 0;
        }

        if (*iter == filter_2 && !skip_dbc_msg && file_ptr != nullptr)   
        {
            do
            {
                if (count == 1) add_ros_msg_sig(file_ptr, &data_typ, &(*iter));
                iter++;
                count++;
            } while( (*iter != filter_1) && (*iter != filter_2) && (iter != end));

            count = 0;
        }
        
    }

    file.close();
}

std::ofstream *dcu::Msg_Builder::create_new_ros_msg(const std::string *msg_name)
{
    std::filesystem::path p(*config_get_ros_msg_dir());
    if (!std::filesystem::exists(p))
    {
        std::cerr << "Error: can not open directory: " << *config_get_ros_msg_dir() << std::endl;
        exit(-1);
    }

    std::string new_msg_name = msg_name->substr(0, msg_name->size() - 1) + ".msg";

    std::ofstream *file = new std::ofstream(*config_get_ros_msg_dir() + new_msg_name, std::ios::out | std::ios::app);
    if (!file->is_open())
    {
        std::cerr << "Error: can not create ros-msg-file: " << *msg_name << std::endl;
        exit(-1);
    }

    //std::cout << new_msg_name << std::endl;
    ros_msg.push_back(new_msg_name);

    p.clear(); 

    return file;
}

void dcu::Msg_Builder::close_new_ros_msg(std::ofstream *file)
{
    if (file == nullptr) return;
    file->close();
    delete file;
    this->ros_msg_count++;
}

void dcu::Msg_Builder::add_ros_msg_sig(std::ofstream *file, const std::string *data_typ, const std::string *var_name)
{
    if (file == nullptr) return;
    *file << *data_typ << " " << *var_name << std::endl;
}

void dcu::Msg_Builder::init_ros_msg_folder()
{
    std::string cmd = "mkdir ../msg";
    cmd.clear();
    cmd = "rm -rf ";
    cmd += *config_get_ros_msg_dir();
    cmd += "*.msg";
    std::system(cmd.c_str());
}


std::vector<std::string> *dcu::Msg_Builder::builder_get_ros_msg_vec()
{
    return &this->ros_msg;
}

void dcu::Msg_Builder::print_info()
{
    std::cout << "\t CREATE ROS MSG" << std::endl;
    std::cout << "ROS_MSG_AMOUNT: " << this->ros_msg_count << std::endl;
    std::cout << "ROS_MSG_DIR: " << *config_get_ros_msg_dir() << std::endl;
    std::cout << std::endl;
}