#ifndef FIXED_H
#define FIXED_H


#include <string>
#include <vector>
#include <map>

namespace dcu
{
    class Fixed
    {
        public:
            Fixed();
            ~Fixed();


            void init_file(std::string file, std::string start_pattern, std::string end_pattern);
            void init_file(std::string file);
            std::vector<std::string> *get_vec();
            void reset();
            bool check_vec(std::vector<std::string> *input);
            void print();

        private:
            std::string file_path;
            std::string start_pattern;
            std::string end_pattern;
            int output_start = 0;

            std::map<int, std::vector<std::string>> custom_area;
            std::vector<int> fixed_area_entry;

            bool input_file();
            void print_custom_area();

    };
}


#endif