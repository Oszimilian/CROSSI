#ifndef MSGGEN_H
#define MSGGEN_H

#include <vector>
#include <fstream>
#include <map>
#include <iterator>
#include <algorithm>

#include "fileHasher.h"
#include "msgBuilder.h"

#define DEFAULT_DBC_CHANGE_PATH "../config/dbc_change.txt"
#define DBC_HASH "dbc_hash:"


namespace dcu
{
    class DCU_Handler;

    class Msggen : public File_Hasher, public Msg_Builder
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
            void analyse_dbc_file(int n);
            void get_dbc_can_message(std::istream_iterator<std::string> *iter, std::istream_iterator<std::string> *end, std::string filter_1, std::string filter_2);
            void get_dbc_can_submessage(std::istream_iterator<std::string> *iter, std::istream_iterator<std::string> *end, std::string filter_1, std::string filter_2);
            char* get_data_typ(std::string data);
    };
}

#endif