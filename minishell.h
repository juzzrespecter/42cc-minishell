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
	int		fd_in;
	int		fd_out;
	char		*pwd;
	char		input;
	int		status;
}				t_data;

int	parser(t_data *data);
void	sig_init(void);
void	handle_sig(int sig)
char	**copy_env(char **env);
void	free_env(char **env);
int	env_len(char **env);
void	b_env(char **env);
void	b_pwd(t_data *data);
void	b_exit(char **inputs, t_data *data);
int	is_number(char *str);

#endif
