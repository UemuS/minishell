/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laafilal <laafilal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 14:56:31 by laafilal          #+#    #+#             */
/*   Updated: 2021/06/17 16:20:12 by laafilal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	child_process(t_minishell *mysh, t_cmd *cmd, t_exec *exec)
{
	if (exec->pid == 0)
	{
		signal(SIGINT, s_handler);
		signal(SIGQUIT, s_handler);
		exec->env = to_env(*mysh);
		mapping_fds(cmd, exec);
		check_cmd(exec, mysh, cmd);
		if (exec->err_flag == 0)
			err_print(cmd->str, "command not found", NULL);
		else
		{
			err_print(exec->err_cmd, strerror(exec->err_flag), NULL);
			free(exec->err_cmd);
		}
		free_all(exec->paths);
		free_all(exec->env);
		x_free(mysh);
		exit(127);
	}
}

void	parent_process(t_cmd *cmd, t_exec *exec)
{
	cmd->pid = exec->pid;
	if (exec->in != 0)
		close(exec->in);
	if (cmd->pipe)
	{
		close(exec->pipefd[1]);
		exec->in = exec->pipefd[0];
	}
}

void	execute_bin(t_exec *exec, t_minishell *mysh, t_cmd *cmd)
{
	int			st;

	st = 0;
	if (exec->bin != -1)
	{
		st = ft_builin_exec(mysh, exec->bin, cmd);
		free_all(exec->paths);
		free_all(exec->env);
		x_free(mysh);
		exit(st);
	}
}

void	execute_no_bin_path(t_cmd *cmd, t_minishell *mysh, t_exec *exec)
{
	struct stat	fileStat;
	char		**argg;

	if (check_if_dir("Is a directory", cmd, mysh, exec))
		exit(126);
	execve(cmd->str, cmd->args, exec->env);
	if (errno == 2)
		exec->err_flag = errno;
	if (stat(cmd->str, &fileStat) == 0 && (fileStat.st_mode & S_IXUSR))
	{
		argg = (char *[3]){"/bin/bash", cmd->str, NULL};
		execve(argg[0], argg, exec->env);
	}
	exec->err_flag = errno;
	exec->err_cmd = ft_strdup(cmd->str);
}

void	execute_no_bin(t_exec *exec, t_cmd *cmd, t_minishell *mysh, int p)
{
	struct stat	fileStat;
	char		**argg;
	char		*tmp;

	tmp = ft_strjoin(exec->paths[p], "/");
	exec->cmd_str = ft_strjoin(tmp, cmd->str);
	free(tmp);
	execve(exec->cmd_str, cmd->args, exec->env);
	if (errno != 2)
	{
		exec->err_flag = errno;
		exec->err_cmd = ft_strdup(exec->cmd_str);
	}
	if (check_if_dir("command not found", cmd, mysh, exec))
		exit(127);
	if (stat(exec->cmd_str, &fileStat) == 0 && (fileStat.st_mode & S_IXUSR))
	{
		argg = (char *[3]){"/bin/bash", cmd->str, NULL};
		execve(argg[0], argg, exec->env);
	}
	free(exec->cmd_str);
}
