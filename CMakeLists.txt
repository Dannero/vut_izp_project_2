cmake_minimum_required(VERSION 3.0)
project(IZP_projekt-2 C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic")

add_executable(IZP_projekt-2 local.c)