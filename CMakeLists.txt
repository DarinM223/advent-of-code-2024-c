cmake_minimum_required(VERSION 3.0)
project(advent_of_code_2024)

file(GLOB_RECURSE sources stb_ds.h utils.h day1.h day1.c main.c)

add_executable(aoc ${sources})