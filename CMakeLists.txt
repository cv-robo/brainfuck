cmake_minimum_required(VERSION 3.17)
project(brainfuck C)

set(CMAKE_C_STANDARD 99)

add_executable(brainfuck main.c brainfuck.c)