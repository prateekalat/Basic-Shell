#ifndef EXEC_PROC_H
#define EXEC_PROC_H

/**
  * Executes a command in the current process
  *
  * argv MUST be null terminated
  *
  * Returns: Exit status
  */
int exec(char **argv, char *path);

/**
  * Executes a command in a background process
  *
  * argv MUST be null terminated
  *
  * Returns: PID
  */
int exec_bg(char **argv, char *path);

#endif