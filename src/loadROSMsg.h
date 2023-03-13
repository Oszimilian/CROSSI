#ifndef LOAD_ROS_MSG_H
#define LOAD_ROS_MSG_H

#include <string.h>
#include "config.h"
#include "Fixed.h"

namespace dcu
{
    class Load_ROS_Msg : virtual public Config
    {
        public:
            Load_ROS_Msg();


            void update_ros_msg_files_in_cmake(std::vector<std::string> *ros_msg_ptr);

        private:
            std::vector<std::string> *ros_msg_ptr = nullptr;
            Fixed *fixed_area;

            bool delete_old_ros_msg_cmake();
            bool create_new_ros_msg_in_cmake();
             
    };
}

#endif