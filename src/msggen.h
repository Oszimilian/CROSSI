#ifndef MSGGEN_H
#define MSGGEN_H

#include <vector>
#include <fstream>

#define DEFAULT_DBC_CHANGE_PATH "../config/dbc_change.txt"
#define DBC_HASH "dbc_hash:"


namespace dcu
{
    class DCU_Handler;

    class Msggen
    {
        public:
            Msggen(DCU_Handler *handler);

        private:
        
            DCU_Handler *handler;

            std::map<int, std::size_t> dbc_hash_value;
            std::map<int, std::size_t> dbc_last_hash_value;

            bool update_all = true;

            void get_dbc_hash_value();
            void get_dbc_last_hash();
            std::fstream *open_file(std::string path, std::string mode);
            void *close_file(std::fstream *file);
            bool is_string_digit(std::string *str);
            void print_hash_values(std::map<int, std::size_t> *hash);
            void compare_hash_value();
            void update_hash_value();
            void print_info();
    };
}

#endif