#include "minishell.h"

int	cmd_len(char *input)
{
	int	len;
	int	quote_ctrl;

	len = 0;
	quote_ctrl = 0;
	while ((quote_ctrl != 0 || !(input[len] == '\n' || \
					input[len] == ';' || input[len] == '|')) && input[len])
	{
		quote_ctrl = is_quote(input[len], quote_ctrl);
		len++;
	}
	return (len);
}

static int	copy_literal_len(char *src, int quote)
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

static int	copy_word_len(char *src)
{
	int		len;
	int		i;
	int		quote_ctrl;

	quote_ctrl = 0;
	len = 0;
	i = 0;
	while (is_blank(src[i]))
		i++;
	while (src[i] && !(is_blank(src[i]) && quote_ctrl == 0))
	{
		if (quote_ctrl != is_quote(src[i], quote_ctrl))
		{
			quote_ctrl = is_quote(src[i], quote_ctrl);
			i++;
		}
		else
		{
			if (quote_ctrl == 3)
				quote_ctrl = 0;
			i++;
			len++;
		}
	}
	return (len);
}

// no funca

char	*copy_word(char *src)
{
	char	*dst;
	t_index	ind;

	dst = (char *)malloc(sizeof(char) * (copy_word_len(src)));
	if (dst == NULL)
		return (NULL);
	ft_bzero(&ind, sizeof(t_index));
	while (is_blank(src[ind.i]))
		ind.i++;
	while (src[ind.i] && !(is_blank(src[ind.i]) && ind.quote == 0))
	{
		if (ind.quote != is_quote(src[ind.i], ind.quote) && ind.quote != 3)
			ind.quote = is_quote(src[ind.i], ind.quote);
		else
		{
			ind.quote = ind.quote * (!(ind.quote == 3));
			dst[ind.j] = src[ind.i];
			ind.j++;
		}
		ind.i++;
	}
	dst[ind.j] = 0;
	return (dst);
}
