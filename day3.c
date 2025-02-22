#include "day3.h"
#include <stdbool.h>
#include <stdlib.h>

#define PARSE_SIZE 10

void aoc_update_state(int *, char);

void aoc_handle_char(int *state, char ch, char expected, int transition)
{
    if (ch == expected) {
        *state = transition;
    } else {
        *state = 0;
        aoc_update_state(state, ch);
    }
}

void aoc_update_state(int *state, char ch)
{
    switch (*state) {
    case 1:
        aoc_handle_char(state, ch, 'u', 2);
        break;
    case 2:
        aoc_handle_char(state, ch, 'l', 3);
        break;
    case 3:
        aoc_handle_char(state, ch, '(', 4);
        break;
    case 5:
        aoc_handle_char(state, ch, 'o', 6);
        break;
    case 6:
        if (ch == '(') {
            *state = 7;
        } else if (ch == 'n') {
            *state = 9;
        } else {
            *state = 0;
            aoc_update_state(state, ch);
        }
        break;
    case 7:
        aoc_handle_char(state, ch, ')', 8);
        break;
    case 9:
        aoc_handle_char(state, ch, '\'', 10);
        break;
    case 10:
        aoc_handle_char(state, ch, 't', 11);
        break;
    case 11:
        aoc_handle_char(state, ch, '(', 12);
        break;
    case 12:
        aoc_handle_char(state, ch, ')', 13);
        break;
    default:
        *state = ch == 'd' ? 5 : ch == 'm';
        break;
    }
}

bool aoc_parse_mul(char *parse, int *diff, long int *num1, long int *num2)
{
    char *endptr, *endptr2;
    *num1 = strtol(parse, &endptr, 10);
    *diff = endptr - parse;
    if (endptr == parse || *endptr != ',') {
        return false;
    }

    *num2 = strtol(endptr + 1, &endptr2, 10);
    *diff = endptr2 - parse;
    if (endptr2 == endptr + 1 || *endptr2 != ')') {
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
    while ((ch = getc(file)) != EOF) {
        aoc_update_state(&state, ch);
        if (state == 4 && fgets(parse, PARSE_SIZE, file)) {
            int diff;
            long int num1, num2;
            if (aoc_parse_mul(parse, &diff, &num1, &num2)) {
                total += num1 * num2;
            }
            // Rewind extra characters taken.
            int rewind_size = PARSE_SIZE - diff;
            fseek(file, ftell(file) - rewind_size, SEEK_SET);
        }
    }
    return total;
}

int aoc_day3_part2(FILE *file)
{
    long int total = 0;
    bool enabled = true;
    int state = 0;
    int ch;
    char parse[PARSE_SIZE];
    while ((ch = getc(file)) != EOF) {
        aoc_update_state(&state, ch);
        if (state == 4 && fgets(parse, PARSE_SIZE, file)) {
            int diff;
            long int num1, num2;
            if (aoc_parse_mul(parse, &diff, &num1, &num2) && enabled) {
                total += num1 * num2;
            }
            // Rewind extra characters taken.
            int rewind_size = PARSE_SIZE - diff;
            fseek(file, ftell(file) - rewind_size, SEEK_SET);
        } else if (state == 8) {
            enabled = true;
        } else if (state == 13) {
            enabled = false;
        }
    }
    return total;
}