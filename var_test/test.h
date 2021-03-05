#ifndef TEST_H
# define TEST_H
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <errno.h>
# include "libft.h"

typedef struct	s_data 
{
	char		**env;
	char		*input;
}				t_data;

int		is_var(char input);
int		is_blank(char input);
int		is_word(char input);
int		is_ctrl_op(char input);
int		parser_variable(char *input, int var_pos, t_data *data);
char	*search_env(char **env, char *name);

#endif
