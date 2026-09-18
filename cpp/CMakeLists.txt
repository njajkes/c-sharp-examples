cmake_minimum_required(VERSION 3.16)

project(ConsoleApp2Cpp LANGUAGES CXX)

add_executable(ConsoleApp2Cpp main.cpp)
target_compile_features(ConsoleApp2Cpp PRIVATE cxx_std_17)

if(MSVC)
    target_compile_options(ConsoleApp2Cpp PRIVATE /W4 /permissive- /utf-8)
else()
    target_compile_options(ConsoleApp2Cpp PRIVATE -Wall -Wextra -Wpedantic)
endif()
