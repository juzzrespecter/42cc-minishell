#include "minishell.h"

int	is_quote(char input, int quote)
{
	if (input == '\"')
		return (quote * (quote != 2) + 2 * (quote == 0));
	if (input == '\'')
		return (quote * (quote != 1) + 1 * (quote == 0));
	return (quote * (quote != 3) + 3 * (quote == 3 && input == '\\'));
}

int	is_var(char *input)
{
	int	i;

	i = 0;
	while ((ft_isalnum(input[i]) || input[i] == '_') && input[i])
		i++;
	return (i);
}

int	is_word(char *input)
{
	int	i;
	int	quote_ctrl;

	i = 0;
	quote_ctrl = 0;
	while ((!ft_strrchr(";|\n\t\v\r<> ", input[i]) || quote_ctrl != 0) && input[i])
	{
		quote_ctrl = is_quote(input[i], quote_ctrl);
		i++;
	}
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
	if (input[i] == ';' || input[i] == '|' || input[i] == '\n')
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
