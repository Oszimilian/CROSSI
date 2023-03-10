#ifndef MSGBUILDER_H
#define MSGBUILDER_H

#include <string>
#include <vector>
#include <fstream>

#include "config.h"

namespace dcu
{
 

    class Msg_Builder : virtual public Config
    {
        public:
            Msg_Builder();

        
            void start_creating_ros_msg();
            std::vector<std::string> *builder_get_ros_msg_vec();

        private:
            std::vector<std::string> *file_paths;

            std::vector<std::string> ros_msg;

            enum ROS_MSG_TYP {
                ros_bool,
                ros_uint8_t,
                ros_uint16_t,
            };

            void analyse_file_with_filter(std::string *file_path, std::string filter_1, std::string filter_2);
            std::ofstream *create_new_ros_msg(const std::string *msg_name);
            void close_new_ros_msg(std::ofstream *file);
            void add_ros_msg_sig(std::ofstream *file, const std::string *data_typ, const std::string *var_name);
            void init_ros_msg_folder();

            

    };
}


#endif