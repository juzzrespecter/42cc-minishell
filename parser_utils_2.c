#include "minishell.h"

int	is_quote(char input, int quote)
{
	if (input == '\"')
		return (quote * (quote != 2) + 2 * (quote == 0));
	if (input == '\'')
		return (quote * (quote != 1) + 1 * (quote == 0));
	return (quote * (quote != 3) + 3 * (quote == 0 && input == '\\'));
}

int	is_var(char *input)
{
	int	i;

	i = 0;
	if (!ft_isalpha(input[i]) && input[i] != '_')
		return (i);
	while ((ft_isalnum(input[i]) || input[i] == '_') && input[i])
		i++;
	return (i);
}

int	is_word(char *input)
{
	int	i;
	int	quote;

	i = 0;
	quote = 0;
	while ((!ft_strchr(";|\n\t\v\r<> ", input[i]) || quote) && input[i])
	{
		if (input[i] == '\\' && input[i + 1] == '"' && quote == 2)
			i += 2;
		quote = is_quote(input[i], quote);
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
