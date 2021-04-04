#include "minishell.h"
#define WORD 1 
#define PIPE 2
#define REDIR 3
#define SEMICOLON 4

static int	parser_err_ctrl(char *input, t_token *prv_token, char *str)
{
	int	token_info;

	if (input[0] == ';')
		token_info = SEMICOLON;
	if (input[0] == '>' || input[0] == '<')
		token_info = REDIR;
	if (input[0] == '|')
		token_info = PIPE;
	if (token_info == REDIR && prv_token->info == REDIR)
		return (parser_err_msg(str));
	if ((token_info == SEMICOLON || token_info == PIPE) && \
			prv_token->info != WORD)
		return (parser_err_msg(str));
	prv_token->info = token_info;
	return (0);
}

static int	parser_err_word(char *input, t_token *prv_token, char *str, int len)
{
	int	next_char;
	int	fd_true;

	next_char = 1 * (input[len] == '>' || input[len] == '<');
	fd_true = is_fd(input);
	if ((next_char && fd_true && (prv_token->info == REDIR)))
		return (parser_err_msg(str));
	prv_token->info = WORD;
	return (0);
}

static int	parser_err_token(char *input, int len, t_token *prv_token, int id)
{
	char	*str;
	int		parser_out;

	if (prv_token->str != NULL)
		free(prv_token->str);
	str = ft_substr(input, 0, len);
	if (str == NULL)
		return (print_error(NULL, NULL, strerror(errno), errno + 128));
	if (id == 1)
		parser_out = parser_err_ctrl(input, prv_token, str);
	else
		parser_out = parser_err_word(input, prv_token, str, len);
	prv_token->str = str;
	return (parser_out);
}

static int	parser_err_exit(t_token *token)
{
	int	ret_value;

	ret_value = 0;
	if (token->info != SEMICOLON && token->info != WORD && token->info != 0)
		ret_value = parser_err_msg(token->str);
	else
		if (token->str != NULL)
			free(token->str);
	return (ret_value);
}

int	parser_error(char *input)
{
	int		i;
	int		token_len;
	int		parser_out;
	t_token	token;

	i = 0;
	ft_memset(&token, 0, sizeof(t_token));
	parser_out = 0;
	while (input[i])
	{
		token_len = is_word(input + i);
		if (token_len > 0)
			parser_out = parser_err_token(input + i, token_len, &token, 0);
		else
		{
			token_len = is_ctrl_op(input + i);
			if (token_len > 0)
				parser_out = parser_err_token(input + i, token_len, &token, 1);
		}
		if (parser_out != 0)
			return (parser_out);
		i += token_len;
		i += is_blank(input[i]);
	}
	return (parser_err_exit(&token));
}
