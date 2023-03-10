cmake_minimum_required(VERSION 3.16)

project(CROSSI)



add_executable(${PROJECT_NAME}      src/dcu.cpp
                                    src/capture.cpp
                                    src/handler.cpp
                                    src/list.cpp
                                    src/decode.cpp
                                    src/config.cpp
                                    src/msggen.cpp
                                    src/fileHasher.cpp
                                    src/msgBuilder.cpp
                                    src/loadROSMsg.cpp
                                    
                                    src/dcu.h
                                    src/capture.h
                                    src/list.h
                                    src/decode.h
                                    src/ring.h
                                    src/config.h
                                    src/msggen.h
                                    src/fileHasher.h
                                    src/msgBuilder.h
                                    src/loadROSMsg.h)

add_definitions(-DEFAULT_CONFIG_PATH="/home/maximilian/Git/CROSSI/config/crossi_config.txt")

add_subdirectory(src/external/dbcppp)

target_link_libraries(${PROJECT_NAME} libdbcppp)

target_link_libraries(${PROJECT_NAME} pthread)

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)

target_compile_options(${PROJECT_NAME}  PRIVATE -g)
