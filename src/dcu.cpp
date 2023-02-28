#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#include <net/if.h>
#include <sys/ioctl.h>
#include <sys/socket.h>

#include <linux/can.h>
#include <linux/can/raw.h>

#include <iostream>

#include "dcu.h"
#include "config.h"


int main(int argc, char **argv)
{
    std::cout << "\t CAN MODULE" << std::endl;
    std::cout << std::endl;


    dcu::DCU_Handler handler(argc, argv);


    handler.handler_start_cros();


    return 0;
}

