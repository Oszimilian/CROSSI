#include <vector>
#include <string>
#include <fstream>
#include <map>
#include "ros/ros.h"
#include "crossiPublisher.h"
#include "config.h"

dcu::Crossi_Publisher::Crossi_Publisher()
{
	setup_function_map();
	setup_publisher_map();
}

dcu::Crossi_Publisher *dcu::Crossi_Publisher::get_Crossi_Publisher_ptr()
{
	return this;
}

void dcu::fill_ros_msg(void *start, float *input)
{
	static float *beginn = nullptr;
	if (start != nullptr)
	{
		beginn = (float*)start;
	} else {
		*beginn = *input;
		beginn++;
	}
}

void dcu::Crossi_Publisher::setup_function_map()
{
	ros_msg_functions.insert(std::make_pair("charger_Signals", &charger_Signals));
	ros_msg_functions.insert(std::make_pair("IMD", &IMD));
	ros_msg_functions.insert(std::make_pair("charge_EN", &charge_EN));
	ros_msg_functions.insert(std::make_pair("BMS_Debug", &BMS_Debug));
	ros_msg_functions.insert(std::make_pair("LTCTemp_Part2", &LTCTemp_Part2));
	ros_msg_functions.insert(std::make_pair("LTCTemp_Part1", &LTCTemp_Part1));
	ros_msg_functions.insert(std::make_pair("Stack12_Temp07_12", &Stack12_Temp07_12));
	ros_msg_functions.insert(std::make_pair("Stack12_Temp01_06", &Stack12_Temp01_06));
	ros_msg_functions.insert(std::make_pair("Stack11_Temp07_12", &Stack11_Temp07_12));
	ros_msg_functions.insert(std::make_pair("Stack11_Temp01_06", &Stack11_Temp01_06));
	ros_msg_functions.insert(std::make_pair("Stack10_Temp07_12", &Stack10_Temp07_12));
	ros_msg_functions.insert(std::make_pair("Stack10_Temp01_06", &Stack10_Temp01_06));
	ros_msg_functions.insert(std::make_pair("Stack09_Temp07_12", &Stack09_Temp07_12));
	ros_msg_functions.insert(std::make_pair("Stack09_Temp01_06", &Stack09_Temp01_06));
	ros_msg_functions.insert(std::make_pair("Stack08_Temp07_12", &Stack08_Temp07_12));
	ros_msg_functions.insert(std::make_pair("Stack08_Temp01_06", &Stack08_Temp01_06));
	ros_msg_functions.insert(std::make_pair("Stack07_Temp07_12", &Stack07_Temp07_12));
	ros_msg_functions.insert(std::make_pair("Stack07_Temp01_06", &Stack07_Temp01_06));
	ros_msg_functions.insert(std::make_pair("Stack06_Temp07_12", &Stack06_Temp07_12));
	ros_msg_functions.insert(std::make_pair("Stack06_Temp01_06", &Stack06_Temp01_06));
	ros_msg_functions.insert(std::make_pair("Stack05_Temp07_12", &Stack05_Temp07_12));
	ros_msg_functions.insert(std::make_pair("Stack05_Temp01_06", &Stack05_Temp01_06));
	ros_msg_functions.insert(std::make_pair("Stack04_Temp07_12", &Stack04_Temp07_12));
	ros_msg_functions.insert(std::make_pair("Stack04_Temp01_06", &Stack04_Temp01_06));
	ros_msg_functions.insert(std::make_pair("Stack03_Temp07_12", &Stack03_Temp07_12));
	ros_msg_functions.insert(std::make_pair("Stack03_Temp01_06", &Stack03_Temp01_06));
	ros_msg_functions.insert(std::make_pair("Stack02_Temp07_12", &Stack02_Temp07_12));
	ros_msg_functions.insert(std::make_pair("Stack02_Temp01_06", &Stack02_Temp01_06));
	ros_msg_functions.insert(std::make_pair("Stack01_Temp07_12", &Stack01_Temp07_12));
	ros_msg_functions.insert(std::make_pair("Stack01_Temp01_06", &Stack01_Temp01_06));
	ros_msg_functions.insert(std::make_pair("Stack12_Cell09_12", &Stack12_Cell09_12));
	ros_msg_functions.insert(std::make_pair("Stack12_Cell05_08", &Stack12_Cell05_08));
	ros_msg_functions.insert(std::make_pair("Stack12_Cell01_04", &Stack12_Cell01_04));
	ros_msg_functions.insert(std::make_pair("Stack11_Cell09_12", &Stack11_Cell09_12));
	ros_msg_functions.insert(std::make_pair("Stack11_Cell05_08", &Stack11_Cell05_08));
	ros_msg_functions.insert(std::make_pair("Stack11_Cell01_04", &Stack11_Cell01_04));
	ros_msg_functions.insert(std::make_pair("Stack10_Cell09_12", &Stack10_Cell09_12));
	ros_msg_functions.insert(std::make_pair("Stack10_Cell05_08", &Stack10_Cell05_08));
	ros_msg_functions.insert(std::make_pair("Stack10_Cell01_04", &Stack10_Cell01_04));
	ros_msg_functions.insert(std::make_pair("Stack09_Cell09_12", &Stack09_Cell09_12));
	ros_msg_functions.insert(std::make_pair("Stack09_Cell05_08", &Stack09_Cell05_08));
	ros_msg_functions.insert(std::make_pair("Stack09_Cell01_04", &Stack09_Cell01_04));
	ros_msg_functions.insert(std::make_pair("Stack08_Cell09_12", &Stack08_Cell09_12));
	ros_msg_functions.insert(std::make_pair("Stack08_Cell05_08", &Stack08_Cell05_08));
	ros_msg_functions.insert(std::make_pair("Stack08_Cell01_04", &Stack08_Cell01_04));
	ros_msg_functions.insert(std::make_pair("Stack07_Cell09_12", &Stack07_Cell09_12));
	ros_msg_functions.insert(std::make_pair("Stack07_Cell05_08", &Stack07_Cell05_08));
	ros_msg_functions.insert(std::make_pair("Stack07_Cell01_04", &Stack07_Cell01_04));
	ros_msg_functions.insert(std::make_pair("Stack06_Cell09_12", &Stack06_Cell09_12));
	ros_msg_functions.insert(std::make_pair("Stack06_Cell05_08", &Stack06_Cell05_08));
	ros_msg_functions.insert(std::make_pair("Stack06_Cell01_04", &Stack06_Cell01_04));
	ros_msg_functions.insert(std::make_pair("Stack05_Cell09_12", &Stack05_Cell09_12));
	ros_msg_functions.insert(std::make_pair("Stack05_Cell05_08", &Stack05_Cell05_08));
	ros_msg_functions.insert(std::make_pair("Stack05_Cell01_04", &Stack05_Cell01_04));
	ros_msg_functions.insert(std::make_pair("Stack04_Cell09_12", &Stack04_Cell09_12));
	ros_msg_functions.insert(std::make_pair("Stack04_Cell05_08", &Stack04_Cell05_08));
	ros_msg_functions.insert(std::make_pair("Stack04_Cell01_04", &Stack04_Cell01_04));
	ros_msg_functions.insert(std::make_pair("Stack03_Cell09_12", &Stack03_Cell09_12));
	ros_msg_functions.insert(std::make_pair("Stack03_Cell05_08", &Stack03_Cell05_08));
	ros_msg_functions.insert(std::make_pair("Stack03_Cell01_04", &Stack03_Cell01_04));
	ros_msg_functions.insert(std::make_pair("Stack02_Cell09_12", &Stack02_Cell09_12));
	ros_msg_functions.insert(std::make_pair("Stack02_Cell05_08", &Stack02_Cell05_08));
	ros_msg_functions.insert(std::make_pair("Stack02_Cell01_04", &Stack02_Cell01_04));
	ros_msg_functions.insert(std::make_pair("Stack01_Cell09_12", &Stack01_Cell09_12));
	ros_msg_functions.insert(std::make_pair("Stack01_Cell05_08", &Stack01_Cell05_08));
	ros_msg_functions.insert(std::make_pair("Stack01_Cell01_04", &Stack01_Cell01_04));
	ros_msg_functions.insert(std::make_pair("VECTOR__INDEPENDENT_SIG_MSG", &VECTOR__INDEPENDENT_SIG_MSG));
	ros_msg_functions.insert(std::make_pair("BMaS_Commands", &BMaS_Commands));
	ros_msg_functions.insert(std::make_pair("Cell_Temp_Info", &Cell_Temp_Info));
	ros_msg_functions.insert(std::make_pair("Cell_Voltage_Info", &Cell_Voltage_Info));
	ros_msg_functions.insert(std::make_pair("BMaS_Status", &BMaS_Status));
	ros_msg_functions.insert(std::make_pair("IVT_Msg_Result_Wh", &IVT_Msg_Result_Wh));
	ros_msg_functions.insert(std::make_pair("IVT_Msg_Result_U2", &IVT_Msg_Result_U2));
	ros_msg_functions.insert(std::make_pair("IVT_Msg_Result_U1", &IVT_Msg_Result_U1));
	ros_msg_functions.insert(std::make_pair("IVT_Msg_Result_I", &IVT_Msg_Result_I));
}

