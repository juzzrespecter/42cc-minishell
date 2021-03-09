#ifndef TEST_H
# define TEST_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "libft.h"

typedef struct	s_data
{
	char **env;
	char *err;
}				t_data;

int	is_ctrl_op(char *input);
int	is_blank(char input);
int	is_quote(char input, int quotes);
int	parser_error(char *input, t_data *data);
int	is_word(char *input, int flags[3]);

#endif
