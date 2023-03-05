#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <functional>
#include <sstream>
#include <iostream>

#include "fileHasher.h"
#include "dcu.h"

dcu::Msggen::Msggen(dcu::DCU_Handler *handler) : handler(handler), 
    File_Hasher(handler->config_get_pathnames(), DEFAULT_DBC_CHANGE_PATH)
{
    //get_dbc_hash_value();
    
    //get_dbc_last_hash();

    //compare_hash_value();

    //analyse_dbc_file(0);

    //print_info();

}






void dcu::Msggen::get_dbc_hash_value()
{
    

    for (int i = 0; i < handler->config_get_can_count(); i++)
    {
        std::fstream *file = open_file(handler->config_get_dbc_path(i), "R"); 

        std::string content((std::istreambuf_iterator<char>(*file)), std::istreambuf_iterator<char>());
        dbc_hash_value.insert(std::make_pair(i ,std::hash<std::string>{}(content) ));

        close_file(file);
    }

    
}


std::fstream *dcu::Msggen::open_file(std::string path, std::string mode)
{
    std::fstream *file;

    if (mode == "R")
    {
        file = new std::fstream(path, std::ios::in);
    }
    else if (mode == "R+")
    {
        file = new std::fstream(path, std::ios::in | std::ios::app);
    }
    else if(mode == "W")
    {
        file = new std::fstream(path, std::ios::out);
    }
    else if(mode == "W+")
    {
        file = new std::fstream(path, std::ios::out | std::ios::app);
    }
    else if(mode == "RW+")
    {
        file = new std::fstream(path, std::ios::out | std::ios::app | std::ios::in);
    }
    else if(mode == "L")
    {
        file = new std::fstream(path, std::ofstream::trunc);
    }

    if (file == nullptr)
    {
        std::cerr << "Error in open file: " << path << std::endl;
        exit(-1);
    }

    return file;
}

void *dcu::Msggen::close_file(std::fstream *file)
{
    file->close();
}


void dcu::Msggen::get_dbc_last_hash()
{
    std::fstream *file = open_file(DEFAULT_DBC_CHANGE_PATH, "RW+");
    std::string str;
    int id;
    std::stringstream ss;
    std::string pattern;

    std::size_t value;

    while (std::getline(*file, str))
    {
        if (str.empty()) continue;

        pattern = str.substr(str.find("(") + 1, str.find(")") - str.find("(") - 1);
        if(is_string_digit(&pattern))
        {
            ss << pattern;
            ss >> id;
            ss.clear();
        } else {
            std::cerr << "ERROR in getting the latest hash-value" << std::endl;
            exit(-1);
        }


        pattern = str.substr(str.find("=") + 1, str.size() - 1 - str.find("="));
        if (is_string_digit(&pattern))
        {
            ss << pattern;
            ss >> value;
            dbc_last_hash_value.insert(std::make_pair(id, value));
            ss.clear();
        }

    }

    close_file(file);

    if (dbc_last_hash_value.size() < handler->config_get_can_count())
    {
        std::fstream *file = open_file(DEFAULT_DBC_CHANGE_PATH, "L");

        for (int i = 0; i < handler->config_get_can_count(); i++)
        {
            *file << "hash_value(" << i << ") =" << 0 << std::endl;
            dbc_last_hash_value.insert(std::make_pair(i, 0));
        }

        close_file(file);
    }

    
    
    
}

bool dcu::Msggen::is_string_digit(std::string *str)
{
    if (str->empty()) return false;
    for (auto &i : *str)
    {
        if (!isdigit(i)) return false;
    }
    return true;
}

void dcu::Msggen::print_hash_values(std::map<int, std::size_t> *hash)
{
    for (auto i : *hash)
    {
        std::cout << "ID: "<<  i.first << " Hashvalue: " <<  i.second << std::endl;
    }
}

void dcu::Msggen::compare_hash_value()
{
    for (int i = 0; i < handler->config_get_can_count(); i++)
    {
        if (dbc_hash_value.at(i) != dbc_last_hash_value.at(i))
        {
            this->update_all = false;
        }
    }

    if (this->update_all == false)
    {
        update_hash_value();
    }
}

void dcu::Msggen::update_hash_value()
{
    std::fstream *file = open_file(DEFAULT_DBC_CHANGE_PATH, "W");

    for (int i = 0; i < handler->config_get_can_count(); i++)
    {
        *file << "hash_value(" << i << ") =" << dbc_hash_value.at(i) << std::endl;
    }
    

    close_file(file);
}

void dcu::Msggen::print_info()
{
    std::cout << "\t MSGGEN:" << std::endl;
    print_hash_values(&dbc_hash_value);
    print_hash_values(&dbc_last_hash_value);
    
    if (!this->update_all)
    {
        std::cout << "Hashvalue has been updated! " << std::endl;
    }

    std::cout << std::endl;
}

void dcu::Msggen::analyse_dbc_file(int n)
{
    std::ifstream file(handler->config_get_dbc_path(n));

    std::istream_iterator<std::string> iter(file);
    std::istream_iterator<std::string> end;

    while(iter++ != end)
    {
        if (*iter == "BO_") get_dbc_can_message(&iter, &end, "BO_", "SG_");

    }

    std::cout << std::endl;


    file.close();
}


void dcu::Msggen::get_dbc_can_message(std::istream_iterator<std::string> *iter, std::istream_iterator<std::string> *end, std::string filter_1, std::string filter_2)
{

    std::cout << std::endl;

    do
    {
        std::cout << **iter << " ";
        (*iter)++;
    } while ((**iter != filter_2) && (*iter != *end));
    

    while((**iter != filter_1) && (*iter != *end))
    {
        get_dbc_can_submessage(iter, end, filter_1, filter_2);
    }
    

}

void dcu::Msggen::get_dbc_can_submessage(std::istream_iterator<std::string> *iter, std::istream_iterator<std::string> *end, std::string filter_1, std::string filter_2)
{
    std::cout << std::endl << "\t";
    
    int count = 0;

    do
    {
        std::cout << **iter << " ";
        (*iter)++;

        if (count == 2)
        {
            std::cout << " " << get_data_typ(**iter) << " ";
        }

        count++;
    } while ((**iter != filter_1) && (**iter != filter_2) && (*iter != *end));
    
}

char* dcu::Msggen::get_data_typ(std::string data)
{
    std::string str = data.substr(data.find("|") + 1, data.find("@") - data.find("|") - 1);

    if (str == "1") return "bool";
    else if (str == "8") return "uint8_t";
    else if (str == "16") return "uint16_t";

}
