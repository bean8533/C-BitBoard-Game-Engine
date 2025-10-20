cmake_minimum_required(VERSION 4.0)
project(cs3503_project_1 C)

set(CMAKE_C_STANDARD 11)

add_executable(cs3503_project_1
        main.c
        bitboard.c
        bitboard.h
        checkers.c
        checkers.h)