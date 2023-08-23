#include "minishell.h"

void	copy_inside_quotes(char **src, char **dst, char quote)
{
	int	slash_count;

	while (**src != quote)
	{
		slash_count = 0;
		while (**src == '\\' && quote == '"')
		{
			*((*dst)++) = *((*src)++);
			slash_count++;
		}
		if (slash_count && !(slash_count % 2))
			*((*dst)--) = *((*src)--);
		*((*dst)++) = *((*src)++);
	}
}

void	input_copy(char *dst, char *src)
{
	char	quote;

	while (*src)
	{
		if (*src == ' ' && (*(src + 1) == ' ' || *(src + 1) == '\0'))
			src++;
		else if (*src == '\t' && (*(src + 1) == '\t' || *(src + 1) == '\0'))
			src++;
		else if (*src == '"' || *src == '\'')
		{
			*(dst++) = *src;
			quote = *(src++);
			copy_inside_quotes(&src, &dst, quote);
			*(dst++) = *(src++);
		}
		else if (*src == '\\' && *(src + 1))
			escape_char(&dst, &src);
		else
			*(dst++) = *(src++);
	}
	*dst = '\0';
}

static int	input_len(char *str, int *len, int quote)
{
	while (*str)
	{
		if (*str == ' ' && (*(str + 1) == ' ' || *(str + 1) == '\0'))
			str++;
		else if (*str == '\t' && (*(str + 1) == '\t' || *(str + 1) == '\0'))
			str++;
		else if (*str == '\\' && (str + 2))
		{
			*len += 4;
			str += 2;
		}
		else if (*str == '"' || *str == '\'')
		{
			quote = *(str++);
			quote_len(&str, len, quote);
			if (!*str)
				return (-1);
			str++;
			*len += 2;
		}
		else if (str++)
			*len = *len + 1;
	}
	return (*len);
}

char	*input_cleaner(char *str)
{
	int		len;
	char	quote;
	char	*clean_input;
	char	*str_start;

	quote = 0;
	str_start = str;
	while (*str == ' ' && *str)
		str++;
	len = 0;
	len = input_len(str, &len, quote);
	if (len == -1)
	{
		free(str_start);
		return (0);
	}
	clean_input = (char *)malloc((len + 1) * sizeof(char));
	if (!clean_input)
		exit(EXIT_FAILURE);
	input_copy(clean_input, str);
	free(str_start);
	return (clean_input);
}

int	parser_start(char *input, t_data *data)
{
	char	*clean_input;

	if ((parser_error(input)) != 0)
		return (0);
	clean_input = input_cleaner(input);
	data->input = NULL;
	if (clean_input == 0)
	{
		ft_putstr("This minishell does not support multiline\n");
		return (0);
	}
	if (!*clean_input)
	{
		free(clean_input);
		return (0);
	}
	return (parser(clean_input, data, 0));
}
