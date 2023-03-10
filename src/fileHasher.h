#ifndef FILE_HASHER
#define FILE_HASHER

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include "config.h"

namespace dcu
{


    class File_Hasher : virtual public Config
    {
        public:
            File_Hasher();
            bool changes_notified();

        private:
            bool files_changed = false;
            std::vector<std::size_t> file_hash;
            std::vector<std::string> *files;
            std::string *change_file;

            std::size_t hash_file(std::string *path);
            std::size_t read_hash_from_file(std::string *path, std::string *file_path);
            bool is_string_digit(const std::string *str);
            void print_hash(std::string msg, std::vector<std::size_t> *hash);
            bool cmp_hash(std::size_t *hash_1, std::size_t *hash_2);
            void update_hash(std::string *path, std::vector<std::size_t> *file_hash_ptr, std::vector<std::string> *file_ptr);
    };
}

#endif