cmake_minimum_required(VERSION 2.8)

project(Blackjack CXX)
set (CMAKE_CXX_STANDARD 11)

file(GLOB SOURCES "Src/*.cpp")

add_executable(${PROJECT_NAME}.run "main.cpp" ${SOURCES})
target_include_directories(${PROJECT_NAME}.run PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/Inc)
