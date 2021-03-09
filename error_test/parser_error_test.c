#include "test.h"
# define PREV_TOKEN 0
# define WORD 1 
# define CTRL 2
# define REDIR 3

// condiciones de error para words:
// 		word es a la vez used_as_fd && used_as_filepath
// 			used_as_fd 			== is_digit && next_char == redir
//			used_as_filepath 	== is_word && prev_token == redir

//	flags
//		flags[0] == prev_token:		{ 0: word, 1: ctrl, 2: redir }
//		flags[1] == is_quoted:		{ 0: no, 1: single_quotes, 2: double_quotes, 3: escaped }

static int	is_fd(char *input)
{
	int	i;

	i = 0;
	while (input[i] && !ft_strrchr(";|\t <>", input[i]))
	{
		if (!ft_isdigit(input[i]))
			return (0);
		i++;
	}
	return (i);
}

static int	word_syntax_err(char metachr, char *input, int prev_token)
{
	int	next_char;
	int	fd_true;

	next_char = 1 * (metachr == '>' || metachr == '<');
	fd_true = is_fd(input);
	printf(" %c, %d, %d\n", metachr, fd_true, prev_token);
	printf(" %d %d %d\n", (next_char), (fd_true), (prev_token == REDIR));
	return ((next_char && fd_true && (prev_token == REDIR)));
}

static int	ctrl_syntax_err(char token, int prev_token)
{
	if ((token == '>' || token == '<') && prev_token == REDIR)
		return (1);
	if (prev_token == WORD)
		return (1);
	return (0);
}

int			parser_error(char *input, t_data *data)
{
	int	flags[2];
	int	i = 0;
	int	token_len;

	ft_bzero(flags, sizeof(int) * 2);
	while (input[i])
	{
		if ((token_len = is_word(input + i, flags)))
		{
			if (word_syntax_err(input[i + token_len], input + i, flags[PREV_TOKEN]))
			{
				data->err = ft_substr(input, i, token_len);
				return (258);
			}
			flags[PREV_TOKEN] = WORD;
			i += token_len;
		}
		if ((token_len = is_ctrl_op(input + i)))
		{
			if (ctrl_syntax_err(input[i], flags[PREV_TOKEN]))
			{
				data->err = ft_substr(input, i, token_len);
				return (258);
			}
			flags[PREV_TOKEN] = CTRL;
			if (input[i] == '>' || input[i] == '<')
				flags[PREV_TOKEN] = REDIR;
			i += token_len;
		}
		i += is_blank(input[i]);
	}
	return (0);
}
 
