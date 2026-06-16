cmake_minimum_required(VERSION 3.20)
project(progetto)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wshadow -Werror=vla")
# Creo il target per l'eseguibile principale del mio progetto software

add_executable(main  main.cpp)
add_executable(time_test dfsCycles_timetest.cpp)
target_include_directories(main PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}") 