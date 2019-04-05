cmake_minimum_required(VERSION 3.10)
project(simple-iciba)

set(CMAKE_CXX_STANDARD 17)

add_compile_options(-Ofast)

include_directories(./include)

add_executable(simple-iciba src/main.cpp)