void dcu::Crossi_Publisher::setup_publisher_map()
{
	ros_msg_publisher.insert(std::make_pair("charger_Signals", new ros::Publisher((node_handler.advertise<crossi::charger_Signals>("charger_Signals", 100))) ));
	ros_msg_publisher.insert(std::make_pair("IMD", new ros::Publisher((node_handler.advertise<crossi::IMD>("IMD", 100))) ));
	ros_msg_publisher.insert(std::make_pair("charge_EN", new ros::Publisher((node_handler.advertise<crossi::charge_EN>("charge_EN", 100))) ));
	ros_msg_publisher.insert(std::make_pair("BMS_Debug", new ros::Publisher((node_handler.advertise<crossi::BMS_Debug>("BMS_Debug", 100))) ));
	ros_msg_publisher.insert(std::make_pair("LTCTemp_Part2", new ros::Publisher((node_handler.advertise<crossi::LTCTemp_Part2>("LTCTemp_Part2", 100))) ));
	ros_msg_publisher.insert(std::make_pair("LTCTemp_Part1", new ros::Publisher((node_handler.advertise<crossi::LTCTemp_Part1>("LTCTemp_Part1", 100))) ));
	ros_msg_publisher.insert(std::make_pair("Stack12_Temp07_12", new ros::Publisher((node_handler.advertise<crossi::Stack12_Temp07_12>("Stack12_Temp07_12", 100))) ));
	ros_msg_publisher.insert(std::make_pair("Stack12_Temp01_06", new ros::Publisher((node_handler.advertise<crossi::Stack12_Temp01_06>("Stack12_Temp01_06", 100))) ));
	ros_msg_publisher.insert(std::make_pair("Stack11_Temp07_12", new ros::Publisher((node_handler.advertise<crossi::Stack11_Temp07_12>("Stack11_Temp07_12", 100))) ));
	ros_msg_publisher.insert(std::make_pair("Stack11_Temp01_06", new ros::Publisher((node_handler.advertise<crossi::Stack11_Temp01_06>("Stack11_Temp01_06", 100))) ));
	ros_msg_publisher.insert(std::make_pair("Stack10_Temp07_12", new ros::Publisher((node_handler.advertise<crossi::Stack10_Temp07_12>("Stack10_Temp07_12", 100))) ));
	ros_msg_publisher.insert(std::make_pair("Stack10_Temp01_06", new ros::Publisher((node_handler.advertise<crossi::Stack10_Temp01_06>("Stack10_Temp01_06", 100))) ));
	ros_msg_publisher.insert(std::make_pair("Stack09_Temp07_12", new ros::Publisher((node_handler.advertise<crossi::Stack09_Temp07_12>("Stack09_Temp07_12", 100))) ));
	ros_msg_publisher.insert(std::make_pair("Stack09_Temp01_06", new ros::Publisher((node_handler.advertise<crossi::Stack09_Temp01_06>("Stack09_Temp01_06", 100))) ));
	ros_msg_publisher.insert(std::make_pair("Stack08_Temp07_12", new ros::Publisher((node_handler.advertise<crossi::Stack08_Temp07_12>("Stack08_Temp07_12", 100))) ));
	ros_msg_publisher.insert(std::make_pair("Stack08_Temp01_06", new ros::Publisher((node_handler.advertise<crossi::Stack08_Temp01_06>("Stack08_Temp01_06", 100))) ));
	ros_msg_publisher.insert(std::make_pair("Stack07_Temp07_12", new ros::Publisher((node_handler.advertise<crossi::Stack07_Temp07_12>("Stack07_Temp07_12", 100))) ));
	ros_msg_publisher.insert(std::make_pair("Stack07_Temp01_06", new ros::Publisher((node_handler.advertise<crossi::Stack07_Temp01_06>("Stack07_Temp01_06", 100))) ));
	ros_msg_publisher.insert(std::make_pair("Stack06_Temp07_12", new ros::Publisher((node_handler.advertise<crossi::Stack06_Temp07_12>("Stack06_Temp07_12", 100))) ));
	ros_msg_publisher.insert(std::make_pair("Stack06_Temp01_06", new ros::Publisher((node_handler.advertise<crossi::Stack06_Temp01_06>("Stack06_Temp01_06", 100))) ));
	ros_msg_publisher.insert(std::make_pair("Stack05_Temp07_12", new ros::Publisher((node_handler.advertise<crossi::Stack05_Temp07_12>("Stack05_Temp07_12", 100))) ));
	ros_msg_publisher.insert(std::make_pair("Stack05_Temp01_06", new ros::Publisher((node_handler.advertise<crossi::Stack05_Temp01_06>("Stack05_Temp01_06", 100))) ));
	ros_msg_publisher.insert(std::make_pair("Stack04_Temp07_12", new ros::Publisher((node_handler.advertise<crossi::Stack04_Temp07_12>("Stack04_Temp07_12", 100))) ));
	ros_msg_publisher.insert(std::make_pair("Stack04_Temp01_06", new ros::Publisher((node_handler.advertise<crossi::Stack04_Temp01_06>("Stack04_Temp01_06", 100))) ));
	ros_msg_publisher.insert(std::make_pair("Stack03_Temp07_12", new ros::Publisher((node_handler.advertise<crossi::Stack03_Temp07_12>("Stack03_Temp07_12", 100))) ));
	ros_msg_publisher.insert(std::make_pair("Stack03_Temp01_06", new ros::Publisher((node_handler.advertise<crossi::Stack03_Temp01_06>("Stack03_Temp01_06", 100))) ));
	ros_msg_publisher.insert(std::make_pair("Stack02_Temp07_12", new ros::Publisher((node_handler.advertise<crossi::Stack02_Temp07_12>("Stack02_Temp07_12", 100))) ));
	ros_msg_publisher.insert(std::make_pair("Stack02_Temp01_06", new ros::Publisher((node_handler.advertise<crossi::Stack02_Temp01_06>("Stack02_Temp01_06", 100))) ));
	ros_msg_publisher.insert(std::make_pair("Stack01_Temp07_12", new ros::Publisher((node_handler.advertise<crossi::Stack01_Temp07_12>("Stack01_Temp07_12", 100))) ));
	ros_msg_publisher.insert(std::make_pair("Stack01_Temp01_06", new ros::Publisher((node_handler.advertise<crossi::Stack01_Temp01_06>("Stack01_Temp01_06", 100))) ));
	ros_msg_publisher.insert(std::make_pair("Stack12_Cell09_12", new ros::Publisher((node_handler.advertise<crossi::Stack12_Cell09_12>("Stack12_Cell09_12", 100))) ));
	ros_msg_publisher.insert(std::make_pair("Stack12_Cell05_08", new ros::Publisher((node_handler.advertise<crossi::Stack12_Cell05_08>("Stack12_Cell05_08", 100))) ));
	ros_msg_publisher.insert(std::make_pair("Stack12_Cell01_04", new ros::Publisher((node_handler.advertise<crossi::Stack12_Cell01_04>("Stack12_Cell01_04", 100))) ));
	ros_msg_publisher.insert(std::make_pair("Stack11_Cell09_12", new ros::Publisher((node_handler.advertise<crossi::Stack11_Cell09_12>("Stack11_Cell09_12", 100))) ));
	ros_msg_publisher.insert(std::make_pair("Stack11_Cell05_08", new ros::Publisher((node_handler.advertise<crossi::Stack11_Cell05_08>("Stack11_Cell05_08", 100))) ));
	ros_msg_publisher.insert(std::make_pair("Stack11_Cell01_04", new ros::Publisher((node_handler.advertise<crossi::Stack11_Cell01_04>("Stack11_Cell01_04", 100))) ));
	ros_msg_publisher.insert(std::make_pair("Stack10_Cell09_12", new ros::Publisher((node_handler.advertise<crossi::Stack10_Cell09_12>("Stack10_Cell09_12", 100))) ));
	ros_msg_publisher.insert(std::make_pair("Stack10_Cell05_08", new ros::Publisher((node_handler.advertise<crossi::Stack10_Cell05_08>("Stack10_Cell05_08", 100))) ));
	ros_msg_publisher.insert(std::make_pair("Stack10_Cell01_04", new ros::Publisher((node_handler.advertise<crossi::Stack10_Cell01_04>("Stack10_Cell01_04", 100))) ));
	ros_msg_publisher.insert(std::make_pair("Stack09_Cell09_12", new ros::Publisher((node_handler.advertise<crossi::Stack09_Cell09_12>("Stack09_Cell09_12", 100))) ));
	ros_msg_publisher.insert(std::make_pair("Stack09_Cell05_08", new ros::Publisher((node_handler.advertise<crossi::Stack09_Cell05_08>("Stack09_Cell05_08", 100))) ));
	ros_msg_publisher.insert(std::make_pair("Stack09_Cell01_04", new ros::Publisher((node_handler.advertise<crossi::Stack09_Cell01_04>("Stack09_Cell01_04", 100))) ));
	ros_msg_publisher.insert(std::make_pair("Stack08_Cell09_12", new ros::Publisher((node_handler.advertise<crossi::Stack08_Cell09_12>("Stack08_Cell09_12", 100))) ));
	ros_msg_publisher.insert(std::make_pair("Stack08_Cell05_08", new ros::Publisher((node_handler.advertise<crossi::Stack08_Cell05_08>("Stack08_Cell05_08", 100))) ));
	ros_msg_publisher.insert(std::make_pair("Stack08_Cell01_04", new ros::Publisher((node_handler.advertise<crossi::Stack08_Cell01_04>("Stack08_Cell01_04", 100))) ));
	ros_msg_publisher.insert(std::make_pair("Stack07_Cell09_12", new ros::Publisher((node_handler.advertise<crossi::Stack07_Cell09_12>("Stack07_Cell09_12", 100))) ));
	ros_msg_publisher.insert(std::make_pair("Stack07_Cell05_08", new ros::Publisher((node_handler.advertise<crossi::Stack07_Cell05_08>("Stack07_Cell05_08", 100))) ));
	ros_msg_publisher.insert(std::make_pair("Stack07_Cell01_04", new ros::Publisher((node_handler.advertise<crossi::Stack07_Cell01_04>("Stack07_Cell01_04", 100))) ));
	ros_msg_publisher.insert(std::make_pair("Stack06_Cell09_12", new ros::Publisher((node_handler.advertise<crossi::Stack06_Cell09_12>("Stack06_Cell09_12", 100))) ));
	ros_msg_publisher.insert(std::make_pair("Stack06_Cell05_08", new ros::Publisher((node_handler.advertise<crossi::Stack06_Cell05_08>("Stack06_Cell05_08", 100))) ));
	ros_msg_publisher.insert(std::make_pair("Stack06_Cell01_04", new ros::Publisher((node_handler.advertise<crossi::Stack06_Cell01_04>("Stack06_Cell01_04", 100))) ));
	ros_msg_publisher.insert(std::make_pair("Stack05_Cell09_12", new ros::Publisher((node_handler.advertise<crossi::Stack05_Cell09_12>("Stack05_Cell09_12", 100))) ));
	ros_msg_publisher.insert(std::make_pair("Stack05_Cell05_08", new ros::Publisher((node_handler.advertise<crossi::Stack05_Cell05_08>("Stack05_Cell05_08", 100))) ));
	ros_msg_publisher.insert(std::make_pair("Stack05_Cell01_04", new ros::Publisher((node_handler.advertise<crossi::Stack05_Cell01_04>("Stack05_Cell01_04", 100))) ));
	ros_msg_publisher.insert(std::make_pair("Stack04_Cell09_12", new ros::Publisher((node_handler.advertise<crossi::Stack04_Cell09_12>("Stack04_Cell09_12", 100))) ));
	ros_msg_publisher.insert(std::make_pair("Stack04_Cell05_08", new ros::Publisher((node_handler.advertise<crossi::Stack04_Cell05_08>("Stack04_Cell05_08", 100))) ));
	ros_msg_publisher.insert(std::make_pair("Stack04_Cell01_04", new ros::Publisher((node_handler.advertise<crossi::Stack04_Cell01_04>("Stack04_Cell01_04", 100))) ));
	ros_msg_publisher.insert(std::make_pair("Stack03_Cell09_12", new ros::Publisher((node_handler.advertise<crossi::Stack03_Cell09_12>("Stack03_Cell09_12", 100))) ));
	ros_msg_publisher.insert(std::make_pair("Stack03_Cell05_08", new ros::Publisher((node_handler.advertise<crossi::Stack03_Cell05_08>("Stack03_Cell05_08", 100))) ));
	ros_msg_publisher.insert(std::make_pair("Stack03_Cell01_04", new ros::Publisher((node_handler.advertise<crossi::Stack03_Cell01_04>("Stack03_Cell01_04", 100))) ));
	ros_msg_publisher.insert(std::make_pair("Stack02_Cell09_12", new ros::Publisher((node_handler.advertise<crossi::Stack02_Cell09_12>("Stack02_Cell09_12", 100))) ));
	ros_msg_publisher.insert(std::make_pair("Stack02_Cell05_08", new ros::Publisher((node_handler.advertise<crossi::Stack02_Cell05_08>("Stack02_Cell05_08", 100))) ));
	ros_msg_publisher.insert(std::make_pair("Stack02_Cell01_04", new ros::Publisher((node_handler.advertise<crossi::Stack02_Cell01_04>("Stack02_Cell01_04", 100))) ));
	ros_msg_publisher.insert(std::make_pair("Stack01_Cell09_12", new ros::Publisher((node_handler.advertise<crossi::Stack01_Cell09_12>("Stack01_Cell09_12", 100))) ));
	ros_msg_publisher.insert(std::make_pair("Stack01_Cell05_08", new ros::Publisher((node_handler.advertise<crossi::Stack01_Cell05_08>("Stack01_Cell05_08", 100))) ));
	ros_msg_publisher.insert(std::make_pair("Stack01_Cell01_04", new ros::Publisher((node_handler.advertise<crossi::Stack01_Cell01_04>("Stack01_Cell01_04", 100))) ));
	ros_msg_publisher.insert(std::make_pair("VECTOR__INDEPENDENT_SIG_MSG", new ros::Publisher((node_handler.advertise<crossi::VECTOR__INDEPENDENT_SIG_MSG>("VECTOR__INDEPENDENT_SIG_MSG", 100))) ));
	ros_msg_publisher.insert(std::make_pair("BMaS_Commands", new ros::Publisher((node_handler.advertise<crossi::BMaS_Commands>("BMaS_Commands", 100))) ));
	ros_msg_publisher.insert(std::make_pair("Cell_Temp_Info", new ros::Publisher((node_handler.advertise<crossi::Cell_Temp_Info>("Cell_Temp_Info", 100))) ));
	ros_msg_publisher.insert(std::make_pair("Cell_Voltage_Info", new ros::Publisher((node_handler.advertise<crossi::Cell_Voltage_Info>("Cell_Voltage_Info", 100))) ));
	ros_msg_publisher.insert(std::make_pair("BMaS_Status", new ros::Publisher((node_handler.advertise<crossi::BMaS_Status>("BMaS_Status", 100))) ));
	ros_msg_publisher.insert(std::make_pair("IVT_Msg_Result_Wh", new ros::Publisher((node_handler.advertise<crossi::IVT_Msg_Result_Wh>("IVT_Msg_Result_Wh", 100))) ));
	ros_msg_publisher.insert(std::make_pair("IVT_Msg_Result_U2", new ros::Publisher((node_handler.advertise<crossi::IVT_Msg_Result_U2>("IVT_Msg_Result_U2", 100))) ));
	ros_msg_publisher.insert(std::make_pair("IVT_Msg_Result_U1", new ros::Publisher((node_handler.advertise<crossi::IVT_Msg_Result_U1>("IVT_Msg_Result_U1", 100))) ));
	ros_msg_publisher.insert(std::make_pair("IVT_Msg_Result_I", new ros::Publisher((node_handler.advertise<crossi::IVT_Msg_Result_I>("IVT_Msg_Result_I", 100))) ));
}

