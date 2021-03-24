#include "minishell.h"
# define WORD 1 
# define CTRL 2
# define REDIR 3

static int	parser_word(char *input, int token_len, int *prev_token, t_data *data)
{
	int	next_char;
	int	fd_true;

	next_char = 1 * (input[token_len] == '>' || input[token_len] == '<');
	fd_true = is_fd(input);
	if ((next_char && fd_true && (prev_token[0] == REDIR)))
	{
		data->err = ft_substr(input, 0, token_len);
		return (0);
	}
	prev_token[0] = WORD;
	return (1);
}

static int	parser_ctrl(char *input, int token_len, int prev_token[2], t_data *data)
{
	int	token;

	token = CTRL;
	if (input[0] == '>' || input[0] == '<')
		token = REDIR;
	if ((token == REDIR && prev_token[0] == REDIR) \
			|| (token == CTRL && prev_token[0] != WORD))
	{
		data->err = ft_substr(input, 0, token_len);
		return (0);
	}
	prev_token[0] = token;
	return (1);
}

int			parser_error(char *input, t_data *data)
{
	int	prev_token[1];
	int	i;
	int	token_len;

	i = 0;
	prev_token[0] = 0;
	while (input[i])
	{
		if ((token_len = is_word(input + i)))
		{
			if (!(parser_word(input + i, token_len, prev_token, data)))
				return (print_error(data->err, NULL, 258));
			i += token_len;
		}
		if ((token_len = is_ctrl_op(input + i)))
		{
			if (!(parser_ctrl(input + i, token_len, prev_token, data)))
				return (print_error(data->err, NULL, 258));
			i += token_len;
		}
		i += is_blank(input[i]);
	}
	return (0);
}
 
