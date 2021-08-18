cmake_minimum_required(VERSION 3.16)
project(untitled)

include_directories(./includes/headers)
include_directories(./includes/source)

set(CMAKE_CXX_STANDARD 14)

add_executable(untitled WIN32 main.cpp includes/headers/BaseWindow.h)