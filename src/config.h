#ifndef CONFIG_H
#define CONFIG_H

#include <fstream>
#include <string>
#include <map>
#include <vector>

#define DEFAULT_CONFIG_PATH "../config/crossi_config.txt"

#define CAN_AMOUNT "Can_Amount"
#define CAN_SETUP "Setup_Can"
#define IMPORT_DBC "Import_DBC"
#define CAPTURE_MODE "Capture_Mode"
#define DECODE_MODE "Decode_Mode"
#define ROS_MSG_DIR "Ros_Msg_Dir"
#define DBC_MSG_IGN "DBC_Msg_Ignore"
#define FORCE_MSG_GEN "Force_Msg_Gen"

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

            bool config_validate_dbc_msg(int socket, const std::string *dbc_msg);

            int config_get_socket_from_path(std::string dbc_path_local);
            bool config_get_ros_msg_force();

        private:

            struct Channel_Config
            {
                std::string socket_name;
                std::string dbc_path;
                std::string capture_mode;
                std::string decode_mode;
                std::string ros_msg_dir;

                std::map<std::string, std::string> dbc_msg_ignore;
            };

            std::map<int, struct Channel_Config*> dcu_config_params;
            std::ifstream *dcu_config_file;
            std::string dcu_config_file_path;
            int can_amount;
            bool ros_msg_force = false;

            bool check_dcu_config_file(int argc, char **argv);
            bool open_dcu_config_file();
            void close_dcu_config_file();
            bool analyse_dcu_config_file();
            bool analyse_crossi_config_file();

            bool is_string_digit(const std::string *str);
            int get_channel(const std::string *str);
            void handle_load_error(int *n,std::string str);
            void handle_load_error(const std::string *c, std::string str);

            template<typename T>
            void handle_dcu_config_error(T input);

    };
}


#endif