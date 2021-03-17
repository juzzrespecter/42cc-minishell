#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <errno.h>
# include <signal.h>
# include <dirent.h>
# include "libft/libft.h"

typedef	struct	s_data
{
	char		**env;
	int			fd_in;
	int			fd_out;
	char		*pwd;
	int			redir;
}				t_data;

int				g_status;
char			*g_input;

int				envlen(char **env);
void			free_env(char **env);
char			**copy_env(char **env);
void			b_env(char **env);

void			sig_init(void);
void			handle_sig(int sig);

void			b_exit(char **inputs, t_data *data);
int			is_number(char *str);

void			b_pwd(t_data *data);

int				b_pipe(char *input1, char *input2, t_data *data);
void			parent(char *input2, t_data *data, int pid, int *fds);

int				parser_start(char *input, t_data *data);
char			*input_cleaner(char *str);
void			input_copy(char *dst, char *src);
void			copy_inside_quotes(char **src, char **dst, char quote);
void			escape_char(char **dst, char **src);
void			quote_len(char **str, int *i, char quote);

int				parser(char *input, t_data *data, int piped);
int			check_special(char **input, int *i, t_data *data);
int			parser_semicolon(char *input, int semi_pos, t_data *data);
int			parser_pipe(char *input, int pipe_pos, t_data *data);

int				parsercore(char *clean_input, t_data *data, int piped);
void			exit_pipe(t_data *data);
void			close_fds(t_data *data);
void			free_inputs(char **inputs);
void			select_cmd(char **inputs, t_data *data);

char			**input_split(char *str);
char			*newsplit(char *src);
void			copy_newsplit(char *src, char *dst, char quote);

int				parser_redir(char **input_address, t_data *data);
void			parser_redir_quotes(char *str, int *i, char quote);
void			remove_redir_input(char **input_address, int i, int j);
char			*get_filename(char *str, int *j);
void			make_filename(char *src, char *dst, int i, int k);

void			handle_redir(char **input, int i, t_data *data);
void			redir_from(char *str, int i, char **input, t_data *data);
void			redir_to_append(char *str, int i, char **input, t_data *data);
void			redir_to(char *str, int i, char **input, t_data *data);
int				get_name_len(char *str);

#endif
