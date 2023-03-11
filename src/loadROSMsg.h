#ifndef LOAD_ROS_MSG_H
#define LOAD_ROS_MSG_H

#include <string.h>
#include "config.h"

namespace dcu
{
    class Load_ROS_Msg : virtual public Config
    {
        public:
            Load_ROS_Msg();


            void update_ros_msg_files_in_cmake(std::vector<std::string> *ros_msg_ptr);

        private:
            std::vector<std::string> *ros_msg_ptr = nullptr;

            std::vector<std::string> cmake_file;
            std::size_t cmake_insert_point = 0;
            void read_old_ros_msg_cmake(const std::string *start, const std::string *end);
            void delete_old_ros_msg_cmake();
            void print_new_cmake_file();
            void create_new_ros_msg_in_cmake();
            bool check_cmake_file(const std::string *start, const std::string *end);
            
    };
}

#endif