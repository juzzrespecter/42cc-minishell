#include "minishell.h"
#include <stdio.h>

static int		copy_literal_len(char *src, int quote)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (src[i])
	{
		if (src[i] == '"' || (ft_strchr("\\$\'<>", src[i]) && !quote))
			len += 2;
		else
			len++;
		i++;
	}
	len++;
	return (len);
}

char	*copy_literal(char *src, int quote)
{
	char	*value;
	int		i;
	int		j;

	i = 0;
	j = 0;
	value = malloc(sizeof(char) * copy_literal_len(src, quote));
	if (!value)
		return (NULL);
	while (src[i])
	{
		if (src[i] == '"' || (ft_strchr("\\$\'<>", src[i]) && !quote))
		{
			value[j] = '\\';
			j++;
			value[j] = src[i];
		}
		else
			value[j] = src[i];
		i++;
		j++;
	}
	value[j] = '\0';
	return (value);
}

int		copy_word_len(char *src)
{
	int		len;
	int		i;
	int		quote_ctrl;

	quote_ctrl = 0;
	len = 0;
	i = 0;

	while (src[i] && !(is_blank(src[i]) && quote_ctrl == 0))
	{
		if (quote_ctrl != is_quote(src[i], quote_ctrl))
		{
			quote_ctrl = is_quote(src[i], quote_ctrl);
			i++;
		}
		else
		{
			i++;
			len++;
		}
	}
	printf("len: (%d)\n", len);
	return (len);
}

char	*copy_word(char *src)
{
	int		i;
	int		j;
	char	*dst;
	int		quote_ctrl;

	quote_ctrl = 0;
	i = 0;
	j = 0;
	dst = (char *)malloc(sizeof(char) * (copy_word_len(src)));
	if (dst == NULL)
		return (NULL);
	while (src[i] && !(is_blank(src[i]) && quote_ctrl == 0))
	{
		if (quote_ctrl != is_quote(src[i], quote_ctrl))
		{
			quote_ctrl = is_quote(src[i], quote_ctrl);
			i++;
		}
		else
		{
			dst[j] = src[i];
			i++;
			j++;
		}
	}
	dst[j] = 0;
	return (dst);
}
