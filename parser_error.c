#include "minishell.h"
#define WORD 1
#define OP_CTRL 2

int			parser_error(char *input, t_data *data)
{
	int		i;
	int		prev_token;
	int		quote_ctrl[2];
	char	op_token[3];


	i = 0;
	quote_ctrl[0] = 0;
	quote_ctrl[1] = 0;
	ft_bzero(op_token, 3);
	while (input[i])
	{
		if (is_word(input[i], quote_ctrl))
		{
			i++;
			prev_token = WORD;
		}
		if (is_blank(input[i], quote_ctrl))
			i++;
		if (is_ctrl_op(input[i], quote_ctrl))
		{
			if (is_syntax_error(input + i, prev_token))
			{
				free(input);
				print_error(data->sh_name, "syntax error near unexpected token", unexp_token);
				return (1);
			}
			i++;
			prev_token = OP_CTRL;
		}
	}
	return (0);
}
