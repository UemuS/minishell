#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
#  define BUFFER_SIZE 32
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include "libft/libft.h"

int			get_next_line(int fd, char **line);
char		*ft_substr(char const *s, unsigned int start, size_t len);
char		*ft_strdup(const char *s1);
char        *ft_strchr(const char *s, int c);

#endif