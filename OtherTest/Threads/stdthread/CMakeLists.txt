#1.cmake verson，指定cmake版本
cmake_minimum_required(VERSION 3.16)

 
#2.project name，指定项目的名称，一般和项目的文件夹名称对应
PROJECT(ThreadDemo)

# 设置指定的C++编译器版本是必须的，如果不设置，或者为OFF，则指定版本不可用时，会使用上一版本。
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 指定为C++11 版本
set(CMAKE_CXX_STANDARD 11)

# 指定版本号的配置文件
#configure_file(include/TutorialConfig.h.in TutorialConfig.h)

#ADD_DEFINITIONS
#为 C/C++ 编译器添加 -D 定义
#ADD_DEFINITIONS(-DENABLE_DEBUG -DABC)，参数之间用空格分隔
add_definitions("-DTARGET_LINUX")
add_definitions(-g)
ADD_DEFINITIONS(-D DEBUG_WARN)  
ADD_DEFINITIONS(-Os)
ADD_DEFINITIONS(-Wall)

#MESSAGE([SEND_ERROR | STATUS | FATAL_ERROR] "message to display" ...)
#向终端输出用户定义的信息或变量的值. SEND_ERROR，产生错误，生成过程被跳过;  STATUS，输出前缀为 – 的信息;  FATAL_ERROR，立即终止所有 cmake 过程

MESSAGE("STATUS " "===================${CMAKE_INSTALL_RPATH_USE_LINK_PATH}")

#link_directories(${PROJECT_SOURCE_DIR}/../../../../../lib )

INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/messagepipe)
  
 #set(CMAKE_EXE_LINKER_FLAGS -fexceptions)
#set(CMKA_SYSTRM_NAME       Linux)
#set(CMAKE_C_COMPILER       arm-linux-gnueabihf-gcc)
#set(CMAKE_C_COMPILER_TARGET ${triple})
#set(CMAKE_CXX_COMPILER       arm-linux-gnueabihf-g++)
#set(CMAKE_CXX_COMPILER_TARGET ${triple})
#set(CMAKE_AR arm-linux-gnueabihf-ar)
#set(CMAKE_arm-linux-gnueabihf-objcopy)
#set(CMAKE_OBJDUMP arm-linux-gnueabihf-objdump)

#set(CMAKE_VERBOSE_MAKEFILEON ON)
#set(CMAKE_BUILD_TYPE Debug CACHE STRING "set build type to debug")



# 查找当前目录下的所有源文件
# 并将名称保存到 DIR_SRCS 变量
#aux_source_directory(. DIR_SRCS)
AUX_SOURCE_DIRECTORY(./ DIR_SRCS)

# 自定义搜索规则
#file(GLOB SRC_LIST "*.cpp" "protocol/*.cpp")
#add_library(demo ${SRC_LIST})
# 或者
#file(GLOB SRC_LIST "*.cpp")
#file(GLOB SRC_PROTOCOL_LIST "protocol/*.cpp")
#add_library(demo ${SRC_LIST} ${SRC_PROTOCOL_LIST})
# 或者
#file(GLOB_RECURSE SRC_LIST "*.cpp") #递归搜索
#FILE(GLOB SRC_PROTOCOL RELATIVE "protocol" "*.cpp") # 相对protocol目录下搜索
#add_library(demo ${SRC_LIST} ${SRC_PROTOCOL_LIST})
# 或者
#aux_source_directory(. SRC_LIST)
#aux_source_directory(protocol SRC_PROTOCOL_LIST)
#add_library(demo ${SRC_LIST} ${SRC_PROTOCOL_LIST})
file(GLOB mythread ./*.cpp  src/framework/innermsg/*.cpp src/*.cpp)

#引入Threads外部依赖包
find_package(Threads) 
#设置编译类型

#add_executable(demo demo.cpp) # 生成可执行文件
#add_library(common STATIC util.cpp) # 生成静态库
#add_library(common SHARED util.cpp) # 生成动态库或共享库

ADD_EXECUTABLE(ThreadDemo ${DIR_SRCS} ${mythread})

#设置 target 需要链接的库
#target_link_libraries( # 目标库
                       # demo
 
                       # 目标库需要链接的库
                       # log-lib 是上面 find_library 指定的变量名
                       # ${log-lib} )

target_link_libraries(ThreadDemo pthread)




