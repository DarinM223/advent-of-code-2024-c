#include "day1.h"
#include "day2.h"
#include "day3.h"
#define STB_DS_IMPLEMENTATION
#include "stb_ds.h"

#define MAX_PATH_LEN 256

void run_day1(FILE *file)
{
    int part1 = aoc_day1_part1(file);
    printf("Day1 part1: %d\n", part1);

    // Go back to beginning of file.
    fseek(file, 0, SEEK_SET);

    int part2 = aoc_day1_part2(file);
    printf("Day2 part2: %d\n", part2);
}

void run_day2(FILE *file)
{
    int part1 = aoc_day2_part1(file);
    printf("Day2 part1: %d\n", part1);

    fseek(file, 0, SEEK_SET);

    int part2 = aoc_day2_part2(file);
    printf("Day2 part2: %d\n", part2);
}

void run_day3(FILE *file)
{
    int part1 = aoc_day3_part1(file);
    printf("Day3 part1: %d\n", part1);

    fseek(file, 0, SEEK_SET);

    int part2 = aoc_day3_part2(file);
    printf("Day3 part2: %d\n", part2);
}

int main(int argc, char *argv[])
{
    if (argc < 2) {
        printf("Expected usage: ./aoc 1 to run day 1\n");
        return 1;
    }

    char *endptr;
    long int day = strtol(argv[1], &endptr, 10);
    if (endptr == argv[1]) {
        printf("No digits were found for day\n");
        return 1;
    } else if (*endptr != '\0') {
        printf("Invalid character %c\n", *endptr);
        return 1;
    }

    char path[MAX_PATH_LEN];
    int chars_written = sprintf(path, "inputs/day%ld.txt", day);
    if (chars_written >= MAX_PATH_LEN) {
        printf("Path length is greater than max size\n");
        return 1;
    }

    FILE *file = fopen(path, "r");
    if (file == NULL) {
        printf("Cannot open input file %s\n", path);
        return 1;
    }

    switch (day) {
    case 1:
        run_day1(file);
        break;
    case 2:
        run_day2(file);
        break;
    case 3:
        run_day3(file);
        break;
    default:
        printf("Invalid day\n");
        break;
    }

    fclose(file);
}