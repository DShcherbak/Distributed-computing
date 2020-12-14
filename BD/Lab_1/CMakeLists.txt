cmake_minimum_required(VERSION 3.17)
project(Lab_1 C)

set(CMAKE_C_STANDARD 99)

add_executable(Lab_1 main.c
        binary_files.h binary_files.c
        operations.h operations.c
        io_functions.h io_functions.c
        movie_database.h movie_database.c)