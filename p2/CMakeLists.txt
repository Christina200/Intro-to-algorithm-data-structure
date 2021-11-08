cmake_minimum_required(VERSION 3.16)
project(p2)

set(CMAKE_CXX_STANDARD 14)

include_directories ("p2/include")
include_directories(C:/Users/Wei Xiwen/p2/bot.h)
add_executable(p2 bot.cpp rand.cpp rand.h constants.h bot.h main.cpp )