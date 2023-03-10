#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <sstream>
#include <iterator>

#include "config.h"

dcu::Config::Config()
{
    this->dcu_config_file_path = DEFAULT_CONFIG_PATH;

    analyse_crossi_config_file();

}

dcu::Config::~Config()
{

}

bool dcu::Config::check_dcu_config_file(int argc, char **argv)
{
    if (argc > 1)
    {
        this->dcu_config_file_path.assign(argv[2]);
    } else {
        this->dcu_config_file_path.assign(DEFAULT_CONFIG_PATH);
    }

    return true;
}

bool dcu::Config::analyse_crossi_config_file()
{
    std::ifstream file(this->dcu_config_file_path);
    if (!file.is_open())
    {
        std::cerr << "Error: CROSSI config File could not open" << std::endl;
        exit(-1);
    }

    std::string line;
    std::istringstream iss;
    std::istream_iterator<std::string> iter(iss);
    std::istream_iterator<std::string> end;

    int can_channel = 0;

    while(std::getline(file, line))
    {
        iss.clear();
        iss.str(line);
        iter = std::istream_iterator<std::string>(iss);

        if (*iter == "#") continue;

        if (*iter == CAN_AMOUNT)
        {
            iter++;
            can_channel = get_channel(&(*iter));
            handle_load_error(&can_channel, CAN_AMOUNT);
            for (int i = 0; i < can_channel; i++)
                dcu_config_params.insert(std::make_pair(i, new Channel_Config));
            this->can_amount = can_channel;
        }

        else if (   *iter == CAN_SETUP ||
                    *iter == IMPORT_DBC || 
                    *iter == CAPTURE_MODE ||
                    *iter == DECODE_MODE ||
                    *iter == ROS_MSG_DIR || 
                    *iter == DBC_MSG_IGN)
        {
            const std::string instruction = *iter;

            iter++;
            can_channel = get_channel(&(*iter));
            handle_load_error(&can_channel, IMPORT_DBC);
            iter++;
            handle_load_error(&(*iter), IMPORT_DBC);
            iter++;

            if (instruction == CAN_SETUP)
                dcu_config_params[can_channel]->socket_name = *iter;
            else if (instruction == IMPORT_DBC)
                dcu_config_params[can_channel]->dbc_path = *iter;
            else if (instruction == CAPTURE_MODE)
                dcu_config_params[can_channel]->capture_mode = *iter;
            else if (instruction == DECODE_MODE)
                dcu_config_params[can_channel]->decode_mode = *iter;
            else if (instruction == ROS_MSG_DIR)
                dcu_config_params[can_channel]->ros_msg_dir = *iter;
            else if (instruction == DBC_MSG_IGN)
                dcu_config_params[can_channel]->dbc_msg_ignore.insert(std::make_pair(*iter, *iter));
            else 
            {
                std::cout << "ERROR: Analysing the crossi_config.txt failed: " << instruction << std::endl;
                exit(-1);
            }
                
        }

        
        else if (   *iter == FORCE_MSG_GEN || 
                    *iter == HASH_DBC_PATH ||
                    *iter == ROS_MSG_PATH ||
                    *iter == CMAKE_FILE
                    )
        {
            const std::string instruction = *iter;

            iter++;
            if (*iter == "=")
            {
                iter++;
                
                if (instruction == FORCE_MSG_GEN)
                    this->ros_msg_force = ( (*iter == "ON") || (*iter == "On")) ? true : false;
                else if (instruction == HASH_DBC_PATH)
                    this->hash_dbc_path = *iter;
                else if (instruction == ROS_MSG_PATH)
                    this->ros_msg_dir = *iter;
                else if (instruction == CMAKE_FILE)
                    this->cmake_file_path = *iter;
                else 
                {
                    std::cout << "ERROR: Analysing the crossi_cofnig.txt Failed: " << instruction << std::endl;
                    exit(-1);
                }  
            } else {
                    std::cout << "ERROR: Analysing the crossi_cofnig.txt Failed: " << instruction << std::endl;
                    exit(-1);
            }
        }
    

    }

    file.close();

    return true;
}

