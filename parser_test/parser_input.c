#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
# define WORD 1
# define CTRL_OP 2

int	is_blank(char input, int quote_ctrl[2])
{
	if (quote_ctrl[0] || quote_ctrl[1])
		return (0);
	if (strrchr(" \n\t\v\f\r", input) == NULL)
		return (0);
	return (1);
}

int	is_quote(char input, int quote_ctrl[2])
{
	if (input == '\'')
	{
		if (quote_ctrl[1] == 1)
			return (0);
		if (quote_ctrl[0] == 1)
			quote_ctrl[0] = 0;
		else
			quote_ctrl[0] = 1;
		return (1);
	}
	if (input == '\"')
	{
		if (quote_ctrl[0] == 1)
			return (0);
		if (quote_ctrl[1] == 1)
			quote_ctrl[1] = 0;
		else
			quote_ctrl[1] = 1;
		return (1);
	}
	return (0);
}

int	is_word(char input, int quote_ctrl[2])
{
	if (quote_ctrl[0] || quote_ctrl[1])
		return (1);
	if (strrchr(" ;|\n", input) == NULL)
		return (1);
	return (0);
}

int	is_ctrl_op(char input, int quote_ctrl[2])
{
	if (quote_ctrl[0] || quote_ctrl[1])
		return (0);
	if (strrchr(";|", input) == NULL)
		return (0);
	return (1);
}

int	move_through_word(char *input, int quote_ctrl[2])
{
	int	i;

	i = 0;
	while (is_word(input[i], quote_ctrl))
	{
		if (input[i] == '\'')
			is_quote(input[i], quote_ctrl);
		if (input[i] == '\"')
			is_quote(input[i], quote_ctrl);
		i++;
	}
	return (i);
}

int	move_through_ctrl_op(char *input, int quote_ctrl[2])
{
	int	i;

	i = 0;
	while (is_ctrl_op(input[i], quote_ctrl))
		i++;
	return (i);
}

char	*get_token(char *input, int quote_ctrl[2], char *type)
{
	char	*token;
	int		token_len;
	int		i;

	i = 0;
	if (strncmp(type, "WORD", 4) == 0)
		token_len = move_through_word(input, quote_ctrl);
	if (strncmp(type, "CTRL_OP", 7) == 0)
		token_len = move_through_ctrl_op(input, quote_ctrl);
	token = (char *)calloc((token_len + 1), sizeof(char));
	strncpy(token, input, token_len);
	return (token);
}

int	parser(char *input)
{
	int	i;
	int	token_count;
	int	quote_ctrl[2];	/* quote_ctrl[0] == single quote, quote_crtl[1] == double quote */
	int	prev_token;
	char *token;

	i = 0;
	prev_token = 0;
	token_count = 0;
	quote_ctrl[0] = 0;
	quote_ctrl[1] = 0;
	while (input[i])
	{
		if (is_word(input[i], quote_ctrl))
		{
			token =  get_token(input + i, quote_ctrl, "WORD");
			printf("WORD: %s\n", token);
			free(token);
			i += move_through_word(input + i, quote_ctrl);
			prev_token = WORD;
		}
		if (is_ctrl_op(input[i], quote_ctrl))
		{
			if (strlen(get_token(input + i, quote_ctrl, "CTRL_OP")) > 1 || prev_token == CTRL_OP)
			{
				printf("nan: syntax error near unexpected token '%s'\n", get_token(input + i, quote_ctrl, "CTRL_OP"));
				return (1);
			}
			token = get_token(input + i, quote_ctrl, "CTRL_OP");
			printf("CTRL: %s\n", token);
			free(token);
			i += move_through_ctrl_op(input + i, quote_ctrl);
			prev_token = CTRL_OP;
		}
		if (is_blank(input[i], quote_ctrl))
			i++;
	}
	return (0);
}

int main()
{
	char buff[1000];

	while (1)
	{
		memset(buff, 0, 1000);
		read(0, buff, 1000);
		parser(buff);
	}
	return (0);
}
