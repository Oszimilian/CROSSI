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

            void analyse_file_with_filter(std::string *file_path, std::string filter_1, std::string filter_2);

    };
}


#endif