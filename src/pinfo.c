#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <ctype.h>

#define SIZE 1000

int main(int argc, char **argv)
{
	int pid;

	if (argc == 1)
	{
		pid = getppid();
	}

	else
	{
		sscanf(argv[1], "%d", &pid);
	}

	long long size;
	char buffer[SIZE] = {0}, buffer2[PATH_MAX] = {0};
	char state;

	sprintf(buffer, "/proc/%d/status", pid);
	FILE *status = fopen(buffer, "r");

	while (fgets(buffer, SIZE, status), buffer[5] = '\0', strcmp(buffer, "State") != 0);

	int i = 6;
	while (!isalpha(buffer[i])) i++;
	state = buffer[i];

	while (fgets(buffer, SIZE, status), buffer[6] = '\0', strcmp(buffer, "VmSize") != 0);

	i = 0;
	while (!isdigit(buffer[i])) i++;

	sscanf(buffer + i, "%lld", &size);
	sprintf(buffer, "/proc/%d/exe", pid);
	realpath(buffer, buffer2);

	printf("PID : %d\nProcess State : %c\nMemory : %lld KB\nExecutable Path : %s\n", pid, state, size, buffer2);

	return 0;
}