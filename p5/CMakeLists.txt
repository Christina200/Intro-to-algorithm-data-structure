cmake_minimum_required(VERSION 3.16)
project(p5)

set(CMAKE_CXX_STANDARD 14)

add_executable(p5 Dlist.h DlistImpl.h Instr.h test.cpp)