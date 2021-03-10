#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <errno.h>
# include <signal.h>
# include <dirent.h>
# include "libft/includes/libft.h"

typedef	struct	s_data
{
	char		**env;
	int			fd_in;
	int			fd_out;
	char		*pwd;
	char		*err;
	int			status;
	int			redir;
}				t_data;

char			*g_input;

int		parser(char *input, t_data *data);
int		check_special(char **input, int *i, t_data *data);
int		parser_pipe(char *input, int pipe_pos, t_data *data);
int		parser_semicolon(char *input, int semicolon_pos, t_data *data);
int		parsercore(char *input, t_data *data, int piped);
void	close_fds(t_data *data);
void	free_inputs(char **inputs);
void	select_cmd(char **inputs, t_data *data);


int		parser_redir(char **input, t_data *data);
void	redir_to(char *str, int i, char **input, t_data *data);
char	*get_filename(char *str, int *j);
int		get_name_len(char *str);
void	make_filename(char *src, char *dst, int i, int k);
void	redir_from(char *str, int i, char **input, t_data *data);
void	redir_to_append(char *str, int i, char **input, t_data *data);
void	remove_redir_input(char **input, int i, int j);
void	parser_redir_quotes(char *str, int *i, char quote);

char	**input_split(char *str);
size_t	stringcount(char *str);
char	*newsplit(char *src);
void	copy_newsplit(char *src, char *dst, char quote);
char	*find_next_input(char *str);

void	sig_init(void);
void	handle_sig(int sig);

void	b_env(char **env);
char	**copy_env(char **env);
void	free_env(char **env);
int		env_len(char **env);

void	b_pwd(t_data *data);

void	b_exit(char **inputs, t_data *data);
int		is_number(char *str);

int		b_pipe(char *input1, char *input2, t_data *data);
void	parent(char *input2, t_data *data, int pid, int *fds);

int		b_cd(char **argv, t_data *data);
int		b_echo(char **argv);
int		b_export(char **argv, t_data *data);
int		b_unset(char **argv, t_data *data);
int		env_add_id(char *id, t_data *data);
int		env_parse_id(char *id);
int		exec_cmd(char **argv, t_data *data);
int		janitor(char **argv, t_data *data, int exit_code);
int		parser_error(char *input, t_data *data);
int		parser_variable(char *input, int var_pos, t_data *data);
int		is_quote(char input, int quote);
int		is_var(char *input);
int		is_word(char *input, int flags[2]);
int		is_blank(char input);
int		is_ctrl_op(char *input);

#endif
