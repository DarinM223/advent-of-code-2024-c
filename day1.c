#include <stdio.h>
#include "stb_ds.h"
#include "day1.h"

#define BUFFER_SIZE 256

int aoc_int_compare(const void *a, const void *b)
{
    return *((const int *)b) - *((const int *)a);
}

int aoc_day1_part1(FILE *file)
{
    int *left_nums = NULL;
    int *right_nums = NULL;
    char line[BUFFER_SIZE];
    while (fgets(line, BUFFER_SIZE, file))
    {
        int num1 = atoi(strtok(line, " "));
        int num2 = atoi(strtok(NULL, " "));
        arrput(left_nums, num1);
        arrput(right_nums, num2);
    }

    qsort(left_nums, arrlen(left_nums), sizeof(int), aoc_int_compare);
    qsort(right_nums, arrlen(right_nums), sizeof(int), aoc_int_compare);

    int total_distance = 0;
    for (long int i = 0; i < arrlen(left_nums); i++)
    {
        total_distance += abs(left_nums[i] - right_nums[i]);
    }

    arrfree(left_nums);
    arrfree(right_nums);
    return total_distance;
}

int aoc_day1_part2(FILE *file)
{
    int *left_nums = NULL;
    struct
    {
        int key;
        int value;
    } *right_count = NULL;

    char line[BUFFER_SIZE];
    while (fgets(line, BUFFER_SIZE, file))
    {
        int num1 = atoi(strtok(line, " "));
        int num2 = atoi(strtok(NULL, " "));
        arrput(left_nums, num1);
        int count = hmget(right_count, num2);
        hmput(right_count, num2, count + 1);
    }

    int total_similarity_score = 0;
    for (long int i = 0; i < arrlen(left_nums); i++)
    {
        int num = left_nums[i];
        int count = hmget(right_count, num);
        total_similarity_score += num * count;
    }

    arrfree(left_nums);
    hmfree(right_count);
    return total_similarity_score;
}