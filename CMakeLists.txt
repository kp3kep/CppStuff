cmake_minimum_required(VERSION 4.0)
project(inheritance_1)

set(CMAKE_CXX_STANDARD 26)

# Add debug flags for C++ compiler
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g")

add_executable(inheritance_1 pure_virtual_f.cpp)