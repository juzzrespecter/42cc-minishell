#include "minishell.h"
# define WORD 1 
# define PIPE 2
# define REDIR 3
# define SEMICOLON 4

static int	parser_err_msg(char *token)
{
	char	*err_msg;
	char	*aux_str;

	if (token == NULL)
		return (print_error(NULL, NULL, strerror(errno), errno + 128));
	err_msg = ft_strjoin("syntax error near unexpected token `", token);
	free(token);
	if (err_msg == NULL)
		return (print_error(NULL, NULL, strerror(errno), errno + 128));
	aux_str = err_msg;
	err_msg = ft_strjoin(err_msg, "\'");
	if (err_msg == NULL)
		return (print_error(NULL, NULL, strerror(errno), errno + 128));
	print_error(NULL, NULL, err_msg, 258);
	free(err_msg);
	return (258);
}

static int	parser_word(char *input, int token_len, t_token *prev_token)
{
	char	*token_str;
	int		next_char;
	int		fd_true;

	if (prev_token->token_str != NULL)
		free(prev_token->token_str);
	token_str = ft_substr(input, 0, token_len);
	if (token_str == NULL)
		return (print_error(NULL, NULL, strerror(errno), errno + 128));
	next_char = 1 * (input[token_len] == '>' || input[token_len] == '<');
	fd_true = is_fd(input);
	if ((next_char && fd_true && (prev_token->info == REDIR)))
		return (parser_err_msg(token_str));
	prev_token->info = WORD;
	return (0);
}

static int	parser_ctrl_info(char input)
{
	if (input == ';')
		return (SEMICOLON);
	if (input == '>' || input == '<')
		return (REDIR);
	return (PIPE);
}

static int	parser_ctrl(char *input, int token_len, t_token *prev_token)
{
	char	*token_str;
	int		token_info;

	if (prev_token->token_str != NULL)
		free(prev_token->token_str);
	token_str = ft_substr(input, 0, token_len);
	if (token_str == NULL)
		return (print_error(NULL, NULL, strerror(errno), errno + 128));
	token_info = parser_ctrl_info(input[0]);
	if (token_info == REDIR && prev_token->info == REDIR) 
		return (parser_err_msg(token_str));
	if ((token_info == SEMICOLON || token_info == PIPE) \
			&& prev_token->info != WORD)
		return (parser_err_msg(token_str));
	prev_token->info = token_info;
	prev_token->token_str = token_str;
	return (0);
}

int			parser_error(char *input)
{
	int		i;
	int		token_len;
	int		parser_out;
	t_token	token;

	i = 0;
	token.info = 0;
	token.token_str = NULL;
	while (input[i])
	{
		token_len = is_word(input + i);
		if (token_len > 0)
		{
			parser_out = parser_word(input + i, token_len, &token);
			if (parser_out != 0)
				return (parser_out);
			i += token_len;
		}
		token_len = is_ctrl_op(input + i);
		if (token_len > 0)
		{
			parser_out = parser_ctrl(input + i, token_len, &token);
			if (parser_out != 0)
				return (parser_out);
			i += token_len;
		}
		i += is_blank(input[i]);
	}
	if (token.info != SEMICOLON && token.info != WORD && token.info != 0)
		return (parser_err_msg(token.token_str));
	if (token.token_str != NULL)
		free(token.token_str);
	return (0);
}
 
