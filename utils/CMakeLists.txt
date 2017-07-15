cmake_minimum_required(VERSION 3.7)
project(utils)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp offset_of.h val_container.h)
add_executable(utils ${SOURCE_FILES})