void dcu::charger_Signals(const std::string *str, std::vector<float> *input, dcu::Crossi_Publisher *pup)
{
	crossi::charger_Signals msg;
	fill_ros_msg(&msg, nullptr);
	for (auto i : *input)
{
		fill_ros_msg(nullptr, &i);
	}
	pup->ros_msg_publisher[*str]->publish(msg);
}

void dcu::IMD(const std::string *str, std::vector<float> *input, dcu::Crossi_Publisher *pup)
{
	crossi::IMD msg;
	fill_ros_msg(&msg, nullptr);
	for (auto i : *input)
{
		fill_ros_msg(nullptr, &i);
	}
	pup->ros_msg_publisher[*str]->publish(msg);
}

void dcu::charge_EN(const std::string *str, std::vector<float> *input, dcu::Crossi_Publisher *pup)
{
	crossi::charge_EN msg;
	fill_ros_msg(&msg, nullptr);
	for (auto i : *input)
{
		fill_ros_msg(nullptr, &i);
	}
	pup->ros_msg_publisher[*str]->publish(msg);
}

void dcu::BMS_Debug(const std::string *str, std::vector<float> *input, dcu::Crossi_Publisher *pup)
{
	crossi::BMS_Debug msg;
	fill_ros_msg(&msg, nullptr);
	for (auto i : *input)
{
		fill_ros_msg(nullptr, &i);
	}
	pup->ros_msg_publisher[*str]->publish(msg);
}

