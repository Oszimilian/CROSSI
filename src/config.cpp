#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <sstream>

#include "config.h"

dcu::Config::Config(int argc, char **argv)
{
    handle_dcu_config_error(check_dcu_config_file(argc, argv));

    handle_dcu_config_error(open_dcu_config_file());

    analyse_dcu_config_file();

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


    std::ifstream file(this->dcu_config_file_path);


    return file.good();
}

template<typename T>
void dcu::Config::handle_dcu_config_error(T input)
{
    if (!input)
    {
        std::cerr << "Error: In DCU_Config! " << std::endl;
        exit(-1);
    }
}

bool dcu::Config::open_dcu_config_file()
{
    this->dcu_config_file = new std::ifstream(this->dcu_config_file_path);

    return this->dcu_config_file->is_open();
}

void dcu::Config::close_dcu_config_file()
{
    this->dcu_config_file->close();
}

bool dcu::Config::analyse_dcu_config_file()
{
    int can_amount;
    std::string instruktion;
    std::string identifier;
    int can_id;
    std::string value;

    int identifier_lengh;
    int id_start;
    int value_start;
    int instruktion_leangh;

    std::stringstream ss;


    std::getline(*this->dcu_config_file, instruktion);
    ss << instruktion.substr((instruktion.find(":") + 1), (instruktion.size() - (instruktion.find(":") + 1)));
    ss >> can_amount;
    this->can_amount = can_amount;
    for (int i = 0; i < can_amount; i++)
    {
        dcu_config_params.insert(std::make_pair(i, new Channel_Config));
    }
    
    ss.clear();
    
    while(std::getline(*this->dcu_config_file, instruktion))
    {
        if (instruktion.size() == 0) continue;
        if (instruktion.find("#") == 0) continue;

        identifier_lengh = instruktion.find("(");
        identifier = instruktion.substr(0, identifier_lengh);


        id_start = instruktion.find(")");
        ss << instruktion.substr( (identifier_lengh + 1), (id_start - (identifier_lengh + 1)));
        ss >> can_id;
        ss.clear();

        value_start = instruktion.find(":");
        instruktion_leangh = instruktion.size();
        value = instruktion.substr((value_start + 2), (instruktion_leangh - (value_start + 1)) );

        if (identifier == CAN_SETUP)
        { 
            dcu_config_params[can_id]->socket_name = value;
        }
        else if (identifier == IMPORT_DBC)
        {
            dcu_config_params[can_id]->dbc_path = value;
        }
        else if (identifier == CAPTURE_MODE)
        {
            dcu_config_params[can_id]->capture_mode = value;
        }
        else if (identifier == DECODE_MODE)
        {
            dcu_config_params[can_id]->decode_mode = value;
        }

    }

    for (int i = 0; i < this->can_amount; i++)
    {
        config_print(i);
    }


    return true;
}

void dcu::Config::config_print(int n)
{
    std::cout << "\t CONFIG:" << std::endl;
    std::cout << "Socketname: \t" << dcu_config_params[n]->socket_name << std::endl;
    std::cout << "DBC_File_Path: \t" << dcu_config_params[n]->dbc_path << std::endl;
    std::cout << "Capture_Mode: \t" << dcu_config_params[n]->capture_mode << std::endl;
    std::cout << "Decode_Mode: \t" << dcu_config_params[n]->decode_mode << std::endl;
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