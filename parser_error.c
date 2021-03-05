#include "minishell.h"
#define WORD 1
#define OP_CTRL 2

static int	is_syntax_error(char *input, int prev_token, char op_token[3])
{
	int	i;

	i = 0;
	while (input[i] && i < 2 && is_ctrl_op(input[i]))
	{
		op_token[i] = input[i];
		i++;
	}
	if (prev_token == OP_CTRL || i == 2)
		return (1);
	ft_bzero(op_token, 3);
	return (0);
}

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
		is_quote(input[i], quote_ctrl)
		if (is_word(input[i]) || (quote_ctrl[0] || quote_crtl[1]))
			prev_token = WORD;
		if (is_ctrl_op(input[i] && !(quote_ctrl[0] || quote_ctrl[1])))
		{
			if (is_syntax_error(input + i, prev_token, op_token))
			{
				print_error(data->sh_name, "syntax error near unexpected token", op_token);
				return (1);
			}
			prev_token = OP_CTRL;
		}
		i++;
	}
	return (0);
}