void dcu::LTCTemp_Part2(const std::string *str, std::vector<float> *input, dcu::Crossi_Publisher *pup)
{
	crossi::LTCTemp_Part2 msg;
	fill_ros_msg(&msg, nullptr);
	for (auto i : *input)
{
		fill_ros_msg(nullptr, &i);
	}
	pup->ros_msg_publisher[*str]->publish(msg);
}

void dcu::LTCTemp_Part1(const std::string *str, std::vector<float> *input, dcu::Crossi_Publisher *pup)
{
	crossi::LTCTemp_Part1 msg;
	fill_ros_msg(&msg, nullptr);
	for (auto i : *input)
{
		fill_ros_msg(nullptr, &i);
	}
	pup->ros_msg_publisher[*str]->publish(msg);
}

void dcu::Stack12_Temp07_12(const std::string *str, std::vector<float> *input, dcu::Crossi_Publisher *pup)
{
	crossi::Stack12_Temp07_12 msg;
	fill_ros_msg(&msg, nullptr);
	for (auto i : *input)
{
		fill_ros_msg(nullptr, &i);
	}
	pup->ros_msg_publisher[*str]->publish(msg);
}

void dcu::Stack12_Temp01_06(const std::string *str, std::vector<float> *input, dcu::Crossi_Publisher *pup)
{
	crossi::Stack12_Temp01_06 msg;
	fill_ros_msg(&msg, nullptr);
	for (auto i : *input)
{
		fill_ros_msg(nullptr, &i);
	}
	pup->ros_msg_publisher[*str]->publish(msg);
}

