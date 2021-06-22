/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yihssan <yihssan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 14:40:05 by laafilal          #+#    #+#             */
/*   Updated: 2021/06/16 17:02:42 by yihssan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	get_back_tohead(t_minishell *mysh)
{
	while (mysh->cmd && mysh->cmd->prev)
		mysh->cmd = mysh->cmd->prev;
}

int	check_if_dir(char *msg, t_cmd *cmd, t_minishell *mysh, t_exec *exec)
{
	DIR		*dir;

	dir = opendir(cmd->str);
	if (dir != NULL)
	{
		err_print(cmd->str, msg, NULL);
		closedir(dir);
		free_all(exec->paths);
		free_all(exec->env);
		x_free(mysh);
		return (1);
	}
	return (0);
}

void	err_print(char *s1, char *s2, char *s3)
{
	int	fd;

	fd = dup(STDOUT_FILENO);
	dup2(STDERR_FILENO, STDOUT_FILENO);
	write(2, "minishell ", ft_strlen("minishell "));
	if (s1)
	{
		write(2, ": ", ft_strlen(": "));
		write(2, s1, ft_strlen(s1));
	}
	if (s2)
	{
		write(2, ": ", ft_strlen(": "));
		write(2, s2, ft_strlen(s2));
	}
	if (s3)
	{
		write(2, ": ", ft_strlen(": "));
		write(2, s3, ft_strlen(s3));
	}
	write(2, "\n", ft_strlen("\n"));
	dup2(STDOUT_FILENO, fd);
	close(fd);
}

int	sig_interuption(int *status, t_cmd *cmd, t_minishell *mysh)
{
	if (*status == 3 && !cmd->pipe)
	{
		write(1, "Quit: ", 6);
		write(1, "3", 1);
		write(1, "\n", 1);
		ft_fillseenv(mysh, "?", "131");
		return (1);
	}
	if (*status == 2 && !cmd->pipe)
	{
		write(1, "\n", 1);
		ft_fillseenv(mysh, "?", "130");
		return (1);
	}
	return (0);
}

void	echo_special_case(t_cmd *cmd, t_minishell *mysh)
{
	int		k;
	char	*tmp;

	if (!cmd->pipe && g_sig_flag == 0 && !ft_strcmp(cmd->args[0], "echo")
		&& cmd->args[1] && !ft_strcmp(cmd->args[1], "-n"))
	{
		k = 2;
		free(mysh->term.echo_line);
		mysh->term.echo_line = ft_strdup("");
		while (cmd->args[k])
		{
			tmp = ft_strjoin(mysh->term.echo_line, cmd->args[k]);
			free(mysh->term.echo_line);
			mysh->term.echo_line = ft_strjoin(tmp, " ");
			free(tmp);
			k++;
		}
		tmp = ft_strtrim(mysh->term.echo_line, " ");
		free(mysh->term.echo_line);
		mysh->term.echo_line = ft_strdup(tmp);
		free(tmp);
	}
}
