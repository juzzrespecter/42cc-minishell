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
