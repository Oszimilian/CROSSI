#ifndef CROSSI_PUBLISHER_H
#define CROSSI_PUBLISHER_H

#include <string>
#include <vector>
#include "config.h"
#include "crossiPublisher.h"
#include "Fixed.h"

namespace dcu
{
    class Publisher_Builder : virtual public Config
    {
        public:
            Publisher_Builder();
            ~Publisher_Builder();
            void update_publisher(std::vector<std::string> *ros_msg);

        private:
            Fixed *fixed_source;
            Fixed *fixed_header;

            std::vector<std::string> *ros_msg_vec_ptr;
            
            std::vector<std::string> fixed_area_source;
            std::size_t start_custom_area_source = 0;
            std::size_t end_custom_area_source = 0;

            std::vector<std::string> fixed_area_header;
            std::size_t start_custom_area_header = 0;
            std::size_t end_custom_area_header = 0;
            
            bool delete_publisher();
            bool build_ros_publisher_header();
            bool build_ros_publisher_source();
            bool save_fixed_area_source(std::string start, std::string end);
            bool save_fixed_area_header(std::string start, std::string end);
    };
}


#endif