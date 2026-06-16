cmake_minimum_required(VERSION 3.14)
project(leetcode_125 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(leetcode_125 main.cpp)
target_compile_options(leetcode_125 PRIVATE -fsanitize=address -fno-omit-frame-pointer)
target_link_options(leetcode_125 PRIVATE -fsanitize=address)
