cmake_minimum_required(VERSION 3.8)
project(UsingTmp)

set(CMAKE_CXX_STANDARD 14)
#set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O2 -fno-exceptions -fno-rtti -Wall -Werror -pedantic-errors")

#include_directories(Hypodermic)
#include_directories(fruit/include)
include_directories(di/include)


set(SOURCE_FILES
        main.cpp
        test1.h
        test2.h test3.h test4.h test5.h test6.h)
add_executable(UsingTmp ${SOURCE_FILES})