#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "../lib/exec_proc.h"
#include "../lib/builtin.h"
#include "../lib/io_redirect.h"

/**
  * Id of builtin command
  */
int builtin_id(char *name)
{
	int i;
	for (i = 0 ; i < NUM_BUILTIN ; i++)
	{
		if (strcmp(builtins[i], name) == 0)
			return i;
	}

	return -1;
}

int exec_in_proc(char **argv, char *path)
{
	int id = builtin_id(argv[0]);

	int fd0,fd1,fd2,in=0,out=0, outappend = 0;
	char input[64],output[64], append[64];


	int i = 0;
	while (argv[i] != NULL)
	{
		// printf("%s | %d\n", argv[i], strcmp(argv[i], "|"));
		// printf("%s > %d\n", argv[i], strcmp(argv[i], ">"));
		// printf("%s < %d\n", argv[i], strcmp(argv[i], "<"));


		if (strcmp(argv[i], "|") == 0)
		{
			pipe_handler(argv);
			return 0;
		}
		if(strcmp(argv[i],">")==0)
		{
			argv[i]=NULL;
			strcpy(output,argv[i+1]);
			out=1;
			i++;
			continue;
		}  

		if(strcmp(argv[i],"<")==0)
		{     
			argv[i]=NULL;
			strcpy(input,argv[i+1]);
			in=1; 
			i++;
			continue;
		}

		if(strcmp(argv[i],">>")==0)
		{ 
			argv[i]=NULL;
			strcpy(append,argv[i+1]);
			outappend=1;
			i++;
			continue;
		}


		i++;

		// printf("next %s\n", argv[i]);
	} 	

	// printf("Input: %s, Output: %s\n", input, output);

	if(in)
	{   
		int fd0;
		if ((fd0 = open(input, O_RDONLY, 0)) < 0) 
		{
			perror("Couldn't open input file");
			exit(0);
		}           
		dup2(fd0, 0); // STDIN_FILENO here can be replaced by 0 

		close(fd0); // necessary
	}

	if (out)
	{

		int fd1;
		if ((fd1 = creat(output , 0644)) < 0) 
		{
			perror("Couldn't open the output file");
			exit(0);
		}           

		dup2(fd1, STDOUT_FILENO); // 1 here can be replaced by STDOUT_FILENO
		close(fd1);
	}

	if (outappend)
	{
		int fd2 = open(append, O_WRONLY|O_APPEND,0600);
		dup2(fd2, STDOUT_FILENO); // 1 here can be replaced by STDOUT_FILENO
		close(fd2);	
	}


	if (id > 0)
	{
		strcat(path, argv[0]); // ../bin/name
		if (execvp(path, argv))
		{
			return 0;
		} else {
			return 1;
		}
	}
	else {
		if (argv[1] == NULL) { 
			argv[1] = "";
			argv[2] = NULL;
		}
		if (execvp(argv[0], argv+1) != -1) {
			return 0;
		} else {
			return 1;
		}
	}
}

int exec_bg(char **argv, char *path)
{
	pid_t pid = fork();

	if (pid == 0) {
		return exec_in_proc(argv, path);
	}

	return 0;
}

int exec(char **argv, char *path)
{
	int i=0;
	char cwd[1024];

	exec_bg(argv, path);
	wait(NULL);
}