#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <functional>
#include <sstream>
#include <iostream>
#include <iterator>

#include "fileHasher.h"

dcu::File_Hasher::File_Hasher(std::vector<std::string> *files, std::string *file) :
        files(files), change_file(file)
{

}

bool dcu::File_Hasher::changes_notified()
{
    std::size_t hash = 0;
    std::size_t last_hash = 0;

    for (auto i : *files)
    {
        hash = hash_file(&i);
        last_hash = read_hash_from_file(change_file, &i);
        if (!cmp_hash(&hash, &last_hash)) files_changed = true;
        file_hash.push_back(hash);
    }

    if (files_changed)
    {
        update_hash(change_file, &file_hash, files);
    }

    print_hash("Hashes:", &file_hash);

    delete files;

    return this->files_changed;
}

std::size_t dcu::File_Hasher::hash_file(std::string *path)
{
    std::fstream file(*path, std::ios::in | std::ios::out | std::ios::app);
    if (!file.is_open())
    {
        std::cerr << "ERROR in hash_file(): Can't open file: " << *path << std::endl;
        exit(-1);
    }

    std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

    file.close();

    return std::hash<std::string>{}(content);
}

std::size_t dcu::File_Hasher::read_hash_from_file(std::string *conf_path, std::string *file_path)
{
    std::ifstream file(*conf_path);
    if (!file.is_open())
    {
        std::cerr << "ERROR in hash_file(): Can't open file: " << *conf_path << std::endl;
        exit(-1);
    }

    std::istream_iterator<std::string> iter(file);
    std::istream_iterator<std::string> end;

    std::stringstream ss;
    std::size_t ret = 0;
    

    while(iter != end)
    {
        

        if (*iter == *file_path)
        {
            iter++;

            if (*iter == "=")
            {
                iter++;

                if (is_string_digit(&(*iter)))
                {
                    ss << *iter;
                    ss >> ret;
                    ss.clear();
                    return ret;
                }
            }
        }

        iter++;
    }

    file.close();

    return 0;
}

bool dcu::File_Hasher::is_string_digit(const std::string *str)
{
    if (str->empty()) return false;
    for (auto &i : *str)
    {
        if (!isdigit(i)) return false;
    }
    return true;
}

bool dcu::File_Hasher::cmp_hash(std::size_t *hash_1, std::size_t *hash_2)
{
    return (*hash_1 == *hash_2) ? true : false;
}

void dcu::File_Hasher::update_hash(std::string *path, std::vector<std::size_t> *file_hash_ptr, std::vector<std::string> *file_ptr)
{
    std::fstream erase(*path, std::ofstream::trunc);
    erase.close();

    std::ofstream file(*path, std::ios::out);
    if (!file.is_open())
    {
        std::cerr << "ERROR in hash_file(): Can't open file: " << *path << std::endl;
        exit(-1);
    }
    
    for (int i = 0; i < file_ptr->size(); i++)
    {
        file << file_ptr->at(i) << " = " << file_hash_ptr->at(i) << std::endl;
    }

    file.close();
}

void dcu::File_Hasher::print_hash(std::string msg, std::vector<std::size_t> *hash)
{
    std::cout << "\t FILE_HASCHER" << std::endl;
    for (auto &i : this->file_hash)
    {
        std::cout << "-> " << msg << " " << i << std::endl;
    }

    std::cout << std::endl;
}