void dcu::Stack11_Temp07_12(const std::string *str, std::vector<float> *input, dcu::Crossi_Publisher *pup)
{
	crossi::Stack11_Temp07_12 msg;
	fill_ros_msg(&msg, nullptr);
	for (auto i : *input)
{
		fill_ros_msg(nullptr, &i);
	}
	pup->ros_msg_publisher[*str]->publish(msg);
}

void dcu::Stack11_Temp01_06(const std::string *str, std::vector<float> *input, dcu::Crossi_Publisher *pup)
{
	crossi::Stack11_Temp01_06 msg;
	fill_ros_msg(&msg, nullptr);
	for (auto i : *input)
{
		fill_ros_msg(nullptr, &i);
	}
	pup->ros_msg_publisher[*str]->publish(msg);
}

void dcu::Stack10_Temp07_12(const std::string *str, std::vector<float> *input, dcu::Crossi_Publisher *pup)
{
	crossi::Stack10_Temp07_12 msg;
	fill_ros_msg(&msg, nullptr);
	for (auto i : *input)
{
		fill_ros_msg(nullptr, &i);
	}
	pup->ros_msg_publisher[*str]->publish(msg);
}

void dcu::Stack10_Temp01_06(const std::string *str, std::vector<float> *input, dcu::Crossi_Publisher *pup)
{
	crossi::Stack10_Temp01_06 msg;
	fill_ros_msg(&msg, nullptr);
	for (auto i : *input)
{
		fill_ros_msg(nullptr, &i);
	}
	pup->ros_msg_publisher[*str]->publish(msg);
}

void dcu::Stack09_Temp07_12(const std::string *str, std::vector<float> *input, dcu::Crossi_Publisher *pup)
{
	crossi::Stack09_Temp07_12 msg;
	fill_ros_msg(&msg, nullptr);
	for (auto i : *input)
{
		fill_ros_msg(nullptr, &i);
	}
	pup->ros_msg_publisher[*str]->publish(msg);
}

void dcu::Stack09_Temp01_06(const std::string *str, std::vector<float> *input, dcu::Crossi_Publisher *pup)
{
	crossi::Stack09_Temp01_06 msg;
	fill_ros_msg(&msg, nullptr);
	for (auto i : *input)
{
		fill_ros_msg(nullptr, &i);
	}
	pup->ros_msg_publisher[*str]->publish(msg);
}

void dcu::Stack08_Temp07_12(const std::string *str, std::vector<float> *input, dcu::Crossi_Publisher *pup)
{
	crossi::Stack08_Temp07_12 msg;
	fill_ros_msg(&msg, nullptr);
	for (auto i : *input)
{
		fill_ros_msg(nullptr, &i);
	}
	pup->ros_msg_publisher[*str]->publish(msg);
}

void dcu::Stack08_Temp01_06(const std::string *str, std::vector<float> *input, dcu::Crossi_Publisher *pup)
{
	crossi::Stack08_Temp01_06 msg;
	fill_ros_msg(&msg, nullptr);
	for (auto i : *input)
{
		fill_ros_msg(nullptr, &i);
	}
	pup->ros_msg_publisher[*str]->publish(msg);
}

void dcu::Stack07_Temp07_12(const std::string *str, std::vector<float> *input, dcu::Crossi_Publisher *pup)
{
	crossi::Stack07_Temp07_12 msg;
	fill_ros_msg(&msg, nullptr);
	for (auto i : *input)
{
		fill_ros_msg(nullptr, &i);
	}
	pup->ros_msg_publisher[*str]->publish(msg);
}

void dcu::Stack07_Temp01_06(const std::string *str, std::vector<float> *input, dcu::Crossi_Publisher *pup)
{
	crossi::Stack07_Temp01_06 msg;
	fill_ros_msg(&msg, nullptr);
	for (auto i : *input)
{
		fill_ros_msg(nullptr, &i);
	}
	pup->ros_msg_publisher[*str]->publish(msg);
}

void dcu::Stack06_Temp07_12(const std::string *str, std::vector<float> *input, dcu::Crossi_Publisher *pup)
{
	crossi::Stack06_Temp07_12 msg;
	fill_ros_msg(&msg, nullptr);
	for (auto i : *input)
{
		fill_ros_msg(nullptr, &i);
	}
	pup->ros_msg_publisher[*str]->publish(msg);
}

void dcu::Stack06_Temp01_06(const std::string *str, std::vector<float> *input, dcu::Crossi_Publisher *pup)
{
	crossi::Stack06_Temp01_06 msg;
	fill_ros_msg(&msg, nullptr);
	for (auto i : *input)
{
		fill_ros_msg(nullptr, &i);
	}
	pup->ros_msg_publisher[*str]->publish(msg);
}

void dcu::Stack05_Temp07_12(const std::string *str, std::vector<float> *input, dcu::Crossi_Publisher *pup)
{
	crossi::Stack05_Temp07_12 msg;
	fill_ros_msg(&msg, nullptr);
	for (auto i : *input)
{
		fill_ros_msg(nullptr, &i);
	}
	pup->ros_msg_publisher[*str]->publish(msg);
}

void dcu::Stack05_Temp01_06(const std::string *str, std::vector<float> *input, dcu::Crossi_Publisher *pup)
{
	crossi::Stack05_Temp01_06 msg;
	fill_ros_msg(&msg, nullptr);
	for (auto i : *input)
{
		fill_ros_msg(nullptr, &i);
	}
	pup->ros_msg_publisher[*str]->publish(msg);
}

void dcu::Stack04_Temp07_12(const std::string *str, std::vector<float> *input, dcu::Crossi_Publisher *pup)
{
	crossi::Stack04_Temp07_12 msg;
	fill_ros_msg(&msg, nullptr);
	for (auto i : *input)
{
		fill_ros_msg(nullptr, &i);
	}
	pup->ros_msg_publisher[*str]->publish(msg);
}

