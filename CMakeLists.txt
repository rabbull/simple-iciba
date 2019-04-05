cmake_minimum_required(VERSION 3.10)
project(iciba)

set(CMAKE_CXX_STANDARD 17)

add_compile_options(-Ofast)

include_directories(./include)

add_executable(icibaapi src/main.cpp)