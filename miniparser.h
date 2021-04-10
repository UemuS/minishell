#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <fcntl.h>
# include <dirent.h>
# include <sys/wait.h>
# include <limits.h>
# include <errno.h>
# include <signal.h>
# include <ncurses.h>
# include "get_next_line.h"

# define STDIN 0
# define STDOUT 1
# define STDERR 2
# define MAX_INT 2147483647
# define EXP -122

typedef struct	s_token
{
	char			*str;
	int				type;
	struct s_token	*prev;
	struct s_token	*next;
}				t_token;

typedef struct	s_pars
{
	t_token			*start;
	int				in;
	int				out;
	int				fdin;
	int				fdout;
	int				pipin;
	int				pipout;
	int				pid;
	int				charge;
	int				parent;
	int				last;
	int				ret;
	int				exit;
	int				notex;
}				t_pars;

void    parse(t_pars *minishell);
int		sep_stuff(char *line, int i);
int		ignore_sep(char *line, int i);
int		quotes(char *line, int index);
int		check_forquotes(t_pars *pars, char **line);

#endif