void dcu::Stack04_Temp01_06(const std::string *str, std::vector<float> *input, dcu::Crossi_Publisher *pup)
{
	crossi::Stack04_Temp01_06 msg;
	fill_ros_msg(&msg, nullptr);
	for (auto i : *input)
{
		fill_ros_msg(nullptr, &i);
	}
	pup->ros_msg_publisher[*str]->publish(msg);
}

void dcu::Stack03_Temp07_12(const std::string *str, std::vector<float> *input, dcu::Crossi_Publisher *pup)
{
	crossi::Stack03_Temp07_12 msg;
	fill_ros_msg(&msg, nullptr);
	for (auto i : *input)
{
		fill_ros_msg(nullptr, &i);
	}
	pup->ros_msg_publisher[*str]->publish(msg);
}

void dcu::Stack03_Temp01_06(const std::string *str, std::vector<float> *input, dcu::Crossi_Publisher *pup)
{
	crossi::Stack03_Temp01_06 msg;
	fill_ros_msg(&msg, nullptr);
	for (auto i : *input)
{
		fill_ros_msg(nullptr, &i);
	}
	pup->ros_msg_publisher[*str]->publish(msg);
}

void dcu::Stack02_Temp07_12(const std::string *str, std::vector<float> *input, dcu::Crossi_Publisher *pup)
{
	crossi::Stack02_Temp07_12 msg;
	fill_ros_msg(&msg, nullptr);
	for (auto i : *input)
{
		fill_ros_msg(nullptr, &i);
	}
	pup->ros_msg_publisher[*str]->publish(msg);
}

void dcu::Stack02_Temp01_06(const std::string *str, std::vector<float> *input, dcu::Crossi_Publisher *pup)
{
	crossi::Stack02_Temp01_06 msg;
	fill_ros_msg(&msg, nullptr);
	for (auto i : *input)
{
		fill_ros_msg(nullptr, &i);
	}
	pup->ros_msg_publisher[*str]->publish(msg);
}

void dcu::Stack01_Temp07_12(const std::string *str, std::vector<float> *input, dcu::Crossi_Publisher *pup)
{
	crossi::Stack01_Temp07_12 msg;
	fill_ros_msg(&msg, nullptr);
	for (auto i : *input)
{
		fill_ros_msg(nullptr, &i);
	}
	pup->ros_msg_publisher[*str]->publish(msg);
}

void dcu::Stack01_Temp01_06(const std::string *str, std::vector<float> *input, dcu::Crossi_Publisher *pup)
{
	crossi::Stack01_Temp01_06 msg;
	fill_ros_msg(&msg, nullptr);
	for (auto i : *input)
{
		fill_ros_msg(nullptr, &i);
	}
	pup->ros_msg_publisher[*str]->publish(msg);
}

void dcu::Stack12_Cell09_12(const std::string *str, std::vector<float> *input, dcu::Crossi_Publisher *pup)
{
	crossi::Stack12_Cell09_12 msg;
	fill_ros_msg(&msg, nullptr);
	for (auto i : *input)
{
		fill_ros_msg(nullptr, &i);
	}
	pup->ros_msg_publisher[*str]->publish(msg);
}

void dcu::Stack12_Cell05_08(const std::string *str, std::vector<float> *input, dcu::Crossi_Publisher *pup)
{
	crossi::Stack12_Cell05_08 msg;
	fill_ros_msg(&msg, nullptr);
	for (auto i : *input)
{
		fill_ros_msg(nullptr, &i);
	}
	pup->ros_msg_publisher[*str]->publish(msg);
}

void dcu::Stack12_Cell01_04(const std::string *str, std::vector<float> *input, dcu::Crossi_Publisher *pup)
{
	crossi::Stack12_Cell01_04 msg;
	fill_ros_msg(&msg, nullptr);
	for (auto i : *input)
{
		fill_ros_msg(nullptr, &i);
	}
	pup->ros_msg_publisher[*str]->publish(msg);
}

void dcu::Stack11_Cell09_12(const std::string *str, std::vector<float> *input, dcu::Crossi_Publisher *pup)
{
	crossi::Stack11_Cell09_12 msg;
	fill_ros_msg(&msg, nullptr);
	for (auto i : *input)
{
		fill_ros_msg(nullptr, &i);
	}
	pup->ros_msg_publisher[*str]->publish(msg);
}

void dcu::Stack11_Cell05_08(const std::string *str, std::vector<float> *input, dcu::Crossi_Publisher *pup)
{
	crossi::Stack11_Cell05_08 msg;
	fill_ros_msg(&msg, nullptr);
	for (auto i : *input)
{
		fill_ros_msg(nullptr, &i);
	}
	pup->ros_msg_publisher[*str]->publish(msg);
}

void dcu::Stack11_Cell01_04(const std::string *str, std::vector<float> *input, dcu::Crossi_Publisher *pup)
{
	crossi::Stack11_Cell01_04 msg;
	fill_ros_msg(&msg, nullptr);
	for (auto i : *input)
{
		fill_ros_msg(nullptr, &i);
	}
	pup->ros_msg_publisher[*str]->publish(msg);
}

void dcu::Stack10_Cell09_12(const std::string *str, std::vector<float> *input, dcu::Crossi_Publisher *pup)
{
	crossi::Stack10_Cell09_12 msg;
	fill_ros_msg(&msg, nullptr);
	for (auto i : *input)
{
		fill_ros_msg(nullptr, &i);
	}
	pup->ros_msg_publisher[*str]->publish(msg);
}

void dcu::Stack10_Cell05_08(const std::string *str, std::vector<float> *input, dcu::Crossi_Publisher *pup)
{
	crossi::Stack10_Cell05_08 msg;
	fill_ros_msg(&msg, nullptr);
	for (auto i : *input)
{
		fill_ros_msg(nullptr, &i);
	}
	pup->ros_msg_publisher[*str]->publish(msg);
}

void dcu::Stack10_Cell01_04(const std::string *str, std::vector<float> *input, dcu::Crossi_Publisher *pup)
{
	crossi::Stack10_Cell01_04 msg;
	fill_ros_msg(&msg, nullptr);
	for (auto i : *input)
{
		fill_ros_msg(nullptr, &i);
	}
	pup->ros_msg_publisher[*str]->publish(msg);
}

void dcu::Stack09_Cell09_12(const std::string *str, std::vector<float> *input, dcu::Crossi_Publisher *pup)
{
	crossi::Stack09_Cell09_12 msg;
	fill_ros_msg(&msg, nullptr);
	for (auto i : *input)
{
		fill_ros_msg(nullptr, &i);
	}
	pup->ros_msg_publisher[*str]->publish(msg);
}

