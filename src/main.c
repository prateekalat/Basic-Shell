#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/utsname.h>
#include <unistd.h>
#include "../lib/parser.h"
#include "../lib/exec_proc.h"
#include "../lib/io_redirect.h"

int main()
{
	char path[100];
	FILE *pathptr;
	pathptr=fopen("./path", "r");
	fscanf(pathptr, "%s", path);
	fclose(pathptr);
	strcat(path, "/bin/");

	char home[100];
	int count=0, i;
	for (i=0 ; i<strlen(path) ; i++)
	{
		if (path[i] == '/') count++;
		if (count == 3) break;
		home[i] = path[i];
	}

	//printf("%s\n", home);

	struct utsname unameData;
	if (uname(&unameData) == -1)
	{
		printf("uname call failed\n");
		return -1;
	}
	//printf("%s\n", unameData.sysname);
	char hostname[1024];
	hostname[1023]='\0';
	gethostname(hostname, 1023);
	//printf("%s\n", hostname);
	char cwd[1024];
	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		printf("Directory not found\n");
		return -1;
	}
	//printf("%s\n", cwd);
	char rcommand[1024];
	char **command = (char **) malloc(sizeof(char *) * MAX_ARGS);

	while(1)
	{
		if (getcwd(cwd, sizeof(cwd)) == NULL)
		{
			printf("Directory not found\n");
			return -1;
		}
		printf("<%s@%s:%s>", hostname, unameData.sysname, cwd);
		fgets(rcommand, 1024, stdin);
		int len;
		if ((len = parse(rcommand, command)) != -1)
		{
			if (strcmp(command[0], "quit") == 0)
			{
				break;
			}

			else if (strcmp(command[0], "cd") == 0)
			{
				/*cd implementation*/
				if (len == 2) chdir(home);
				else if (strcmp(command[1], "~") == 0) chdir(home);
				else chdir(command[1]);
			}

			else
			{
				if (strcmp(command[len - 2], "&") == 0)
				{
					//printf("Background\n");
					if (exec_bg(command, path) == 1)
					{
						printf("%s not found\n", command[0]);
					}
				}

				else {
					//printf("Foreground\n");
					if (exec(command, path) == 1)
					{
						printf("%s not found\n", command[0]);
					}
				}
			}
		}
	}
	return 0;
}


