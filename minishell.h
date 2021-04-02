#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <errno.h>
# include <signal.h>
# include <dirent.h>
# include "libft.h"
# include <fcntl.h>

typedef struct s_token
{
	char	*str;
	int		info;
}				t_token;

typedef struct s_pipe
{
	char	*cmd;
	int		cmd_len;
	int		pipe_read;
	int		pipe_write;
	int		next_pipe;
	pid_t	child_pid;
}				t_pipe;

typedef struct s_index
{
	int	i;
	int	j;
	int	quote;
}				t_index;

typedef struct s_data
{
	char	**env;
	char	*pwd;
	int		fd_in;
	int		fd_out;
	int		redir;
}		t_data;

int		g_status;
char	*g_input;
int		envlen(char **env);
void	free_env(char **env);
char	**copy_env(char **env);
void	b_env(char **env);
void	sig_init(void);
void	handle_sig(int sig);
void	b_exit(char **inputs, t_data *data);
int		is_number(char *str);
void	b_pwd(t_data *data);
int		parser_start(char *input, t_data *data);
char	*input_cleaner(char *str);
void	input_copy(char *dst, char *src);
void	copy_inside_quotes(char **src, char **dst, char quote);
void	escape_char(char **dst, char **src);
void	quote_len(char **str, int *i, char quote);
int		parser(char *input, t_data *data, int piped);
int		check_special(char **input, int *i, t_data *data);
int		parser_semicolon(char *input, int semi_pos, t_data *data);
int		parsercore(char *clean_input, t_data *data, int piped);
void	exit_pipe(t_data *data);
void	close_fds(t_data *data);
void	free_inputs(char **inputs);
void	select_cmd(char **inputs, t_data *data);
char	**input_split(char *str);
char	*newsplit(char *src);
void	copy_newsplit(char *src, char *dst, char quote);
int		parser_redir(char **input_address, t_data *data);
void	parser_redir_quotes(char *str, int *i, char quote);
void	remove_redir_input(char **input_address, int i, int j);
char	*get_filename(char *str, int *j, t_data *data);
void	make_filename(char *src, char *dst, int i, int k);
void	handle_redir(char **input, int i, t_data *data);
void	redir_from(char *str, int i, char **input, t_data *data);
void	redir_to_append(char *str, int i, char **input, t_data *data);
void	redir_to(char *str, int i, char **input, t_data *data);
int		get_name_len(char *str);
int		b_unset(char **argv, t_data *data);
int		b_export(char **argv, t_data *data);
void	b_echo(char **argv);
int		b_cd(char **argv, t_data *data);
int		env_parse_id(char *id);
int		env_add_id(char *id, t_data *data);
int		is_fd(char *input);
int		is_ctrl_op(char *input);
int		is_blank(char input);
int		is_word(char *input);
int		is_var(char *input);
int		is_quote(char input, int quote);
char	*search_env(char **env, char *name);
int		parser_error(char *input);
char	*expand_variables(char *input, t_data *data);
int		exec_cmd(char **argv, t_data *data);
int		janitor(char **argv, t_data *data, int err_code);
void	b_pipe(char *input, t_data *data);
int		print_error(char *cmd, char *arg, char *err_msg, int exit_code);
char	*expand_and_control(char *str, t_data *data);
int		stringcount(char *str);
char	*copy_literal(char *str, int quote);
char	*copy_word(char *src);
int		cmd_len(char *input);
int		parser_err_msg(char *token);

#endif
