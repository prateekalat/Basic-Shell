#include <stdio.h>
#include <sys/utsname.h>
#include <unistd.h>
#include "../lib/builtin.h"

int main()
{
	char cwd[1024];
	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		printf("Directory not found\n");
		return -1;
	}
	printf("%s\n", cwd);
	return 0;
}