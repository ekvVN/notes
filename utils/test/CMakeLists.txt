cmake_minimum_required(VERSION 3.7)
set(PROJ test_utils)
project(${PROJ})

set(CMAKE_CXX_STANDARD 11)

enable_testing()
if(DEFINED ENV{GTEST_ROOT})  # Note we omit the $ here!
    message(" ... using gtest found in $ENV{GTEST_ROOT}")
ELSE()
    message("GTEST_ROOT is not defined. You must tell CMake where to find the gtest source")
    # exit early
    return()
endif()

find_package(GTest REQUIRED)

# Вывод установленных переменных
message("gtest include dirs: \n" ${GTEST_INCLUDE_DIRS})
message("libgtest: \n" ${GTEST_LIBRARIES})
message("libgtest-main: \n" ${GTEST_MAIN_LIBRARIES})
message("Both libgtest & libgtest-main: \n" ${GTEST_BOTH_LIBRARIES})

if(DEFINED GTEST_FOUND)  # Note we omit the $ here!
    message("${GTEST_FOUND}")
ELSE()
    message("GTEST_FOUND is not found")
    # exit early
    return()
endif()
include_directories(${GTEST_INCLUDE_DIRS})

set(SOURCE_FILES
        test_val_container.cpp
        )

add_library(${PROJ} ${SOURCE_FILES})
target_link_libraries(${PROJ} ${GTEST_BOTH_LIBRARIES})