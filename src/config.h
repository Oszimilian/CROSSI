#ifndef CONFIG_H
#define CONFIG_H

#include <fstream>
#include <string>
#include <map>
#include <vector>

#define DEFAULT_CONFIG_PATH "../config/config.txt"

#define CAN_SETUP "Setup_Can"
#define IMPORT_DBC "Import_DBC"
#define CAPTURE_MODE "Capture_Mode"
#define DECODE_MODE "Decode_Mode"

namespace dcu
{
    class Config
    {
        public:
            Config(int argc, char **argv);
            ~Config();



            const struct Channel_Config *get_config(int channel);
            void config_print(int n);

            std::string config_get_socketname(int socket);
            std::string config_get_dbc_path(int socket);
            std::string config_get_capture_mode(int socket);
            std::string config_get_decode_mode(int socket);
            int config_get_can_count();

            std::vector<std::string> *config_get_socketnames();
            std::vector<std::string> *config_get_pathnames();

        private:

            struct Channel_Config
            {
                std::string socket_name;
                std::string dbc_path;
                std::string capture_mode;
                std::string decode_mode;
            };

            std::map<int, struct Channel_Config*> dcu_config_params;
            std::ifstream *dcu_config_file;
            std::string dcu_config_file_path;
            int can_amount;

            bool check_dcu_config_file(int argc, char **argv);
            bool open_dcu_config_file();
            void close_dcu_config_file();
            bool analyse_dcu_config_file();

            template<typename T>
            void handle_dcu_config_error(T input);

    };
}


#endif