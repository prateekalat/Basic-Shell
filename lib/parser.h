#ifndef PARSER_H
#define PARSER_H

#define MAX_ARGS 10

/**
  * Takes an input string and a pointer to a string array to populate.
  * 
  * Returns the size of the array
  */
int parse(char *input_string, char **argv);

#endif