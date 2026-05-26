cmake_minimum_required(VERSION 3.20)
project(esercitazione10)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wshadow -Werror=vla")

add_executable(main  main.cpp)
target_include_directories(main PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}") 