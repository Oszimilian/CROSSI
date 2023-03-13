cmake_minimum_required(VERSION 3.0.2)
project(crossi)


## Compile as C++11, supported in ROS Kinetic and newer
# add_compile_options(-std=c++11)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
roscpp
rospy
std_msgs
message_generation
)

## System dependencies are found with CMake's conventions
# find_package(Boost REQUIRED COMPONENTS system)


## Uncomment this if the package has a setup.py. This macro ensures
## modules and global scripts declared therein get installed
## See http://ros.org/doc/api/catkin/html/user_guide/setup_dot_py.html
# catkin_python_setup()

################################################
## Declare ROS messages, services and actions ##
################################################

## To declare and build messages, services or actions from within this
## package, follow these steps:
## * Let MSG_DEP_SET be the set of packages whose message types you use in
##   your messages/services/actions (e.g. std_msgs, actionlib_msgs, ...).
## * In the file package.xml:
##   * add a build_depend tag for "message_generation"
##   * add a build_depend and a exec_depend tag for each package in MSG_DEP_SET
##   * If MSG_DEP_SET isn't empty the following dependency has been pulled in
##     but can be declared for certainty nonetheless:
##     * add a exec_depend tag for "message_runtime"
## * In this file (CMakeLists.txt):
##   * add "message_generation" and every package in MSG_DEP_SET to
##     find_package(catkin REQUIRED COMPONENTS ...)
##   * add "message_runtime" and every package in MSG_DEP_SET to
##     catkin_package(CATKIN_DEPENDS ...)
##   * uncomment the add_*_files sections below as needed
##     and list every .msg/.srv/.action file to be processed
##   * uncomment the generate_messages entry below
##   * add every package in MSG_DEP_SET to generate_messages(DEPENDENCIES ...)

#add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/CROSSI/)

#file(GLOB MESSAGE_FILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}/CROSSI/msg/ *.msg)



#
# Hier wird eingefügt
#
add_message_files(FILES

#START_CUSTOM_AREA
charger_Signals.msg
IMD.msg
charge_EN.msg
BMS_Debug.msg
LTCTemp_Part2.msg
LTCTemp_Part1.msg
Stack12_Temp07_12.msg
Stack12_Temp01_06.msg
Stack11_Temp07_12.msg
Stack11_Temp01_06.msg
Stack10_Temp07_12.msg
Stack10_Temp01_06.msg
Stack09_Temp07_12.msg
Stack09_Temp01_06.msg
Stack08_Temp07_12.msg
Stack08_Temp01_06.msg
Stack07_Temp07_12.msg
Stack07_Temp01_06.msg
Stack06_Temp07_12.msg
Stack06_Temp01_06.msg
Stack05_Temp07_12.msg
Stack05_Temp01_06.msg
Stack04_Temp07_12.msg
Stack04_Temp01_06.msg
Stack03_Temp07_12.msg
Stack03_Temp01_06.msg
Stack02_Temp07_12.msg
Stack02_Temp01_06.msg
Stack01_Temp07_12.msg
Stack01_Temp01_06.msg
Stack12_Cell09_12.msg
Stack12_Cell05_08.msg
Stack12_Cell01_04.msg
Stack11_Cell09_12.msg
Stack11_Cell05_08.msg
Stack11_Cell01_04.msg
Stack10_Cell09_12.msg
Stack10_Cell05_08.msg
Stack10_Cell01_04.msg
Stack09_Cell09_12.msg
Stack09_Cell05_08.msg
Stack09_Cell01_04.msg
Stack08_Cell09_12.msg
Stack08_Cell05_08.msg
Stack08_Cell01_04.msg
Stack07_Cell09_12.msg
Stack07_Cell05_08.msg
Stack07_Cell01_04.msg
Stack06_Cell09_12.msg
Stack06_Cell05_08.msg
Stack06_Cell01_04.msg
Stack05_Cell09_12.msg
Stack05_Cell05_08.msg
Stack05_Cell01_04.msg
Stack04_Cell09_12.msg
Stack04_Cell05_08.msg
Stack04_Cell01_04.msg
Stack03_Cell09_12.msg
Stack03_Cell05_08.msg
Stack03_Cell01_04.msg
Stack02_Cell09_12.msg
Stack02_Cell05_08.msg
Stack02_Cell01_04.msg
Stack01_Cell09_12.msg
Stack01_Cell05_08.msg
Stack01_Cell01_04.msg
VECTOR__INDEPENDENT_SIG_MSG.msg
BMaS_Commands.msg
Cell_Temp_Info.msg
Cell_Voltage_Info.msg
BMaS_Status.msg
IVT_Msg_Result_Wh.msg
IVT_Msg_Result_U2.msg
IVT_Msg_Result_U1.msg
IVT_Msg_Result_I.msg
#END_CUSTOM_AREA
)

## Generate services in the 'srv' folder
# add_service_files(
#   FILES
#   Service1.srv
#   Service2.srv
# )

## Generate actions in the 'action' folder
# add_action_files(
#   FILES
#   Action1.action
#   Action2.action
# )

## Generate added messages and services with any dependencies listed here
generate_messages(
   DEPENDENCIES
  std_msgs
 )

################################################
## Declare ROS dynamic reconfigure parameters ##
################################################

