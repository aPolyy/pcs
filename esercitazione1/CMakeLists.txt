cmake_minimum_required(VERSION 3.20)
project(passo2) 
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wshadow")

add_executable(lettura_parametri lettura_parametri.cpp)
add_executable(lettura_file lettura_file.cpp)
