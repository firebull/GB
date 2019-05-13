cmake_minimum_required(VERSION 2.8)

project(Blackjack)
file(GLOB SOURCES "Src/*.cpp")
include_directories(Inc)

add_executable(${PROJECT_NAME} "main.cpp")
