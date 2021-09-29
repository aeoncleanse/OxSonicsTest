cmake_minimum_required(VERSION 3.21)
project(OxSonics)

set(CMAKE_CXX_STANDARD 17)

add_executable(OxSonics main.cpp device.hpp fetchLoop.hpp Queue.cpp Queue.hpp)
