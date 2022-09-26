#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
int	main(void)
{
	char *p;

	while (1)
	{
		p = malloc(10);
		printf("%p\n", p);
		sleep(5);
	}
	return (0);
}