## To declare and build dynamic reconfigure parameters within this
## package, follow these steps:
## * In the file package.xml:
##   * add a build_depend and a exec_depend tag for "dynamic_reconfigure"
## * In this file (CMakeLists.txt):
##   * add "dynamic_reconfigure" to
##     find_package(catkin REQUIRED COMPONENTS ...)
##   * uncomment the "generate_dynamic_reconfigure_options" section below
##     and list every .cfg file to be processed

## Generate dynamic reconfigure parameters in the 'cfg' folder
# generate_dynamic_reconfigure_options(
#   cfg/DynReconf1.cfg
#   cfg/DynReconf2.cfg
# )

###################################
## catkin specific configuration ##
###################################
## The catkin_package macro generates cmake config files for your package
## Declare things to be passed to dependent projects
## INCLUDE_DIRS: uncomment this if your package contains header files
## LIBRARIES: libraries you create in this project that dependent projects also need
## CATKIN_DEPENDS: catkin_packages dependent projects also need
## DEPENDS: system dependencies of this project that dependent projects also need
catkin_package(
  CATKIN_DEPENDS roscpp rospy std_msgs message_runtime
)

###########
## Build ##
###########

## Specify additional locations of header files
## Your package locations should be listed before other locations
include_directories(
# include
  ${catkin_INCLUDE_DIRS}
)

## Declare a C++ library
# add_library(${PROJECT_NAME}
#   src/${PROJECT_NAME}/CROSSI.cpp
# )

## Add cmake target dependencies of the library
## as an example, code may need to be generated before libraries
## either from message generation or dynamic reconfigure
# add_dependencies(${PROJECT_NAME} ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

## Declare a C++ executable
## With catkin_make all packages are built within a single CMake context
## The recommended prefix ensures that target names across packages don't collide
add_executable(${PROJECT_NAME}_node src/dcu.cpp
                                    src/capture.cpp
                                    src/handler.cpp
                                    src/list.cpp
                                    src/decode.cpp
                                    src/config.cpp
                                    src/msggen.cpp
                                    src/fileHasher.cpp
                                    src/msgBuilder.cpp
                                    src/loadROSMsg.cpp
                                    src/headerBuilder.cpp
                                    src/crossiPublisher.cpp
                                    src/publisherBuilder.cpp
                                    src/Fixed.cpp
                                    
                                    src/dcu.h
                                    src/capture.h
                                    src/list.h
                                    src/decode.h
                                    src/ring.h
                                    src/config.h
                                    src/msggen.h
                                    src/fileHasher.h
                                    src/msgBuilder.h
                                    src/loadROSMsg.h
                                    src/headerBuilder.h
                                    src/crossiPublisher.h
                                    src/publisherBuilder.h
                                    src/Fixed.h)

add_definitions(-DEFAULT_CONFIG_PATH="/home/maximilian/Git/CROSSI/config/crossi_config.txt")

add_subdirectory(src/external/dbcppp)

target_link_libraries(${PROJECT_NAME}_node libdbcppp)

target_link_libraries(${PROJECT_NAME}_node pthread)

set_property(TARGET ${PROJECT_NAME}_node PROPERTY CXX_STANDARD 17)

target_compile_options(${PROJECT_NAME}_node  PRIVATE -g)

## Rename C++ executable without prefix
## The above recommended prefix causes long target names, the following renames the
## target back to the shorter version for ease of user use
## e.g. "rosrun someones_pkg node" instead of "rosrun someones_pkg someones_pkg_node"
# set_target_properties(${PROJECT_NAME}_node PROPERTIES OUTPUT_NAME node PREFIX "")

## Add cmake target dependencies of the executable
## same as for the library above
add_dependencies(${PROJECT_NAME}_node ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

## Specify libraries to link a library or executable target against
target_link_libraries(${PROJECT_NAME}_node
   ${catkin_LIBRARIES}
 )

#############
## Install ##
#############

# all install targets should use catkin DESTINATION variables
# See http://ros.org/doc/api/catkin/html/adv_user_guide/variables.html

## Mark executable scripts (Python etc.) for installation
## in contrast to setup.py, you can choose the destination
# catkin_install_python(PROGRAMS
#   scripts/my_python_script
#   DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
# )

## Mark executables for installation
## See http://docs.ros.org/melodic/api/catkin/html/howto/format1/building_executables.html
# install(TARGETS ${PROJECT_NAME}_node
#   RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
# )

## Mark libraries for installation
## See http://docs.ros.org/melodic/api/catkin/html/howto/format1/building_libraries.html
# install(TARGETS ${PROJECT_NAME}
#   ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
#   LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
#   RUNTIME DESTINATION ${CATKIN_GLOBAL_BIN_DESTINATION}
# )

## Mark cpp header files for installation
# install(DIRECTORY include/${PROJECT_NAME}/
#   DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
#   FILES_MATCHING PATTERN "*.h"
#   PATTERN ".svn" EXCLUDE
# )

## Mark other files for installation (e.g. launch and bag files, etc.)
# install(FILES
#   # myfile1
#   # myfile2
#   DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
# )

#############
## Testing ##
#############

## Add gtest based cpp test target and link libraries
# catkin_add_gtest(${PROJECT_NAME}-test test/test_CROSSI.cpp)
# if(TARGET ${PROJECT_NAME}-test)
#   target_link_libraries(${PROJECT_NAME}-test ${PROJECT_NAME})
# endif()

## Add folders to be run by python nosetests
# catkin_add_nosetests(test)
