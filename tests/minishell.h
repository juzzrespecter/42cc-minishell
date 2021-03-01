#ifndef MINISHELL_H
# define MINISHELL_H

typedef struct  s_cmd {
                char    **argv;
                int     fd_in;
                int     fd_out;
                int     fd_err;
}               t_cmd;

typedef struct  s_data {
        char    **env;
}               t_data;

typedef struct s_minishell {
	char **argv;

}	t_minishell;

int	env_len(char **env);
void	free_env(char **env);

# include "libft.h"
# include <sys/stat.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <dirent.h>
# include <signal.h>
# include <errno.h>

# endif