void dcu::Stack09_Cell05_08(const std::string *str, std::vector<float> *input, dcu::Crossi_Publisher *pup)
{
	crossi::Stack09_Cell05_08 msg;
	fill_ros_msg(&msg, nullptr);
	for (auto i : *input)
{
		fill_ros_msg(nullptr, &i);
	}
	pup->ros_msg_publisher[*str]->publish(msg);
}

void dcu::Stack09_Cell01_04(const std::string *str, std::vector<float> *input, dcu::Crossi_Publisher *pup)
{
	crossi::Stack09_Cell01_04 msg;
	fill_ros_msg(&msg, nullptr);
	for (auto i : *input)
{
		fill_ros_msg(nullptr, &i);
	}
	pup->ros_msg_publisher[*str]->publish(msg);
}

void dcu::Stack08_Cell09_12(const std::string *str, std::vector<float> *input, dcu::Crossi_Publisher *pup)
{
	crossi::Stack08_Cell09_12 msg;
	fill_ros_msg(&msg, nullptr);
	for (auto i : *input)
{
		fill_ros_msg(nullptr, &i);
	}
	pup->ros_msg_publisher[*str]->publish(msg);
}

void dcu::Stack08_Cell05_08(const std::string *str, std::vector<float> *input, dcu::Crossi_Publisher *pup)
{
	crossi::Stack08_Cell05_08 msg;
	fill_ros_msg(&msg, nullptr);
	for (auto i : *input)
{
		fill_ros_msg(nullptr, &i);
	}
	pup->ros_msg_publisher[*str]->publish(msg);
}

void dcu::Stack08_Cell01_04(const std::string *str, std::vector<float> *input, dcu::Crossi_Publisher *pup)
{
	crossi::Stack08_Cell01_04 msg;
	fill_ros_msg(&msg, nullptr);
	for (auto i : *input)
{
		fill_ros_msg(nullptr, &i);
	}
	pup->ros_msg_publisher[*str]->publish(msg);
}

void dcu::Stack07_Cell09_12(const std::string *str, std::vector<float> *input, dcu::Crossi_Publisher *pup)
{
	crossi::Stack07_Cell09_12 msg;
	fill_ros_msg(&msg, nullptr);
	for (auto i : *input)
{
		fill_ros_msg(nullptr, &i);
	}
	pup->ros_msg_publisher[*str]->publish(msg);
}

void dcu::Stack07_Cell05_08(const std::string *str, std::vector<float> *input, dcu::Crossi_Publisher *pup)
{
	crossi::Stack07_Cell05_08 msg;
	fill_ros_msg(&msg, nullptr);
	for (auto i : *input)
{
		fill_ros_msg(nullptr, &i);
	}
	pup->ros_msg_publisher[*str]->publish(msg);
}

void dcu::Stack07_Cell01_04(const std::string *str, std::vector<float> *input, dcu::Crossi_Publisher *pup)
{
	crossi::Stack07_Cell01_04 msg;
	fill_ros_msg(&msg, nullptr);
	for (auto i : *input)
{
		fill_ros_msg(nullptr, &i);
	}
	pup->ros_msg_publisher[*str]->publish(msg);
}

void dcu::Stack06_Cell09_12(const std::string *str, std::vector<float> *input, dcu::Crossi_Publisher *pup)
{
	crossi::Stack06_Cell09_12 msg;
	fill_ros_msg(&msg, nullptr);
	for (auto i : *input)
{
		fill_ros_msg(nullptr, &i);
	}
	pup->ros_msg_publisher[*str]->publish(msg);
}

void dcu::Stack06_Cell05_08(const std::string *str, std::vector<float> *input, dcu::Crossi_Publisher *pup)
{
	crossi::Stack06_Cell05_08 msg;
	fill_ros_msg(&msg, nullptr);
	for (auto i : *input)
{
		fill_ros_msg(nullptr, &i);
	}
	pup->ros_msg_publisher[*str]->publish(msg);
}

void dcu::Stack06_Cell01_04(const std::string *str, std::vector<float> *input, dcu::Crossi_Publisher *pup)
{
	crossi::Stack06_Cell01_04 msg;
	fill_ros_msg(&msg, nullptr);
	for (auto i : *input)
{
		fill_ros_msg(nullptr, &i);
	}
	pup->ros_msg_publisher[*str]->publish(msg);
}

void dcu::Stack05_Cell09_12(const std::string *str, std::vector<float> *input, dcu::Crossi_Publisher *pup)
{
	crossi::Stack05_Cell09_12 msg;
	fill_ros_msg(&msg, nullptr);
	for (auto i : *input)
{
		fill_ros_msg(nullptr, &i);
	}
	pup->ros_msg_publisher[*str]->publish(msg);
}

void dcu::Stack05_Cell05_08(const std::string *str, std::vector<float> *input, dcu::Crossi_Publisher *pup)
{
	crossi::Stack05_Cell05_08 msg;
	fill_ros_msg(&msg, nullptr);
	for (auto i : *input)
{
		fill_ros_msg(nullptr, &i);
	}
	pup->ros_msg_publisher[*str]->publish(msg);
}

void dcu::Stack05_Cell01_04(const std::string *str, std::vector<float> *input, dcu::Crossi_Publisher *pup)
{
	crossi::Stack05_Cell01_04 msg;
	fill_ros_msg(&msg, nullptr);
	for (auto i : *input)
{
		fill_ros_msg(nullptr, &i);
	}
	pup->ros_msg_publisher[*str]->publish(msg);
}

void dcu::Stack04_Cell09_12(const std::string *str, std::vector<float> *input, dcu::Crossi_Publisher *pup)
{
	crossi::Stack04_Cell09_12 msg;
	fill_ros_msg(&msg, nullptr);
	for (auto i : *input)
{
		fill_ros_msg(nullptr, &i);
	}
	pup->ros_msg_publisher[*str]->publish(msg);
}

void dcu::Stack04_Cell05_08(const std::string *str, std::vector<float> *input, dcu::Crossi_Publisher *pup)
{
	crossi::Stack04_Cell05_08 msg;
	fill_ros_msg(&msg, nullptr);
	for (auto i : *input)
{
		fill_ros_msg(nullptr, &i);
	}
	pup->ros_msg_publisher[*str]->publish(msg);
}

void dcu::Stack04_Cell01_04(const std::string *str, std::vector<float> *input, dcu::Crossi_Publisher *pup)
{
	crossi::Stack04_Cell01_04 msg;
	fill_ros_msg(&msg, nullptr);
	for (auto i : *input)
{
		fill_ros_msg(nullptr, &i);
	}
	pup->ros_msg_publisher[*str]->publish(msg);
}

void dcu::Stack03_Cell09_12(const std::string *str, std::vector<float> *input, dcu::Crossi_Publisher *pup)
{
	crossi::Stack03_Cell09_12 msg;
	fill_ros_msg(&msg, nullptr);
	for (auto i : *input)
{
		fill_ros_msg(nullptr, &i);
	}
	pup->ros_msg_publisher[*str]->publish(msg);
}

