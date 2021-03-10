#include "minishell.h"

//	quote status
//		0	no quotes
//		1	single quotes
//		2	double quotes
//		3	escaped

int	is_quote(char input, int quote)
{
	if (input == '\"')
		return (quote * (quote != 2) + 2 * (quote == 0));
	if (input == '\\')
		return (quote * (quote != 3) + 3 * (quote == 0));
	return (quote * (quote != 3) + 3 * (quote == 3 && input == '\\'));
}

int	is_var(char *input)
{
	int	i;

	i = 0;
	while ((ft_isalnum(input[i]) || input[i] == '_') && input[i])
		i++;;
	return (i);
}

int	is_word(char *input, int flags[2])
{
	int	i;

	i = 0;
	while ((!ft_strrchr(";|\n\t\v\r<> ", input[i]) || flags[1] != 0) && input[i])
	{
		flags[1] = is_quote(input[i], flags[1]);
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
