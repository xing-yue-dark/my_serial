cmake_minimum_required(VERSION 2.8.3)
project(serial)

find_package(catkin REQUIRED)

set(rt_LIBRARIES rt)
set(pthread_LIBRARIES pthread)

catkin_package(
    LIBRARIES ${PROJECT_NAME}
    INCLUDE_DIRS include
    DEPENDS rt pthread
)

set(serial_SRCS
    src/serial.cc
    include/serial/serial.h
    include/serial/v8stdint.h
    src/impl/unix.cc
    src/impl/list_ports/list_ports_linux.cc
)

add_library(${PROJECT_NAME} ${serial_SRCS})

target_link_libraries(${PROJECT_NAME} rt pthread)

include_directories(include)

add_executable(my_serials my_serial.cpp)

add_dependencies(my_serials ${PROJECT_NAME})

target_link_libraries(my_serials ${PROJECT_NAME})