void dcu::Stack03_Cell05_08(const std::string *str, std::vector<float> *input, dcu::Crossi_Publisher *pup)
{
	crossi::Stack03_Cell05_08 msg;
	fill_ros_msg(&msg, nullptr);
	for (auto i : *input)
{
		fill_ros_msg(nullptr, &i);
	}
	pup->ros_msg_publisher[*str]->publish(msg);
}

void dcu::Stack03_Cell01_04(const std::string *str, std::vector<float> *input, dcu::Crossi_Publisher *pup)
{
	crossi::Stack03_Cell01_04 msg;
	fill_ros_msg(&msg, nullptr);
	for (auto i : *input)
{
		fill_ros_msg(nullptr, &i);
	}
	pup->ros_msg_publisher[*str]->publish(msg);
}

void dcu::Stack02_Cell09_12(const std::string *str, std::vector<float> *input, dcu::Crossi_Publisher *pup)
{
	crossi::Stack02_Cell09_12 msg;
	fill_ros_msg(&msg, nullptr);
	for (auto i : *input)
{
		fill_ros_msg(nullptr, &i);
	}
	pup->ros_msg_publisher[*str]->publish(msg);
}

void dcu::Stack02_Cell05_08(const std::string *str, std::vector<float> *input, dcu::Crossi_Publisher *pup)
{
	crossi::Stack02_Cell05_08 msg;
	fill_ros_msg(&msg, nullptr);
	for (auto i : *input)
{
		fill_ros_msg(nullptr, &i);
	}
	pup->ros_msg_publisher[*str]->publish(msg);
}

void dcu::Stack02_Cell01_04(const std::string *str, std::vector<float> *input, dcu::Crossi_Publisher *pup)
{
	crossi::Stack02_Cell01_04 msg;
	fill_ros_msg(&msg, nullptr);
	for (auto i : *input)
{
		fill_ros_msg(nullptr, &i);
	}
	pup->ros_msg_publisher[*str]->publish(msg);
}

void dcu::Stack01_Cell09_12(const std::string *str, std::vector<float> *input, dcu::Crossi_Publisher *pup)
{
	crossi::Stack01_Cell09_12 msg;
	fill_ros_msg(&msg, nullptr);
	for (auto i : *input)
{
		fill_ros_msg(nullptr, &i);
	}
	pup->ros_msg_publisher[*str]->publish(msg);
}

void dcu::Stack01_Cell05_08(const std::string *str, std::vector<float> *input, dcu::Crossi_Publisher *pup)
{
	crossi::Stack01_Cell05_08 msg;
	fill_ros_msg(&msg, nullptr);
	for (auto i : *input)
{
		fill_ros_msg(nullptr, &i);
	}
	pup->ros_msg_publisher[*str]->publish(msg);
}

void dcu::Stack01_Cell01_04(const std::string *str, std::vector<float> *input, dcu::Crossi_Publisher *pup)
{
	crossi::Stack01_Cell01_04 msg;
	fill_ros_msg(&msg, nullptr);
	for (auto i : *input)
{
		fill_ros_msg(nullptr, &i);
	}
	pup->ros_msg_publisher[*str]->publish(msg);
}

void dcu::VECTOR__INDEPENDENT_SIG_MSG(const std::string *str, std::vector<float> *input, dcu::Crossi_Publisher *pup)
{
	crossi::VECTOR__INDEPENDENT_SIG_MSG msg;
	fill_ros_msg(&msg, nullptr);
	for (auto i : *input)
{
		fill_ros_msg(nullptr, &i);
	}
	pup->ros_msg_publisher[*str]->publish(msg);
}

void dcu::BMaS_Commands(const std::string *str, std::vector<float> *input, dcu::Crossi_Publisher *pup)
{
	crossi::BMaS_Commands msg;
	fill_ros_msg(&msg, nullptr);
	for (auto i : *input)
{
		fill_ros_msg(nullptr, &i);
	}
	pup->ros_msg_publisher[*str]->publish(msg);
}

void dcu::Cell_Temp_Info(const std::string *str, std::vector<float> *input, dcu::Crossi_Publisher *pup)
{
	crossi::Cell_Temp_Info msg;
	fill_ros_msg(&msg, nullptr);
	for (auto i : *input)
{
		fill_ros_msg(nullptr, &i);
	}
	pup->ros_msg_publisher[*str]->publish(msg);
}

void dcu::Cell_Voltage_Info(const std::string *str, std::vector<float> *input, dcu::Crossi_Publisher *pup)
{
	crossi::Cell_Voltage_Info msg;
	fill_ros_msg(&msg, nullptr);
	for (auto i : *input)
{
		fill_ros_msg(nullptr, &i);
	}
	pup->ros_msg_publisher[*str]->publish(msg);
}

void dcu::BMaS_Status(const std::string *str, std::vector<float> *input, dcu::Crossi_Publisher *pup)
{
	crossi::BMaS_Status msg;
	fill_ros_msg(&msg, nullptr);
	for (auto i : *input)
{
		fill_ros_msg(nullptr, &i);
	}
	pup->ros_msg_publisher[*str]->publish(msg);
}

void dcu::IVT_Msg_Result_Wh(const std::string *str, std::vector<float> *input, dcu::Crossi_Publisher *pup)
{
	crossi::IVT_Msg_Result_Wh msg;
	fill_ros_msg(&msg, nullptr);
	for (auto i : *input)
{
		fill_ros_msg(nullptr, &i);
	}
	pup->ros_msg_publisher[*str]->publish(msg);
}

void dcu::IVT_Msg_Result_U2(const std::string *str, std::vector<float> *input, dcu::Crossi_Publisher *pup)
{
	crossi::IVT_Msg_Result_U2 msg;
	fill_ros_msg(&msg, nullptr);
	for (auto i : *input)
{
		fill_ros_msg(nullptr, &i);
	}
	pup->ros_msg_publisher[*str]->publish(msg);
}

void dcu::IVT_Msg_Result_U1(const std::string *str, std::vector<float> *input, dcu::Crossi_Publisher *pup)
{
	crossi::IVT_Msg_Result_U1 msg;
	fill_ros_msg(&msg, nullptr);
	for (auto i : *input)
{
		fill_ros_msg(nullptr, &i);
	}
	pup->ros_msg_publisher[*str]->publish(msg);
}

void dcu::IVT_Msg_Result_I(const std::string *str, std::vector<float> *input, dcu::Crossi_Publisher *pup)
{
	crossi::IVT_Msg_Result_I msg;
	fill_ros_msg(&msg, nullptr);
	for (auto i : *input)
{
		fill_ros_msg(nullptr, &i);
	}
	pup->ros_msg_publisher[*str]->publish(msg);
}

