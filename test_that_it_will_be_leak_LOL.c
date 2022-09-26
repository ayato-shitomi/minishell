#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

/*
 * NOTE
 *
 * - run `gcc FILE_NAME` to build.
 * - run `ps | grep a.out` to get PID.
 * - run `leak PID`. to check this program making leaks.
 *
 * >>> WE WERE NOT MAKING MISTAKES <<<
 *
*/

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
