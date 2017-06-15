cmake_minimum_required(VERSION 3.5)
project(RedBlackTree)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
#glog
#find_package(Glog REQUIRED)
set(GLOG_INCLUDE_DIRS "/usr/include")
set(GLOG_LIBRARIES_DIRS "/usr/lib/x86_64-linux-gnu")
include_directories(${GLOG_INCLUDE_DIRS})
link_directories(${GLOG_LIBRARIES_DIRS}$)

set(SOURCE_FILES main.cpp)
add_executable(RedBlackTree ${SOURCE_FILES})

target_link_libraries(RedBlackTree -lglog)
