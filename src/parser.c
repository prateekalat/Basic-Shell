#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/utsname.h>
#include <unistd.h>
#include "../lib/parser.h"
#include <ctype.h>

char *trimwhitespace(char *str)
{
  char *end;

  /*Trim leading space*/
  while(isspace((unsigned char)*str)) str++;

  if(*str == 0)  // All spaces?
    return str;

  /*Trim trailing space*/
  end = str + strlen(str) - 1;
  while(end > str && isspace((unsigned char)*end)) end--;

  /*Write new null terminator*/
  *(end+1) = 0;

  return str;
}

int parse(char *input_string, char** argv)
{
	const char delim[2] = " ";

	/*Trimming the string by removing the leading
	and triling spaces or tabspaces*/
	input_string = trimwhitespace(input_string);
	
	/*Mallocing each pointer in the pointer
	array some space to hold the string*/
	int i;
	for (i=0 ; i < MAX_ARGS ; i++)
	{
		argv[i] = (char *)malloc(sizeof(char)*1024);
	}

	/*If the input string is emepty*/
	if (*input_string == 0)
	{
		return -1;
	}

	/*Populating the array of strings with
	the arguments and flags*/
	argv[0] = strtok(input_string, delim);
	i=1;
	while(argv[i-1] != NULL)
	{
		argv[i] = strtok(NULL, delim);
		i++;
	}
	return i;
}