#include <iostream>

#include <fstream>
#include <iostream>
#include <vector>

#include "Fixed.h"

dcu::Fixed::Fixed() {}

dcu::Fixed::~Fixed() {}

void dcu::Fixed::init_file(std::string file_path, std::string start_pattern, std::string end_pattern)
{
    this->file_path = file_path;
    this->start_pattern = start_pattern;
    this->end_pattern = end_pattern;

    if (!input_file())
    {
        std::cerr << "Error in input_file()" << std::endl;
        exit(-1);
    }
}

void dcu::Fixed::init_file(std::string file_path)
{
    this->file_path = file_path;
    this->start_pattern = "//START_CUSTOM_AREA";
    this->end_pattern = "//END_CUSTOM_AREA";

    if (!input_file())
    {
        std::cerr << "Error in input_file()" << std::endl;
        exit(-1);
    }
}

bool dcu::Fixed::input_file()
{
    std::ifstream file(this->file_path, std::ios::in);
    if (!file.is_open()) return false;

    std::string line;
    int area_count = 0;
    std::streampos prev_pos;

    while(std::getline(file, line))
    {
        fixed_area_entry.push_back(0);

    

        do
        {
            custom_area[area_count].push_back(line);
            fixed_area_entry[area_count]++;
            if (line.find(start_pattern) != std::string::npos) break;
        } while (line != start_pattern && std::getline(file, line));
        area_count++;

        do
        {
            prev_pos = file.tellg();
            if (line.find(end_pattern) != std::string::npos)
            {
                
                custom_area[area_count].push_back(line);
                break;
            }
        } while (std::getline(file, line));

        file.seekg(prev_pos);
        

    }

    file.close();

    return true;
}

void dcu::Fixed::print_custom_area()
{
    for (int i = 0; i < custom_area.size(); i++)
    {
        for (auto i : custom_area[i])
        {
            std::cout << i << std::endl;
        }
        std::cout << "---" << custom_area[i].size() << "---" << std::endl;
    }

    std::cout << std::endl;
}

std::vector<std::string> *dcu::Fixed::get_vec()
{
    return (custom_area.size() > output_start) ? &custom_area[output_start++] : nullptr;  
}

void dcu::Fixed::reset()
{
    output_start = 0;
}

bool dcu::Fixed::check_vec(std::vector<std::string> *input)
{
    return (input == nullptr) ? false : true;
}

void dcu::Fixed::print()
{
    std::vector<std::string> *input;
    while(check_vec(input = get_vec()))
    {
        for(auto i : *input)
        {
            std::cout << i << std::endl;
        }
    }
}

bool dcu::Fixed::erase_file(std::string *path)
{
    std::ofstream file(*path, std::ios::out | std::ios::trunc);
    if (!file.is_open()) return false;

    file.clear();
    file.close();

    return true;
}