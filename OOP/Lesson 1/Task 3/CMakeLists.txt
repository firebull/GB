cmake_minimum_required(VERSION 2.8)
project(StackTest CXX) # Прописываю жёстко компилятор C++
set (CMAKE_CXX_STANDARD 11)

file(GLOB SOURCES "src/*.cpp")

add_executable(stack_test.run ${SOURCES})
include_directories(inc)
target_include_directories(stack_test.run PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/inc)
