#include <errno.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "lib.h"

char err_msg[ERR_MSG_SIZE] = {0};

void set_err_msg(const char *msg, ...)
{
    va_list args;
    va_start(args, msg);
    vsnprintf(err_msg, ERR_MSG_SIZE - 1, msg, args);
    va_end(args);
}

void format_duration(char *buf, int buf_size, double seconds)
{
    char *s = "s";
    char *ms = "ms";
    char *us = "µs";
    char *ns = "ns";

    char *labels[] = {
        s,
        ms,
        us,
        ns,
    };

    int i;
    for (i = 0; i < 4; i++)
    {
        if (seconds > 1e-3)
            break;
        seconds *= 1000;
    }
    snprintf(buf, buf_size, "%.3f%s", seconds, labels[i]);
}

int read_file_to_buffer(char **buf, const char *filename)
{
    *buf = NULL;
    int rval;

    // open the file
    FILE *f = fopen(filename, "rb");
    if (f == NULL)
    {
        set_err_msg("unable to open file: %s", strerror(errno));
        goto err_cleanup;
    }

    // get the length
    if (fseek(f, 0L, SEEK_END))
    {
        set_err_msg("unable to seek file: %s");
        goto err_cleanup;
    }
    long filesize = ftell(f);
    if (filesize < 0)
    {
        set_err_msg("unable to get file size: %s", strerror(errno));
        goto err_cleanup;
    }
    rewind(f);

    // allocate the buffer
    *buf = calloc(filesize + 1, sizeof(char));
    if (*buf == NULL)
    {
        set_err_msg("unable to allocate buffer for file read: %s", strerror(errno));
        goto err_cleanup;
    }

    // read the file into the buffer
    size_t rd = fread(*buf, 1, filesize, f);
    if (rd < filesize)
    {
        if (ferror(f))
        {
            set_err_msg("unable to read entire file: %s", strerror(errno));
            goto err_cleanup;
        }
        set_err_msg("read %d bytes, expected %d", rd, filesize);
        goto err_cleanup;
    }

    rval = rd;
    goto cleanup;

err_cleanup:
    rval = -1;
    if (*buf != NULL)
        free(*buf);
    *buf = NULL;
cleanup:
    if (f != NULL)
        fclose(f);
    return rval;
}
