#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#ifndef IO_REDIRECT_H
#define IO_REDIRECT_H

#define WRITE O_WRONLY | O_CREAT | O_TRUNC
#define APPEND O_APPEND | O_CREAT

void change_stdin(char *path);

void change_stdout(char *path, int flag);

void pipe_handler(char **args);

#endif