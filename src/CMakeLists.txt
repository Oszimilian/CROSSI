cmake_minimum_required(VERSION 3.16)

project(CROSSI)



add_executable(${PROJECT_NAME}      dcu.cpp
                                    capture.cpp
                                    handler.cpp
                                    list.cpp
                                    decode.cpp
                                    config.cpp
                                    
                                    dcu.h
                                    capture.h
                                    list.h
                                    decode.h
                                    ring.h
                                    config.h)

add_subdirectory(external/dbcppp)

target_link_libraries(${PROJECT_NAME} libdbcppp)

target_link_libraries(${PROJECT_NAME} pthread)

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)

target_compile_options(${PROJECT_NAME}  PRIVATE -g)
