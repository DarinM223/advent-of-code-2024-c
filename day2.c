#include "day2.h"
#include "stb_ds.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 256

int aoc_day2_part1(FILE *file)
{
    size_t total_safe = 0;
    char line[BUFFER_SIZE];
    while (fgets(line, BUFFER_SIZE, file)) {
        bool safe = true;
        int prev_level = atoi(strtok(line, " "));
        int prev_diff = 0;
        char *level_str;
        while ((level_str = strtok(NULL, " ")) != NULL) {
            int level = atoi(level_str);
            int diff = level - prev_level;
            bool same_sign = prev_diff == 0 || (prev_diff < 0 ? diff < 0 : diff >= 0);
            if (diff == 0 || abs(diff) > 3 || !same_sign) {
                safe = false;
                break;
            }

            prev_level = level;
            prev_diff = diff;
        }
        if (safe) {
            total_safe++;
        }
    }
    return total_safe;
}

bool aoc_is_safe_with_removed(int *levels, int levels_size)
{
    for (int removed_index = 0; removed_index < levels_size; removed_index++) {
        bool safe = true;
        bool first = true;
        int prev_level;
        int prev_diff = 0;
        for (int i = 0; i < levels_size; i++) {
            // Ignore removed element.
            if (i == removed_index) {
                continue;
            }

            if (first) {
                first = false;
                prev_level = levels[i];
            } else {
                int level = levels[i];
                int diff = level - prev_level;
                bool same_sign = prev_diff == 0 || (prev_diff < 0 ? diff < 0 : diff >= 0);
                if (diff == 0 || abs(diff) > 3 || !same_sign) {
                    safe = false;
                    break;
                }

                prev_level = level;
                prev_diff = diff;
            }
        }
        if (safe) {
            return safe;
        }
    }
    return false;
}

int aoc_day2_part2(FILE *file)
{
    size_t total_safe = 0;
    char line[BUFFER_SIZE];
    while (fgets(line, BUFFER_SIZE, file)) {
        int *levels = NULL;
        arrput(levels, atoi(strtok(line, " ")));
        char *level_str;
        while ((level_str = strtok(NULL, " ")) != NULL) {
            arrput(levels, atoi(level_str));
        }
        if (aoc_is_safe_with_removed(levels, arrlen(levels))) {
            total_safe++;
        }
        arrfree(levels);
    }
    return total_safe;
}