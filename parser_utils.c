#include "minishell.h"

void			quote_len(char **str, int *i, char quote)
{
	int slash_count;

	while (**str != quote && **str)
	{
		slash_count = 0;
		while (quote == '"' && **str == '\\')
		{
			(*i)++;
			(*str)++;
			slash_count++;
		}
		if (slash_count && !(slash_count % 2))
		{
			(*str)--;
			(*i)--;
		}
		(*i)++;
		(*str)++;
	}
}

void			escape_char(char **dst, char **src)
{
	char	quote;

	(*src)++;
	if (**src == '\'')
		quote = '"';
	else
		quote = '\'';
	*((*dst)++) = quote;
	*((*dst)++) = *((*src)++);
	*((*dst)++) = quote;
}

int		is_fd(char *input)
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

int		stringcount(char *str)
{
	int		i;
	char	quote;
	int		slash_count;

	i = 1;
	str--;
	while (*(++str))
	{
		if (*str == '"' || *str == '\'')
		{
			quote = *(str++);
			while (*str != quote)
			{
				slash_count = 0;
				while (*str == '\\' && quote == '"' && ++slash_count)
					str++;
				if (slash_count && !(slash_count % 2))
					str--;
				str++;
			}
		}
		if (*str == ' ')
			i++;
	}
	return (i);
}
