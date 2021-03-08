#include "test.h"

/* quote_ctrl[0] == single quotes, quote_ctrl[1] == double */

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

int	is_var(char *input)
{
	int	i;

	i = 0;
	while ((ft_isalnum(input[i]) || input[i] == '_') && input[i])
		i++;;
	return (i);
}

int	is_word(char *input)
{
	int	i;

	i = 0;
	while (!ft_strrchr(";|\n\t\v\r<> ", input[i]) && input[i])
		i++;;
	return (i);
}

int	is_blank(char input)
{
	if (!ft_strrchr(" \t\v\f\r", input))
		return (0);
	return (1);
}

int	is_ctrl_op(char *input)
{
	int	i;
	int	op_len;

	i = 0;
	op_len = 0;
	if (input[i] == ';' || input[i] == '|' || input[i]  == '\n')
		op_len++;
	if (input[i] == '>')
	{
		op_len++;
		if (input[i + op_len] == '>')
			op_len++;
	}
	if (input[i] == '<')
		op_len++;
	return (op_len);
}
