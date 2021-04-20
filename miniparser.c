#include "miniparser.h"

int main()
{
    t_pars pars;
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


int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] == s2[i])
	{
		if (s1[i] == '\0' && s2[i] == '\0')
			return (0);
		i++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

void	type_arg(t_token *token, int separator)
{
	if (ft_strcmp(token->str, "") == 0)
		token->type = EMPTY;
	else if (ft_strcmp(token->str, ">") == 0 && separator == 0)
		token->type = TRUNC;
	else if (ft_strcmp(token->str, ">>") == 0 && separator == 0)
		token->type = APPEND;
	else if (ft_strcmp(token->str, "<") == 0 && separator == 0)
		token->type = INPUT;
	else if (ft_strcmp(token->str, "|") == 0 && separator == 0)
		token->type = PIPE;
	else if (ft_strcmp(token->str, ";") == 0 && separator == 0)
		token->type = END;
	else if (token->prev && token->prev->type >= TRUNC && token->prev->type <= INPUT)
		token->type = ARG;
	else if (token->prev == NULL || token->prev->type >= TRUNC)
		token->type = CMD;
	else
		token->type = ARG;
}

void	ft_skip_space(const char *str, int *i)
{
	while ((str[*i] == ' ' || str[*i] == '\t')
	|| (str[*i] == '\r' || str[*i] == '\v' || str[*i] == '\f'))
		(*i)++;
}

int		alloc_str(char *line, int *i)
{
	int		count;
	int		j;
	char	c;

	count = 0;
	j = 0;
	c = ' ';
	while (line[*i + j] && (line[*i + j] != ' ' || c != ' '))
	{
		if (c == ' ' && (line[*i + j] == '\'' || line[*i + j] == '\"'))
			c = line[*i + j++];
		else if (c != ' ' && line[*i + j] == c)
		{
			count += 2;
			c = ' ';
			j++;
		}
		else
			j++;
		if (line[*i + j - 1] == '\\')
			count--;
		if (line[*i + j - 1] == '\\' && line[*i +j] == ' ')
		{
			j++;
			count++;
		}
	}
	return (j - count + 1);
}

int		dblquotes(char c)
{
	if (c == '\'' || c == '$')
		return(1);
	else
		return(0);
}

t_token	*next_token(char *line, int *i)
{
	t_token	*token;
	int		j;
	char	c;

	j = 0;
	c = ' ';
	token = malloc(sizeof(t_token));
	if (!token)
		return(NULL);
	token->str = malloc(sizeof(char) * alloc_str(line, i));
	if (!token->str)
		return(NULL);
	while (line[*i] && (line[*i] != ' ' || c != ' '))
	{
		if (c == ' ' && (line[*i] == '\'' || line[*i] == '\"'))
			c = line[(*i)++];
		else if (c != ' ' && line[*i] == c)
		{
			c = ' ';
			(*i)++;
		}
		else if (line[*i] == '\\')
		{
			/* Single and double quotes checker should be added here*/
			if (quotes(line, *i) != 2 && (quotes(line, *i) != 1 || (line[(*i) + 1] && dblquotes(line[(*i) + 1]))))
				(*i)++;
			token->str[j++] = line[(*i)++];
		}
		else
			token->str[j++] = line[(*i)++];
	}
	token->str[j] = '\0';
	return (token);
}

t_token	*split_tok(char *line)
{
	t_token	*prev;
	t_token	*next;
	int		i;
	int		sep;

	prev = NULL;
	next = NULL;
	i = 0;
	ft_skip_space(line, &i);
	while (line[i])
	{
		sep = ignore_sep(line, i);
		next = next_token(line, &i);
		next->prev = prev;
		if (prev)
			prev->next = next;
		prev = next;
		type_arg(next, sep);
		ft_skip_space(line, &i);
	}
	if (next)
		next->next = NULL;
	while (next && next->prev)
		next = next->prev;
	return (next);
}

void		resetlst(t_pars *pars)
{
	while (pars->start && pars->start->prev)
		pars->start = pars->start->prev;
}


int		isnotcmd(char *str)
{
	if (!ft_strcmp(str, "echo") || !ft_strcmp(str, "ls") ||
		!ft_strcmp(str, "pwd") || !ft_strcmp(str, "unset") ||
			!ft_strcmp(str, "wc") || !ft_strcmp(str, "env") ||
			!ft_strcmp(str, "export") || !ft_strcmp(str, "cd"))
		return(0);
	return(1);
}

void	fill_tok(t_pars *pars, t_token *tok, char *line)
{
	pars->start = split_tok(line);
}

void	unexpectedtoken(char *str)
{
	char *ret;
	ret = ft_strjoin("syntax error near unexpected token ", str);
	ft_putendl_fd(ret, STDERR);
	if(ret)
		free(ret);
}

int		checksyntaxe(t_token *start)
{
	while(start)
	{
		if(!start->prev && start->type >= 6)
		{		
			unexpectedtoken(start->str);
			return(1);
		}
		if(start->next && start->type >= 3 && start->next->type >= 3)
		{
			unexpectedtoken(start->str);
			return(1);
		}
		else if (!start->next)
		{
			if(start->type >= 3 && start->type <= 6)
			{
				unexpectedtoken(start->str);
				return(1);
			}
			else
				break;
		}
		start = start->next;
	}
	return(0);
}

int		echoflag(t_token *flag)
{
	char	*str;
	int		i;
	if(!ft_strcmp(flag->str,"echo")  && flag->next && flag->next->type == 2)
	{
		str = flag->next->str;
		if(!ft_strncmp(str,"-n", 2))
		{
			i = 1;
			while(str[++i])
			{
				if (str[i] != 'n')
					return(0);
			}
			return(1);
		}
	}
	return(0);
}

void	removecmd(t_token *start)
{
	while (start)
	{
		if (start->type == 1 && isnotcmd(start->str))
		{
			start->type = 9;
			while(start->next && start->next->type <= 5)
			{
				if (start->next->next)
				{
					start->next = start->next->next;
					start->next->prev = start; 
				}
				else
					start->next = NULL;
			}
		}
		else if(echoflag(start))
			start->next->type = 8;
		start = start->next;
	}
}

void	printtokens(t_pars *pars)
{
	while(pars->start)
	{
		printf("\033[0;34m\033[1mToken : \033[0;37m%s| \033[0;34m\033[1m type :  \033[0m", pars->start->str);
		printf("%-10d\n", pars->start->type);
		if(pars->start->next)
			pars->start = pars->start->next;
		else
			break;
	}
	/* FOR BACKWARD
	while(pars->start)
	{
		printf("%s\n", pars->start->str);
		if(pars->start->prev)
			pars->start = pars->start->prev;
		else
			break;
	}*/

	/* until here */
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
	fill_tok(pars, tok, line);
	if (checksyntaxe(pars->start))
		return ;
	resetlst(pars);
	removecmd(pars->start);
	printtokens(pars);
}