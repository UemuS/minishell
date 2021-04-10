#include "miniparser.h"

int main()
{
    t_pars pars;

    pars.in = dup(STDIN);
	pars.out = dup(STDOUT);
	pars.exit = 0;
	pars.ret = 0;
	pars.notex = 0;
    while(pars.exit == 0)
    {
        parse(&pars);
    }
}

void	*freememory(void *ptr)
{
	if (ptr)
	{
		free(ptr);
		ptr = NULL;
	}
	return (NULL);
}

char	*space_alloc(char *line)
{
	char	*new;
	int		count;
	int		i;

	count = 0;
	i = 0;
	while (line[i])
	{
		if (sep_stuff(line, i))
			count++;
		i++;
	}
	if (!(new = malloc(sizeof(char) * (i + 2 * count + 1))))
		return (NULL);
	return (new);
}

char	*space_line(char *line)
{
	char	*new;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new = space_alloc(line);
	while (new && line[i])
	{
		if (quotes(line, i) != 2 && line[i] == '$' && i && line[i - 1] != '\\')
        {
			new[j] = (char)(-122);
            i++;
            j++;
        }
		else if (quotes(line, i) == 0 && sep_stuff(line, i))
		{
			new[j++] = ' ';
			new[j++] = line[i++];
			if (quotes(line, i) == 0 && line[i] == '>')
				new[j++] = line[i++];
			new[j++] = ' ';
		}
		else
			new[j++] = line[i++];
	}
	new[j] = '\0';
	freememory(line);
	return (new);
}

int		check_forquotes(t_pars *pars, char **line)
{
	if (quotes(*line, MAX_INT))
	{
		ft_putendl_fd("problem with quotes !", STDERR);
		freememory(*line);
		pars->ret = 2;
		pars->start = NULL;
		return (1);
	}
	return (0);
}

void    parse(t_pars *pars)
{
    t_token *tok;
    char    *line;

    ft_putstr_fd("\033[0;35m\033[1mminishell\033[0;37m$ \033[0m", STDERR);
    if (get_next_line(0, &line) < 0 && (pars->exit = 1))
		ft_putendl_fd("exit", STDERR);
    if (check_forquotes(pars, &line))
		return ;
    line = space_line(line);
    if (line && line[0] == '$')
		line[0] = (char)(-122);
    printf("%s\n", line);
}