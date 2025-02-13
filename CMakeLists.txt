cmake_minimum_required(VERSION 3.5)
project(advent_of_code_2024)

file(GLOB_RECURSE headers stb_ds.h utils.h day1.h day2.h day3.h)
file(GLOB_RECURSE sources main.c day1.c day2.c day3.c)
add_compile_options(-g -Wall -Wextra -Werror)

add_executable(aoc ${headers} ${sources})