#ifndef CROOSI_PUBLISHER_H
#define CROOSI_PUBLISHER_H

#include <map>
#include "ros/ros.h"
#include "ros_msg_header.h"

namespace dcu {
	class Crossi_Publisher;

	//START_CUSTOM_AREA
	void charger_Signals(const std::string* str, std::vector<float> *input, Crossi_Publisher *pup);
	void IMD(const std::string* str, std::vector<float> *input, Crossi_Publisher *pup);
	void charge_EN(const std::string* str, std::vector<float> *input, Crossi_Publisher *pup);
	void BMS_Debug(const std::string* str, std::vector<float> *input, Crossi_Publisher *pup);
	void LTCTemp_Part2(const std::string* str, std::vector<float> *input, Crossi_Publisher *pup);
	void LTCTemp_Part1(const std::string* str, std::vector<float> *input, Crossi_Publisher *pup);
	void Stack12_Temp07_12(const std::string* str, std::vector<float> *input, Crossi_Publisher *pup);
	void Stack12_Temp01_06(const std::string* str, std::vector<float> *input, Crossi_Publisher *pup);
	void Stack11_Temp07_12(const std::string* str, std::vector<float> *input, Crossi_Publisher *pup);
	void Stack11_Temp01_06(const std::string* str, std::vector<float> *input, Crossi_Publisher *pup);
	void Stack10_Temp07_12(const std::string* str, std::vector<float> *input, Crossi_Publisher *pup);
	void Stack10_Temp01_06(const std::string* str, std::vector<float> *input, Crossi_Publisher *pup);
	void Stack09_Temp07_12(const std::string* str, std::vector<float> *input, Crossi_Publisher *pup);
	void Stack09_Temp01_06(const std::string* str, std::vector<float> *input, Crossi_Publisher *pup);
	void Stack08_Temp07_12(const std::string* str, std::vector<float> *input, Crossi_Publisher *pup);
	void Stack08_Temp01_06(const std::string* str, std::vector<float> *input, Crossi_Publisher *pup);
	void Stack07_Temp07_12(const std::string* str, std::vector<float> *input, Crossi_Publisher *pup);
	void Stack07_Temp01_06(const std::string* str, std::vector<float> *input, Crossi_Publisher *pup);
	void Stack06_Temp07_12(const std::string* str, std::vector<float> *input, Crossi_Publisher *pup);
	void Stack06_Temp01_06(const std::string* str, std::vector<float> *input, Crossi_Publisher *pup);
	void Stack05_Temp07_12(const std::string* str, std::vector<float> *input, Crossi_Publisher *pup);
	void Stack05_Temp01_06(const std::string* str, std::vector<float> *input, Crossi_Publisher *pup);
	void Stack04_Temp07_12(const std::string* str, std::vector<float> *input, Crossi_Publisher *pup);
	void Stack04_Temp01_06(const std::string* str, std::vector<float> *input, Crossi_Publisher *pup);
	void Stack03_Temp07_12(const std::string* str, std::vector<float> *input, Crossi_Publisher *pup);
	void Stack03_Temp01_06(const std::string* str, std::vector<float> *input, Crossi_Publisher *pup);
	void Stack02_Temp07_12(const std::string* str, std::vector<float> *input, Crossi_Publisher *pup);
	void Stack02_Temp01_06(const std::string* str, std::vector<float> *input, Crossi_Publisher *pup);
	void Stack01_Temp07_12(const std::string* str, std::vector<float> *input, Crossi_Publisher *pup);
	void Stack01_Temp01_06(const std::string* str, std::vector<float> *input, Crossi_Publisher *pup);
	void Stack12_Cell09_12(const std::string* str, std::vector<float> *input, Crossi_Publisher *pup);
	void Stack12_Cell05_08(const std::string* str, std::vector<float> *input, Crossi_Publisher *pup);
	void Stack12_Cell01_04(const std::string* str, std::vector<float> *input, Crossi_Publisher *pup);
	void Stack11_Cell09_12(const std::string* str, std::vector<float> *input, Crossi_Publisher *pup);
	void Stack11_Cell05_08(const std::string* str, std::vector<float> *input, Crossi_Publisher *pup);
	void Stack11_Cell01_04(const std::string* str, std::vector<float> *input, Crossi_Publisher *pup);
	void Stack10_Cell09_12(const std::string* str, std::vector<float> *input, Crossi_Publisher *pup);
	void Stack10_Cell05_08(const std::string* str, std::vector<float> *input, Crossi_Publisher *pup);
	void Stack10_Cell01_04(const std::string* str, std::vector<float> *input, Crossi_Publisher *pup);
	void Stack09_Cell09_12(const std::string* str, std::vector<float> *input, Crossi_Publisher *pup);
	void Stack09_Cell05_08(const std::string* str, std::vector<float> *input, Crossi_Publisher *pup);
	void Stack09_Cell01_04(const std::string* str, std::vector<float> *input, Crossi_Publisher *pup);
	void Stack08_Cell09_12(const std::string* str, std::vector<float> *input, Crossi_Publisher *pup);
	void Stack08_Cell05_08(const std::string* str, std::vector<float> *input, Crossi_Publisher *pup);
	void Stack08_Cell01_04(const std::string* str, std::vector<float> *input, Crossi_Publisher *pup);
	void Stack07_Cell09_12(const std::string* str, std::vector<float> *input, Crossi_Publisher *pup);
	void Stack07_Cell05_08(const std::string* str, std::vector<float> *input, Crossi_Publisher *pup);
	void Stack07_Cell01_04(const std::string* str, std::vector<float> *input, Crossi_Publisher *pup);
	void Stack06_Cell09_12(const std::string* str, std::vector<float> *input, Crossi_Publisher *pup);
	void Stack06_Cell05_08(const std::string* str, std::vector<float> *input, Crossi_Publisher *pup);
	void Stack06_Cell01_04(const std::string* str, std::vector<float> *input, Crossi_Publisher *pup);
	void Stack05_Cell09_12(const std::string* str, std::vector<float> *input, Crossi_Publisher *pup);
	void Stack05_Cell05_08(const std::string* str, std::vector<float> *input, Crossi_Publisher *pup);
	void Stack05_Cell01_04(const std::string* str, std::vector<float> *input, Crossi_Publisher *pup);
	void Stack04_Cell09_12(const std::string* str, std::vector<float> *input, Crossi_Publisher *pup);
	void Stack04_Cell05_08(const std::string* str, std::vector<float> *input, Crossi_Publisher *pup);
	void Stack04_Cell01_04(const std::string* str, std::vector<float> *input, Crossi_Publisher *pup);
	void Stack03_Cell09_12(const std::string* str, std::vector<float> *input, Crossi_Publisher *pup);
	void Stack03_Cell05_08(const std::string* str, std::vector<float> *input, Crossi_Publisher *pup);
	void Stack03_Cell01_04(const std::string* str, std::vector<float> *input, Crossi_Publisher *pup);
	void Stack02_Cell09_12(const std::string* str, std::vector<float> *input, Crossi_Publisher *pup);
	void Stack02_Cell05_08(const std::string* str, std::vector<float> *input, Crossi_Publisher *pup);
	void Stack02_Cell01_04(const std::string* str, std::vector<float> *input, Crossi_Publisher *pup);
	void Stack01_Cell09_12(const std::string* str, std::vector<float> *input, Crossi_Publisher *pup);
	void Stack01_Cell05_08(const std::string* str, std::vector<float> *input, Crossi_Publisher *pup);
	void Stack01_Cell01_04(const std::string* str, std::vector<float> *input, Crossi_Publisher *pup);
	void VECTOR__INDEPENDENT_SIG_MSG(const std::string* str, std::vector<float> *input, Crossi_Publisher *pup);
	void BMaS_Commands(const std::string* str, std::vector<float> *input, Crossi_Publisher *pup);
	void Cell_Temp_Info(const std::string* str, std::vector<float> *input, Crossi_Publisher *pup);
	void Cell_Voltage_Info(const std::string* str, std::vector<float> *input, Crossi_Publisher *pup);
	void BMaS_Status(const std::string* str, std::vector<float> *input, Crossi_Publisher *pup);
	void IVT_Msg_Result_Wh(const std::string* str, std::vector<float> *input, Crossi_Publisher *pup);
	void IVT_Msg_Result_U2(const std::string* str, std::vector<float> *input, Crossi_Publisher *pup);
	void IVT_Msg_Result_U1(const std::string* str, std::vector<float> *input, Crossi_Publisher *pup);
	void IVT_Msg_Result_I(const std::string* str, std::vector<float> *input, Crossi_Publisher *pup);
	//END_CUSTOM_AREA

	void fill_ros_msg(void *start, float *input);

	class Crossi_Publisher {
		public:
			Crossi_Publisher();
			Crossi_Publisher *get_Crossi_Publisher_ptr();
			std::map<std::string, ros::Publisher*> ros_msg_publisher;
			std::map<std::string, void(*)(const std::string*, std::vector<float>*, Crossi_Publisher *pup)> ros_msg_functions;
			void setup_function_map();
			void setup_publisher_map();

			ros::NodeHandle node_handler;

	};
}

#endif





