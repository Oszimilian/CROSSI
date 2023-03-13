#ifndef HEADER_BUILDER_H
#define HEADER_BUILDER_H

#include <vector>
#include <string>
#include "config.h"
#include "Fixed.h"

namespace dcu
{
    class Header_Builder : virtual public Config
    {
        public:
            Header_Builder();
            ~Header_Builder();

            void update_ros_msg_header(std::vector<std::string> *ros_msg);
            std::string get_header_name();
            void print_info();

        private:

            std::vector<std::string> *ros_msg_vec_ptr;
            Fixed *fixed_space;


            bool delete_ros_msg_header();
            bool build_ros_msg_header();


    };
}

#endif