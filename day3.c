#include <stdbool.h>
#include <stdlib.h>
#include "day3.h"

#define PARSE_SIZE 10

void aoc_update_state(int *state, char ch)
{
    switch (*state)
    {
    case 1:
        if (ch == 'u')
        {
            *state = 2;
        }
        else
        {
            *state = 0;
            aoc_update_state(state, ch);
        }
        break;
    case 2:
        if (ch == 'l')
        {
            *state = 3;
        }
        else
        {
            *state = 0;
            aoc_update_state(state, ch);
        }
        break;
    case 3:
        if (ch == '(')
        {
            *state = 4;
        }
        else
        {
            *state = 0;
            aoc_update_state(state, ch);
        }
        break;
    default:
        *state = ch == 'm';
        break;
    }
}

bool aoc_parse_mul(char *parse, int *diff, long int *num1, long int *num2)
{
    char *endptr, *endptr2;
    *num1 = strtol(parse, &endptr, 10);
    *diff = endptr - parse;
    if (endptr == parse || *endptr != ',')
    {
        return false;
    }

    *num2 = strtol(endptr + 1, &endptr2, 10);
    *diff = endptr2 - parse;
    if (endptr2 == endptr + 1 || *endptr2 != ')')
    {
        return false;
    }
    return true;
}

int aoc_day3_part1(FILE *file)
{
    long int total = 0;
    int state = 0;
    int ch;
    char parse[PARSE_SIZE];
    while ((ch = getc(file)) != EOF)
    {
        aoc_update_state(&state, ch);
        if (state == 4 && fgets(parse, PARSE_SIZE, file))
        {
            int diff;
            long int num1, num2;
            if (aoc_parse_mul(parse, &diff, &num1, &num2))
            {
                total += num1 * num2;
            }
            // Rewind extra characters taken.
            int rewind_size = PARSE_SIZE - diff;
            fseek(file, ftell(file) - rewind_size, SEEK_SET);
        }
    }
    return total;
}

int aoc_day3_part2(FILE *)
{
    return 0;
}