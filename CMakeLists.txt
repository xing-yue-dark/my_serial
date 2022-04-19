cmake_minimum_required(VERSION 2.8.3)
project(serial)


# Find catkin
find_package(catkin REQUIRED)


if(APPLE)
    #查找静态，动态库
    find_library(IOKIT_LIBRARY IOKit)
    find_library(FOUNDATION_LIBRARY Foundation)
endif()

if(UNIX AND NOT APPLE)
    # If Linux, add rt and pthread
    set(rt_LIBRARIES rt)
    set(pthread_LIBRARIES pthread)
    #把当前包变成一个被ros认可的包
    #INCLUDE_DIRS  include  :包A中如果定义的有头文件文件夹的话，就把该文件夹地址传给B，作为B  camke过程中的变量A_INCLUDE_DIRS.
    #LIBRARIES  pose_estimation  :包A中生成的库文件（pose_estimation）的地址传给B，作为B  camke过程中的变量pose_estimation_LIBRARIES.
    #CATKIN_DEPENDS pcl_conversions pcl_ros roscpp sensor_msgs   :包A依赖的一些catkin程序包，可以使得B递归依赖它们，而不用手动再次在B中去依赖它们。
    #DEPENDS system_lib    ：包A中依赖的一些非catkin程序包，可以使得B递归依赖(递归查找它们的库路径，头文件路径等等)它们，而不用手动再次在B中去依赖它们。

    catkin_package(
        LIBRARIES ${PROJECT_NAME}
        INCLUDE_DIRS include
        DEPENDS rt pthread
    )
else()
    # Otherwise normal call
    catkin_package(
        LIBRARIES ${PROJECT_NAME}
        INCLUDE_DIRS include
    )
endif()

## Sources
#声明一个清单，代表什么值
set(serial_SRCS
    src/serial.cc
    include/serial/serial.h
    include/serial/v8stdint.h
)
if(APPLE)
    # If OSX
    # 用于将元素追加到列表中
    list(APPEND serial_SRCS src/impl/unix.cc)
    list(APPEND serial_SRCS src/impl/list_ports/list_ports_osx.cc)
elseif(UNIX)
    # If unix
    list(APPEND serial_SRCS src/impl/unix.cc)
    list(APPEND serial_SRCS src/impl/list_ports/list_ports_linux.cc)
else()
    # If windows
    list(APPEND serial_SRCS src/impl/win.cc)
    list(APPEND serial_SRCS src/impl/list_ports/list_ports_win.cc)
endif()



## Add serial library
add_library(${PROJECT_NAME} ${serial_SRCS})
if(APPLE)
    target_link_libraries(${PROJECT_NAME} ${FOUNDATION_LIBRARY} ${IOKIT_LIBRARY})
elseif(UNIX)
    target_link_libraries(${PROJECT_NAME} rt pthread)
else()
    target_link_libraries(${PROJECT_NAME} setupapi)
endif()


## Include headers
##将根目录添加到include的搜索路径中
include_directories(include)


## Uncomment for example
add_executable(my_serials my_serial.cpp)
#生成依赖（就是main函数里有一些变量定义在头文件中，所以要先 生成头文件再来生成mian函数）
add_dependencies(my_serials ${PROJECT_NAME})
target_link_libraries(my_serials ${PROJECT_NAME})
