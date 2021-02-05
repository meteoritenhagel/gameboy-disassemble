cmake_minimum_required(VERSION 3.17)
project(gameboy_debug)

set(CMAKE_CXX_STANDARD 17)

add_executable(gameboy_debug main.cpp disassembler.cpp disassembler.h instructions.cpp instructions.h)