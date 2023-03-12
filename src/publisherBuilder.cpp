#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <iostream>
#include <iterator>
#include <filesystem>

#include "publisherBuilder.h"
#include "config.h"

dcu::Publisher_Builder::Publisher_Builder()
{

}

void dcu::Publisher_Builder::update_publisher(std::vector<std::string> *ros_msg)
{
    if (ros_msg != nullptr)
    {
        this->ros_msg_vec_ptr = ros_msg;
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

    file << "#ifndef CROOSI_PUBLISHER_H" << std::endl;
    file << "#define CROOSI_PUBLISHER_H" << std::endl;
    file << std::endl;

    file << "#include <map>" << std::endl;
    file << "#include \"ros/ros.h\"" << std::endl;
    file << "#include \"ros_msg_header.h\"" << std::endl;
    file << std::endl;

    file << "namespace dcu {" << std::endl;
    file << "\t" << "class Crossi_Publisher;" << std::endl;
    std::cout << std::endl;


    for (auto i : *ros_msg_vec_ptr)
    {
        file << "\t";
        file << "void " << i.substr(0, i.find(".")) <<"(const std::string* str, std::vector<float> *input, Crossi_Publisher *pup);" << std::endl;
    }
    std::cout << std::endl;

    file << "\t" << "void fill_ros_msg(void *start, float *input);" << std::endl;
    file << std::endl;


    file << "\t" << "class Crossi_Publisher {" << std::endl;
    file << "\t" << "\t" << "public:" << std::endl;
    file << "\t" << "\t" << "\t" << "Crossi_Publisher();" << std::endl;
    file << "\t" << "\t" << "\t" << "Crossi_Publisher *get_Crossi_Publisher_ptr();" << std::endl;
    file << "\t" << "\t" << "\t" << "std::map<std::string, ros::Publisher*> ros_msg_publisher;" << std::endl;
    file << "\t" << "\t" << "\t" << "std::map<std::string, void(*)(const std::string*, std::vector<float>*, Crossi_Publisher *pup)> ros_msg_functions;" << std::endl;

    file << "\t" << "\t" << "\t" << "void setup_function_map();" << std::endl;
    file << "\t" << "\t" << "\t" << "void setup_publisher_map();" << std::endl;
    file << std::endl;

    file << "\t" << "\t" << "\t" << "ros::NodeHandle node_handler;" << std::endl;
    file << std::endl;





    file << "\t" << "};" << std::endl;
    file << "}" << std::endl;
    file << std::endl;

    file << "#endif" << std::endl;

    file.close();

    return true;
}

bool dcu::Publisher_Builder::build_ros_publisher_source()
{
    std::ofstream file(*config_get_publisher_source_path(), std::ios::out | std::ios::app);
    if (!file.is_open()) return false;

    file << "#include <vector>" << std::endl;
    file << "#include <string>" << std::endl;
    file << "#include <fstream>" << std::endl;
    file << "#include <map>" << std::endl;
    file << "#include \"ros/ros.h\"" << std::endl;
    file << "#include \"crossiPublisher.h\"" << std::endl;
    file << "#include \"config.h\"" << std::endl;
    file << std::endl;

    file << "dcu::Crossi_Publisher::Crossi_Publisher()" << std::endl;
    file << "{" << std::endl;
    file << "\t" << "setup_function_map();" << std::endl;
    file << "\t" << "setup_publisher_map();" << std::endl;
    file << "}" << std::endl;
    file << std::endl;

    file << "dcu::Crossi_Publisher *dcu::Crossi_Publisher::get_Crossi_Publisher_ptr()" << std::endl;
    file << "{" << std::endl;
    file << "\t" << "return this;" << std::endl;
    file << "}" << std::endl;
    file << std::endl;


    // Create fill_ros_msg() funktion
    file << "void dcu::fill_ros_msg(void *start, float *input)" << std::endl;
    file << "{" << std::endl;
    file << "\t" << "static float *beginn = nullptr;" << std::endl;
    file << "\t" << "if (start != nullptr)" << std::endl;
    file << "\t" << "{" << std::endl;
    file << "\t" << "\t" << "beginn = (float*)start;" << std::endl;
    file << "\t" << "} else {" << std::endl;
    file << "\t" << "\t" << "*beginn = *input;" << std::endl;
    file << "\t" << "\t" << "beginn++;" << std::endl;
    file << "\t" << "}" << std::endl;
    file << "}" << std::endl;
    file << std::endl;


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

    return true;
}