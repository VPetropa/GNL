#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

//# include "libft/libft.h"

# define MAX_FD 1024 + 1 //1024 is the max FD for linux
# define BUFF_SIZE 10
# define BYTES_READ(bytes_read) bytes_read > 0 ? 1 : bytes_read

int	get_next_line(const int fd, char **line);

#endif
