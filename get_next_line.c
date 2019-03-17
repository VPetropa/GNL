#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "get_next_line.h"
//#include "libft/libft.h"

static char	*ft_strdup(const char *s1)
{
	char	*s2;
	size_t	i;

	i = 0;
	printf("We allocate memory\n");
	while (s1[i])
		i++;
	if (!(s2 = (char *)malloc(sizeof(char) * (i + 1))))
		return (NULL);
	i = -1;
	while (s1[++i])
		s2[i] = s1[i];
	s2[i] = '\0';
	printf("The returned string from strdup is: %s\n", s2);
	return (s2);
}

static char	*ft_strjoin(char const *s1, char const *s2)
{
	char		*s3;
	char		*tmp_s3;
	size_t		i;
	size_t		j;

	j = 0;
	i = 0;
	printf("We join strings\n");
	while (s1[i])
		i++;
	while (s2[j])
		j++;
	if (!s1 || !s2 || !(s3 = (char *)malloc(sizeof(char) * (i + j + 1))))
		return (NULL);
	tmp_s3 = s3;
	while (*s1 != '\0')
		*tmp_s3++ = *s1++;
	while (*s2 != '\0')
		*tmp_s3++ = *s2++;
	*tmp_s3 = '\0';
	return (s3);
}

static int	verify_line(char **stack_text, char **line)
{
	char	*strchar_in_stack;
	char	*tmp_stack;
	int i;
	
	i = 0;
	printf("We are verifying the line\n");
	strchar_in_stack = *stack_text;
	while (strchar_in_stack[i] != '\n')
	{
		if (!strchar_in_stack[i])
			return (0);
		printf("we count bytes: %d until we reach New Line char\n", i);
		i++;
	}
	tmp_stack = &strchar_in_stack[i];
	*tmp_stack = '\0';
	*line = ft_strdup(*stack_text);
	*stack_text = ft_strdup(tmp_stack + 1);
	printf("On heap_text we have '%s'\n", *line);
	printf("On stack_text we have '%s'\n", *stack_text);
	return (1);
}

static int	gnl_read_file(int fd, char *heap, char **stack_text, char **line)
{
	int	bytes_read;
	char	*tmp_stack;

	printf("2nd or last step - We are reading file\n");
	while ((bytes_read = read(fd, heap, BUFF_SIZE)) > 0)
	{
		heap[bytes_read] = '\0';
		printf("3rd step - Result from read is %d bytes read, stack_text is %s\n", bytes_read, *stack_text);
		if (*stack_text)
		{
			printf("we are in gnl_read_file if condition\n");
			tmp_stack = *stack_text;
			*stack_text = ft_strjoin(tmp_stack, heap);
			free(tmp_stack);
			tmp_stack = 0;
		}
		else
		{
			printf("4th step - We allocate heap memory for 1st time after reading the nbytes which is the whole text file\n");
			*stack_text = ft_strdup(heap);
		}
		if (verify_line(stack_text, line))
			break;
	}
	printf("from gnl_read_file we return bytes read = %d\n", bytes_read);
	return(BYTES_READ(bytes_read));
}

int	get_next_line(const int fd, char **line)
{
	static char *stack_text[MAX_FD];
	char	*heap_text;
	int	result;
	int	i;
	
	if (!line || (fd < 0 || fd >= MAX_FD) || (read(fd,stack_text[fd], 0) < 0) || !(heap_text = (char *)malloc(sizeof(char) * BUFF_SIZE + 1)))
		return(-1);
	if (stack_text[fd])//On first call of the function, stack_text is empty so we skip this if condition
	{
		printf("On the stack in GNL we have:%s\n", stack_text[fd]);
		if (verify_line(&stack_text[fd], line))
			return(1);
	}
	i = 0;
	while (i < BUFF_SIZE)
		heap_text[i++] = '\0';
	result = gnl_read_file(fd, heap_text, &stack_text[fd], line);
	free(heap_text);
	if (result != 0 || stack_text[fd] == 0 || stack_text[fd][0] == '\0')
	{
		if (!result && *line)
			*line = 0;
		printf("1st raw, last raw!We return GNL result %d\n", result); //affected by the BUFF_SIZE how many we read
		return (result);
	}
	*line = stack_text[fd];
	stack_text[fd] = 0;
	return (1);
}

