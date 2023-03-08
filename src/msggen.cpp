#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <functional>
#include <sstream>
#include <iostream>

#include "fileHasher.h"
#include "msgBuilder.h"
#include "dcu.h"

dcu::Msggen::Msggen(dcu::DCU_Handler *handler) : 
        handler(handler), 
        File_Hasher(handler->config_get_pathnames(), DEFAULT_DBC_CHANGE_PATH),
        Msg_Builder(handler->config_get_pathnames(), handler)
{
    if (changes_notified()) std::cout << "Changes in .dbc-Files notified" << std::endl;

}





void dcu::Msggen::analyse_dbc_file(int n)
{
    std::ifstream file(handler->config_get_dbc_path(n));

    std::istream_iterator<std::string> iter(file);
    std::istream_iterator<std::string> end;

    while(iter++ != end)
    {
        if (*iter == "BO_") get_dbc_can_message(&iter, &end, "BO_", "SG_");

    }

    std::cout << std::endl;


    file.close();
}


void dcu::Msggen::get_dbc_can_message(std::istream_iterator<std::string> *iter, std::istream_iterator<std::string> *end, std::string filter_1, std::string filter_2)
{

    std::cout << std::endl;

    do
    {
        std::cout << **iter << " ";
        (*iter)++;
    } while ((**iter != filter_2) && (*iter != *end));
    

    while((**iter != filter_1) && (*iter != *end))
    {
        get_dbc_can_submessage(iter, end, filter_1, filter_2);
    }
    

}

void dcu::Msggen::get_dbc_can_submessage(std::istream_iterator<std::string> *iter, std::istream_iterator<std::string> *end, std::string filter_1, std::string filter_2)
{
    std::cout << std::endl << "\t";
    
    int count = 0;

    do
    {
        std::cout << **iter << " ";
        (*iter)++;

        if (count == 2)
        {
            std::cout << " " << get_data_typ(**iter) << " ";
        }

        count++;
    } while ((**iter != filter_1) && (**iter != filter_2) && (*iter != *end));
    
}

char* dcu::Msggen::get_data_typ(std::string data)
{
    std::string str = data.substr(data.find("|") + 1, data.find("@") - data.find("|") - 1);

    if (str == "1") return "bool";
    else if (str == "8") return "uint8_t";
    else if (str == "16") return "uint16_t";

}
