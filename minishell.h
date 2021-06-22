/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yihssan <yihssan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 13:15:57 by laafilal          #+#    #+#             */
/*   Updated: 2021/06/16 17:10:53 by yihssan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <termios.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <curses.h>
# include <term.h>
# include <termcap.h>
# include <signal.h>
# include "libft.h"
# include <fcntl.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <dirent.h>
# include <stdbool.h>

# define SIG_NONE 0
# define STDIN 0
# define STDOUT 1
# define STDERR 2
# define MAX_INT 2147483647
# define EXP -122
# define EMPTY 0
# define CMD 1
# define ARG 2
# define TRUNC 3
# define APPEND 4
# define INPUT 5
# define PIPE 6
# define END 7
# define FLAG 8
# define FILE 10

# define B_ECHO 0
# define B_PWD 1
# define B_ENV 2
# define B_EXPORT 3
# define B_CD 4
# define B_UNSET 5
# define B_EXIT 6

# define PATH_M 1024

typedef struct s_exec
{
	int		pipefd[2];
	int		pid;
	int		in;
	int		out;
	char	**paths;
	char	*cmd_str;
	int		bin;
	int		err_flag;
	char	*err_cmd;
	char	**env;
}				t_exec;

typedef struct s_token
{
	char			*str;
	int				type;
	struct s_token	*prev;
	struct s_token	*next;
}				t_token;

typedef struct s_cmd
{
	char			*str;
	char			*input;
	char			*output;
	int				toappend;
	char			**args;
	int				pipe;
	int				ret;
	int				pid;
}				t_cmd;

typedef struct s_env
{
	char			*alias;
	char			*value;
}				t_env;

typedef struct s_pars
{
	t_token			*start;
	int				ret;
}				t_pars;

typedef struct s_d_list
{
	void			*content;
	struct s_d_list	*next;
	struct s_d_list	*prev;
}				t_d_list;

typedef struct s_hisb
{
	char	*line;
	char	*backup;
}				t_hisb;

typedef struct s_actions
{
	char	*clearstr;
	char	*gotto;
	char	*del_c;
	char	*key_back;
}				t_actions;

typedef struct s_term_infos
{
	struct termios	oldattr;
	struct termios	newattr;
	char			*terminal_type;
	int				ret;
	t_actions		action;
	t_d_list		*histories;
	t_d_list		*htmp;
	char			*line;
	char			*echo_line;
	char			*buffer;
}				t_term_infos;

typedef struct s_minishell
{
	t_term_infos	term;
	t_pars			pars;
	t_d_list		*cmd;
	t_d_list		*env;
	t_d_list		*seenv;
	int				endline;
}				t_minishell;

int			g_sig_flag;

void		read_line(t_minishell *mysh);
void		catch_ctl_c(t_minishell *mysh);
void		c_handler(int sig);
void		prompt(void);
t_d_list	*ft_d_lstnew(void *content);
void		ft_d_lstadd_front(t_d_list **alst, t_d_list *new);
void		ft_d_lstiter(t_d_list *lst, void (*f)(void *));
void		f(void *content);
void		init_term(t_minishell *mysh);
void		term_config(t_minishell *mysh);
void		set_term_actions(t_minishell *mysh);
int			reached_eol(t_minishell *mysh);
void		escape_seq(t_minishell *mysh, char ch);
void		reached_eof(t_minishell *mysh);
void		delete_char(t_minishell *mysh);
void		print_on_terminal(t_minishell *mysh, char *ch);
int			ft_put_c(int c);
char		get_c(void);
void		delete_line_char(t_minishell *mysh);
void		clean_term_line(t_minishell *mysh);
void		refresh_term_line(t_minishell *mysh);
void		backup_manager(t_minishell *mysh);

void		parse(t_minishell *minishell, char *line);
int			sep_stuff(char *line, int i);
int			ignore_sep(char *line, int i);
int			quotes(char *line, int index);
int			check_forquotes(t_pars *pars, char **line, t_minishell *mysh);
int			dblquotes(char *line, int i);
int			ft_strcmp(const char *s1, const char *s2);
char		*ft_get_env(char *line, t_d_list *env);
void		free_tokens2(t_minishell *head);
void		fill_tok(t_pars *pars, char *line);
t_token		*split_tok(char *line);
char		*ft_addbcksp(char *var, t_d_list *env);
int			ft_countspe(char *line);
int			ft_varlength(char *line);
t_token		*next_token(char *line, int *i);
void		type_arg(t_token *token, int separator);
int			ft_validvar(char c, int i);
void		ft_skip_space(const char *str, int *i);
int			bslquotes(char *line, int *i);
int			alloc_str(char *line, int *i);
t_d_list	*fill_cmds(t_pars *pars, t_minishell *mysh);
int			ft_underscore(t_minishell *mysh, t_d_list *last);
int			ft_count_args(t_token *start);
int			ft_treat_fd(t_token *start, int file, t_cmd *ret);
t_cmd		*init_cmd(void);
char		*space_line2(char *line, t_minishell *mysh);
char		*space_line(char *line, t_minishell *mysh);
char		*space_alloc(char *line);
char		*ft_substr2(char *s, unsigned int start, size_t len);
char		*ft_cutline(char *line);
int			ft_nextlineexist(char *line);
int			ft_nextline(char *line);
void		free_tokens(t_token *head);
void		sortlst(t_pars *pars);
void		removecmd(t_token *start);
int			checksyntaxe(t_token *start, t_pars *pars, t_minishell *mysh);
int			ft_isflag(char *line);

t_cmd		*ft_cmd(void *content);
t_env		*ft_env(void *content);
char		*ft_strjoin3(char *s1, char *s2);

t_hisb		*create_his(char *line, char *backup);
void		execution(t_minishell *mysh);
void		err_print(char *s1, char *s2, char *s3);
int			ft_str_isdigit(const char *s);

int			ft_doecho(t_cmd *cmd);
int			ft_doenv(t_d_list *env);
int			ft_dounset(t_minishell *mysh, t_cmd *cmd, int rem);
int			ft_export(t_minishell *mysh, t_cmd *cmd);
t_env		*next_env(char *line);
int			ft_fillenv(t_minishell *mysh, char *alias, char *value);
int			ft_fillseenv(t_minishell *mysh, char *alias, char *value);
int			ft_unsetalias(t_minishell *mysh, char *cmd);
void		freesenv(char **env);
int			ft_syntax(char *str);
int			ft_cutmiddle(char *arg);
int			notbuilt_err(char *s1);
int			ft_syntax2(char *str);

void		free_cmd(t_d_list *cmd);
void		free_all(char **s);

t_d_list	*ft_fill_env(char **env);
t_d_list	*ft_fillscretenv(void);
int			ft_shell_lvl(t_minishell *mysh);
int			t_str_isdigit(const char *s);
void		x_free(t_minishell *mysh);
void		free_env(t_d_list *env);

void		signals(void);
void		catch_signal(t_minishell *mysh);
void		s_handler(int sig);
void		free_hisb(void *content);
void		get_attr_term(struct termios *attr);
void		set_attr_term(struct termios *attr);
int			ft_wcount2(char *path, char ch);
char		**ft_split2(char *str, char c);
int			files_manager(t_cmd *cmd, int *in, int *out);
int			ft_size(char **str);
long		ft_atol(const char *str);
int			ft_length(t_minishell mysh);
int			ft_check_builtins(t_minishell *mysh);
int			ft_builin_exec(t_minishell *mysh, int type, t_cmd *cmd);
int			ft_docd(t_minishell *mysh, t_cmd *cmd);
int			ft_dopwd(t_cmd *cmd);
int			ft_doexit(t_minishell *mysh);
void		ft_set_newpwd(t_minishell *mysh, char *oldpath);

char		**get_paths(t_minishell *mysh);
void		ft_set_newpwd(t_minishell *mysh, char *oldpath);
char		**to_env(t_minishell mysh);
void		execute_no_bin(t_exec *exec, t_cmd *cmd, t_minishell *mysh, int p);
void		execute_no_bin_path(t_cmd *cmd, t_minishell *mysh, t_exec *exec);
void		execute_bin(t_exec *exec, t_minishell *mysh, t_cmd *cmd);
void		parent_process(t_cmd *cmd, t_exec *exec);
void		child_process(t_minishell *mysh, t_cmd *cmd, t_exec *exec);
void		init_exec_var(t_exec *exec, t_minishell *mysh);
void		mapping_fds(t_cmd *cmd, t_exec *exec);
void		piping_fd(t_cmd *cmd, t_minishell *mysh, t_exec *exec);
int			set_returns(t_cmd *cmd, t_minishell *mysh, int status);
int			execute_cmd(t_minishell *mysh, t_cmd *cmd, t_exec *exec);
int			built_in_nofork(int bin, t_cmd *cmd, t_minishell *mysh);
void		check_cmd(t_exec *exec, t_minishell *mysh, t_cmd *cmd);
void		waiting_process(int j, t_minishell *mysh,
				int *status, char *cmd_str);
void		get_back_tohead(t_minishell *mysh);
int			check_if_dir(char *msg, t_cmd *cmd,
				t_minishell *mysh, t_exec *exec);
void		err_print(char *s1, char *s2, char *s3);
int			sig_interuption(int *status, t_cmd *cmd, t_minishell *mysh);
void		echo_special_case(t_cmd *cmd, t_minishell *mysh);

#endif