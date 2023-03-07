#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <iostream>
#include <iterator>

#include "msgBuilder.h"

dcu::Msg_Builder::Msg_Builder(std::vector<std::string> *file_paths) :
    file_paths(file_paths)
{
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

    
    while(std::getline(file, line))
    {
        
        iss.clear();
        iss.str(line);
        iter = std::istream_iterator<std::string>(iss);

        if (*iter == filter_1)
        {
            do
            {
                std::cout << *iter << " ";
                iter++;
            } while ( (*iter != filter_2) && (iter != end));
            std::cout << std::endl;
        }

        if (*iter == filter_2)   
        {
            std::cout << "\t";
            do
            {
                std::cout << *iter << " ";
                iter++;
            } while( (*iter != filter_1) && (*iter != filter_2) && (iter != end));
            std::cout << std::endl;
        }
        
    }

    file.close();
}

int dcu::Msg_Builder::get_datatyp(std::string *str)
{
    std::string datatyp = str->substr( (str->find("|") + 1), (str->find("@") - str->find("|") - 1));

    if (datatyp == "1") return ros_bool;
    else if (datatyp == "8") return ros_uint8_t;
    else if (datatyp == "16") return ros_uint16_t;
    else return -1;
}