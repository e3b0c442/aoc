#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "lib.h"

static int part1(const char *input, size_t input_len)
{
    int floor = 0;
    for (int i = 0; i < input_len; i++)
    {
        switch (input[i])
        {
        case '(':
            floor++;
            break;
        case ')':
            floor--;
            break;
        default:
            set_err_msg("invalid input: %c", input[i]);
            return INT_MIN;
        }
    }

    return floor;
}

static int part2(const char *input, size_t input_len)
{
    int floor = 0;
    for (int i = 0; i < input_len; i++)
    {
        switch (input[i])
        {
        case '(':
            floor++;
            break;
        case ')':
            floor--;
            break;
        default:
            set_err_msg("invalid input: %c", input[i]);
            return -1;
        }
        if (floor == -1)
            return i + 1;
    }

    set_err_msg("solution not found");
    return -1;
}

int day1(const char *filename)
{
    printf("Day 1: Not Quite Lisp\n");

    int rval = -1;

    char *input;
    int filesize = read_file_to_buffer(&input, filename);
    if (filesize < 0)
        return 1;

    clock_t start = clock();
    int solution = part1(input, filesize);
    clock_t end = clock();
    double duration = ((double)(end - start)) / CLOCKS_PER_SEC;
    if (solution == INT_MIN)
        goto cleanup;

    char dur_buf[8] = {0};
    format_duration(dur_buf, 8, duration);
    printf("\tPart 1: %d (%s)\n", solution, dur_buf);

    start = clock();
    solution = part2(input, filesize);
    end = clock();
    duration = ((double)(end - start)) / CLOCKS_PER_SEC;
    format_duration(dur_buf, 8, duration);
    if (solution < 0)
        goto cleanup;

    printf("\tPart 2: %d (%s)\n", solution, dur_buf);
    rval = 0;

cleanup:
    free(input);
    return rval;
}
