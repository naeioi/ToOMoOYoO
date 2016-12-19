cmake_minimum_required(VERSION 2.6)
PROJECT (TMY_TEST)
# set(CMAKE_CURRENT_BINARY_DIR ${PROJECT_SOURCE_DIR}/build)
# INCLUDE_DIRECTORIES(../common)

SET(CMAKE_CXX_FLAGS  "-std=c++11")

add_executable(hello hello.cpp)
# add_executable(test_dirinfo dirinfo_t.cpp)