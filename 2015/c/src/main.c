#include <stdio.h>
#include <string.h>
#include <time.h>
#include "days.h"
#include "lib.h"

#ifdef DAYNUM
int main(int argc, char const *argv[])
{
    if (argc < 2)
    {
        fprintf(stderr, "%s\n", "must provide path to input file");
        return 1;
    }

    clock_t start = clock();
    int rval = DAYNUM(argv[1]);
    clock_t end = clock();
    double duration = ((double)(end - start)) / CLOCKS_PER_SEC;
    char dur_buf[8] = {0};
    format_duration(dur_buf, 8, duration);
    if (rval)
    {
        fprintf(stderr, "%s\n", err_msg);
        return 1;
    }
    else
    {
        printf("\tCompleted in %s\n", dur_buf);
    }

    return 0;
}
#else  // #ifdef DAYNUM
typedef int (*day_f)(const char *);

static const int days_len = 1;
static const day_f days[] = {
    day1,
};
static char path[FILENAME_MAX];

int main(int argc, char const *argv[])
{
    if (argc < 2)
    {
        fprintf(stderr, "%s\n", "must provide path to input files");
        return 1;
    }

    if (strlen(argv[1]) > FILENAME_MAX - 8)
    {
        fprintf(stderr, "%s\n", "input path too long");
        return 1;
    }

    printf("Advent of Code 2015\n");
    clock_t start = clock();
    char dur_buf[8] = {0};

    for (int i = 0; i < days_len; i++)
    {
        sprintf(path, "%s/%d.txt", argv[1], i + 1);

        clock_t day_start = clock();
        int rval = days[i](path);
        clock_t day_end = clock();
        double day_duration = ((double)(day_end - day_start)) / CLOCKS_PER_SEC;
        format_duration(dur_buf, 8, day_duration);
        if (rval)
        {
            fprintf(stderr, "%s\n", err_msg);
            return rval;
        }
        else
        {
            printf("\tCompleted in %s\n", dur_buf);
        }
    }
    clock_t end = clock();
    double duration = ((double)(end - start)) / CLOCKS_PER_SEC;
    format_duration(dur_buf, 8, duration);
    printf("All puzzles completed in %s\n", dur_buf);
    return 0;
}
#endif // #ifdef DAYNUM
