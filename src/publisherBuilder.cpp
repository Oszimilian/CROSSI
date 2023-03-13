#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <iostream>
#include <iterator>
#include <filesystem>

#include "publisherBuilder.h"
#include "config.h"
#include "Fixed.h"

dcu::Publisher_Builder::Publisher_Builder()
{

}

dcu::Publisher_Builder::~Publisher_Builder()
{
    delete this->fixed_header;
    delete this->fixed_source;
}

void dcu::Publisher_Builder::update_publisher(std::vector<std::string> *ros_msg)
{
    if (ros_msg != nullptr)
    {
        this->ros_msg_vec_ptr = ros_msg; 

        this->fixed_header = new Fixed;
        fixed_header->init_file(*config_get_publisher_header_path(), "//START_CUSTOM_AREA", "//END_CUSTOM_AREA");
        this->fixed_header->reset();

        /*
        if (!save_fixed_area_source("//START_CUSTOM_AREA", "//END_CUSTOM_AREA"))
        {
            std::cerr << "Error: Publisher_Builder faild saving fixed code area" << std::endl;
            exit(-1);
        }
        */
       this->fixed_source = new Fixed;
       fixed_source->init_file(*config_get_publisher_source_path(), "//START_CUSTOM_AREA", "//END_CUSTOM_AREA");
       this->fixed_header->reset();
        

        if (delete_publisher())
        {
            if (!build_ros_publisher_header())
            {
                std::cerr << "Error: publisher header could not been created" << std::endl;
                exit(-1);
            }
            if (!build_ros_publisher_source())
            {
                std::cerr << "Error: publisher source could not been created" << std::endl;
                exit(-1);
            }
        } else {
            std::cerr << "Error: publisher could not delete to build a new one" << std::endl;
            exit(-1);
        }
    } else {
        std::cerr << "Error: Update publisher has no ros_msg_vector provided" << std::endl;
        exit(-1);
    }
}

bool dcu::Publisher_Builder::save_fixed_area_source(std::string start, std::string end)
{
    std::ifstream file(*config_get_publisher_source_path(), std::ios::in);
    if (!file.is_open()) return false;

    std::string line;

    while(std::getline(file, line))
    {   
        this->fixed_area_source.push_back(line);
        this->start_custom_area_source++;
        if (line.find(start) != std::string::npos) break;
    }

    if (file.eof())
    {
        file.close();
        return false;
    }

    while(std::getline(file, line) && line != end)
    {
        if (line.find(end) != std::string::npos)
        {
            break;
        }
    }

    if (file.eof() && line.find(end) == std::string::npos)
    {
        file.close();
        return false;
    }

    do
    {
        this->fixed_area_source.push_back(line);
    } while(std::getline(file, line));

    file.close();



    return true; 
}

bool dcu::Publisher_Builder::save_fixed_area_header(std::string start, std::string end)
{
    std::ifstream file(*config_get_publisher_header_path(), std::ios::in);
    if (!file.is_open()) return false;

    std::string line;

    while(std::getline(file, line))
    {   
        this->fixed_area_header.push_back(line);
        this->start_custom_area_header++;
        if (line.find(start) != std::string::npos) break;
    }

    

    if (file.eof())
    {
        file.close();
        return false;
    }

    while(std::getline(file, line) && line != end)
    {
        if (line.find(end) != std::string::npos)
        {
            break;
        }
    }

    if (file.eof() && line.find(end) == std::string::npos)
    {
        file.close();
        return false;
    }

    do
    {
        this->fixed_area_header.push_back(line);
    } while(std::getline(file, line));


    file.close();

    return true; 
}

bool dcu::Publisher_Builder::delete_publisher()
{
    std::ofstream header(*config_get_publisher_header_path(), std::ios::out | std::ios::trunc);

    if (header.is_open())
    {
        header.clear();
        header.close();
        
        std::ofstream source(*config_get_publisher_source_path(), std::ios::out | std::ios::trunc);

        if (source.is_open())
        {
            source.clear();
            source.close();

            return true;
        } else {
            return false;
        }
    } else {
        return false;
    }
}

bool dcu::Publisher_Builder::build_ros_publisher_header()
{
    std::ofstream file(*config_get_publisher_header_path(), std::ios::out | std::ios::app);
    if (!file.is_open()) return false;

    for (auto i : *this->fixed_header->get_vec())
    {
        file << i << std::endl;
    }

    for (auto i : *ros_msg_vec_ptr)
    {
        file << "\t";
        file << "void " << i.substr(0, i.find(".")) <<"(const std::string* str, std::vector<float> *input, Crossi_Publisher *pup);" << std::endl;
    }

    for (auto i : *this->fixed_header->get_vec())
    {
        file << i << std::endl;
    }
    
    file.close();

    return true;
}

bool dcu::Publisher_Builder::build_ros_publisher_source()
{
    std::ofstream file(*config_get_publisher_source_path(), std::ios::out | std::ios::app);
    if (!file.is_open()) return false;

    /*
    int i = 0;
    for(i = 0; i < this->start_custom_area_source; i++)
    {
        file << this->fixed_area_source[i] << std::endl;
    }
    */

    for (auto i : *this->fixed_source->get_vec())
    {
        file << i << std::endl;
    }

    std::cout << "Test" << std::endl;

    // Create setup_function_map() funktion
    file << "void dcu::Crossi_Publisher::setup_function_map()" << std::endl;
    file << "{" << std::endl;
    for(auto i : *ros_msg_vec_ptr)
    {
        file << "\t" << "ros_msg_functions.insert(std::make_pair(";
        file << "\"" << i.substr(0, i.find(".")) << "\", ";
        file << "&" << i.substr(0, i.find(".")) << "));";
        file << std::endl;
    }
    file << "}" << std::endl;
    file << std::endl;


    // Create setup_publisher_map() function
    file << "void dcu::Crossi_Publisher::setup_publisher_map()" << std::endl;
    file << "{" << std::endl;
    for (auto i : *ros_msg_vec_ptr)
    {
        file << "\t" << "ros_msg_publisher.insert(std::make_pair(\"";
        file << i.substr(0, i.find(".")) << "\", ";
        file << "new ros::Publisher((node_handler.advertise<crossi::";
        file << i.substr(0, i.find(".")) << ">(\"";
        file << i.substr(0, i.find(".")) << "\"" << ", 100))) ));" << std::endl;
    }
    file << "}" << std::endl;
    file << std::endl;



    // Create all signal_funktions
    for (auto i : *ros_msg_vec_ptr)
    {
        file << "void dcu::" << i.substr(0, i.find("."))  << "(const std::string *str, std::vector<float> *input, dcu::Crossi_Publisher *pup)" << std::endl;
        file << "{" << std::endl;
        file << "\t" << "crossi::" << i.substr(0, i.find(".")) << " " << "msg;" << std::endl;
        file << "\t" << "fill_ros_msg(&msg, nullptr);" << std::endl;
        file << "\t" << "for (auto i : *input)" << std::endl;
        file << "{" << std::endl;
        file << "\t" << "\t" << "fill_ros_msg(nullptr, &i);" << std::endl;
        file << "\t" << "}" << std::endl;
        file << "\t" << "pup->ros_msg_publisher[*str]->publish(msg);" << std::endl;
        file << "}" << std::endl;
        file << std::endl;
    }

    /*
    for (int j = i; j < this->fixed_area_source.size(); j++)
    {
        file << this->fixed_area_source[j] << std::endl;
    }
    */

    for (auto i : *this->fixed_source->get_vec())
    {
        file << i << std::endl;
    }    

    file.close();

    return true;
}