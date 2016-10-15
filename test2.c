#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
	int	a = fork();
	if (a == -1)
		return (EXIT_FAILURE);
	else if (a == 0)
	{
		sleep(1);
		return (EXIT_SUCCESS);
	}
	int status;
	wait(&status);
	printf("test");
	return (EXIT_SUCCESS);
}
