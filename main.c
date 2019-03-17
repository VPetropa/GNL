#include "libft/libft.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

int	get_next_line(const int fd, char **line);
	
int     main(int argc, char **argv)
{
	char *heap_line;
	int fd;
	int line = 0;
	int gnl_result;

	if (argc == 2)
	{
		fd = open(argv[1], O_RDONLY);
		printf("1st step - FD is %d\n", fd);
		while ((gnl_result = get_next_line(fd, &heap_line)) > 0)
		{
			printf("Result %d, Line #%d: %s\n", gnl_result, line++, heap_line);
			free(heap_line);
		}
		printf("Result %d, Line #%d: %s\n", gnl_result, line++, heap_line);
		if (gnl_result == -1)
			printf("Error\n");
		if (gnl_result == 0)
			printf("End of file\n");
		close(fd);
	}
	if (argc == 1)
	{
		while ((gnl_result = get_next_line(0, &heap_line)) > 0)
			printf("Return: %d, Line #%d: %s\n", gnl_result, line++, heap_line);
		if (gnl_result == -1)
			printf("Error\n");
		else if (gnl_result == 0)
			printf("End of stdin\n");
		close(fd);
	}
	return(0);
}
