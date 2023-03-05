#ifndef FILE_HASHER
#define FILE_HASHER

#include <iostream>
#include <string>
#include <map>
#include <vector>

namespace dcu
{
    class File_Hasher
    {
        public:
            File_Hasher(std::vector<std::string> *files, std::string file);
            std::vector<int> get_updated_file();

        private:
            bool files_changed = false;
            std::vector<std::size_t> file_hash;

            std::size_t hash_file(std::string *path);
            std::size_t read_hash_from_file(std::string *path, std::string *file_path);
            bool is_string_digit(const std::string *str);
            void print_hash(std::string msg, std::vector<std::size_t> *hash);
            bool cmp_hash(std::size_t *hash_1, std::size_t *hash_2);
            void update_hash(std::string *path, std::vector<std::size_t> *file_hash_ptr, std::vector<std::string> *file_ptr);
    };
}

#endif