void dcu::Config::config_print_settings()
{
    for (int i = 0; i < this->can_amount; i++)
    {
        config_print(i);
    }

    std::cout << "\t CONFIG:" << std::endl;
    std::cout << "Hash_DBC_Path: \t" << this->ros_msg_dir << std::endl;
    std::cout << "ROS_Msg_Path: \t" << this->hash_dbc_path << std::endl;
    std::cout << "CMake_File: \t" << this->cmake_file_path << std::endl;
    std::cout << std::endl;
}

int dcu::Config::get_channel(const std::string *str)
{
    if (!is_string_digit(str)) return -1;

    int channel;
    std::stringstream ss;
    ss.clear();
    ss << *str;
    ss >> channel;

    return channel;
}

bool dcu::Config::is_string_digit(const std::string *str)
{
    if (str->empty()) return false;
    for (auto &i : *str)
    {
        if (!isdigit(i)) return false;
    }
    return true;
}

void dcu::Config::handle_load_error(int *n, std::string str)
{
    if (*n == -1)
    {
        std::cerr << "Error: Failed to load " << str << std::endl;
        exit(-1);
    }
}

void dcu::Config::handle_load_error(const std::string *c, std::string str)
{
    if (*c != "=")
    {
        std::cerr << "Error: Failed to load " << str << std::endl;
        exit(-1);
    }
}

void dcu::Config::config_print(int n)
{
    std::cout << "\t CONFIG:" << std::endl;
    std::cout << "Socketname: \t" << dcu_config_params[n]->socket_name << std::endl;
    std::cout << "DBC_File_Path: \t" << dcu_config_params[n]->dbc_path << std::endl;
    std::cout << "Capture_Mode: \t" << dcu_config_params[n]->capture_mode << std::endl;
    std::cout << "Decode_Mode: \t" << dcu_config_params[n]->decode_mode << std::endl;
    std::cout << "Ros_Msg_Dir: \t" << dcu_config_params[n]->ros_msg_dir << std::endl;

    for (auto &i : dcu_config_params[n]->dbc_msg_ignore)
    {
        std::cout << "DBC_MSG_IGNORE: \t" << i.second << std::endl;
    }
    std::cout << std::endl;
}

std::string dcu::Config::config_get_socketname(int socket)
{
    return dcu_config_params[socket]->socket_name;
}

std::string dcu::Config::config_get_dbc_path(int socket)
{
    return dcu_config_params[socket]->dbc_path;
}


std::string dcu::Config::config_get_capture_mode(int socket)
{
    return dcu_config_params[socket]->capture_mode;
}


std::string dcu::Config::config_get_decode_mode(int socket)
{
    return dcu_config_params[socket]->decode_mode;
}

std::vector<std::string> *dcu::Config::config_get_socketnames()
{
    std::vector<std::string> *ret = new std::vector<std::string>();

    for (int i = 0; i < config_get_can_count(); i++)
    {
        ret->push_back(config_get_socketname(i));
    }

    return ret;
}

std::vector<std::string> *dcu::Config::config_get_pathnames()
{
    std::vector<std::string> *ret = new std::vector<std::string>();

    for (int i = 0; i < config_get_can_count(); i++)
    {
        ret->push_back(config_get_dbc_path(i));
    }

    return ret;
}



int dcu::Config::config_get_can_count()
{
    return this->can_amount;
}

bool dcu::Config::config_validate_dbc_msg(int socket, const std::string *dbc_msg)
{
    auto it = this->dcu_config_params[socket]->dbc_msg_ignore.find(*dbc_msg);

    return (it != this->dcu_config_params[socket]->dbc_msg_ignore.end()) ? true : false;
}

int dcu::Config::config_get_socket_from_path(std::string dbc_path_local)
{
    for (int i = 0; i < config_get_can_count(); i++)
    {
        if (this->dcu_config_params[i]->dbc_path == dbc_path_local) return i;
    }

    return -1;
}

bool dcu::Config::config_get_ros_msg_force()
{
    return this->ros_msg_force;
}

std::string *dcu::Config::config_get_hash_dbc_path()
{
    return &this->hash_dbc_path;
}

std::string *dcu::Config::config_get_ros_msg_dir()
{
    return &this->ros_msg_dir;
}

std::string *dcu::Config::config_get_cmake_path()
{
    return &this->cmake_file_path;
}