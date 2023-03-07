#ifndef MSGBUILDER_H
#define MSGBUILDER_H

#include <string>
#include <vector>

namespace dcu
{
    class Msg_Builder
    {
        public:
            Msg_Builder(std::vector<std::string> *file_paths);

        private:
            std::vector<std::string> *file_paths;

            enum ROS_MSG_TYP {
                ros_bool,
                ros_uint8_t,
                ros_uint16_t,
            };

            void analyse_file_with_filter(std::string *file_path, std::string filter_1, std::string filter_2);
            int get_datatyp(std::string *str);
            

    };
}


#endif