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
            
            
            bool delete_publisher();
            bool build_ros_publisher_header();
            bool build_ros_publisher_source();

    };
}


#endif