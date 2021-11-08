cmake_minimum_required(VERSION 3.16)
project(p3)

set(CMAKE_CXX_STANDARD 14)

add_executable(p3 card.cpp card.h deck.h player.h rand.h rand.cpp deck.cpp hand.cpp player.cpp blackjack.cpp)