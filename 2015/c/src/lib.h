#ifndef E3B0C442_AOC_2015_LIB_H
#define E3B0C442_AOC_2015_LIB_H

#define ERR_MSG_SIZE 256

extern char err_msg[ERR_MSG_SIZE];

void set_err_msg(const char *error, ...);
void format_duration(char *buf, int buf_size, double seconds);
int read_file_to_buffer(char **buf, const char *filename);

#endif // E3B0C442_AOC_2015_LIB_H
