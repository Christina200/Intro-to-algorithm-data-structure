cmake_minimum_required(VERSION 3.16)
project(p4)

set(CMAKE_CXX_STANDARD 17)

add_executable(p4 BinaryTree.h BinaryTree.cpp test.cpp NodeInfo.h)