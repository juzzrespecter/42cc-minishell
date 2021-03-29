#include "minishell.h"

void		make_filename(char *src, char *dst, int i, int k)
{
	while (src[i] != ' ' && src[i])
	{
		if (src[i] == '\'')
		{
			while (src[++i] != '\'')
				dst[k++] = src[i];
			i++;
		}
		else if (src[i] == '"')
		{
			while (src[++i] != '"')
			{
				if (src[i] == '\\')
					i++;
				dst[k++] = src[i];
			}
			i++;
		}
		else
			dst[k++] = src[i++];
	}
	dst[k] = '\0';
}

char		*get_filename(char *str, int *j, t_data *data)
{
	int		i;
	int		k;
	char	*filename;

	i = get_name_len(str);
	*j += i;
	i = 0;
	k = 0;
	filename = ft_substr(str, 0, is_word(str));
	filename = expand_and_control(filename, data);
	filename = copy_word(filename);
	return (filename);
}

void		remove_redir_input(char **input_address, int i, int j)
{
	char *tmp;
	char *new_input;

	tmp = ft_substr(input_address[0], 0, i);
	new_input = ft_strjoin(tmp, &(input_address[0][j + 1]));
	free(tmp);
	free(*input_address);
	*input_address = new_input;
}

void		parser_redir_quotes(char *str, int *i, char quote)
{
	int slash_count;

	while (str[*i] != quote)
	{
		slash_count = 0;
		while (str[*i] == '\\' && quote == '"')
		{
			slash_count++;
			(*i)++;
		}
		if (slash_count && !(slash_count % 2))
			(*i)--;
		(*i)++;
	}
}

int			parser_redir(char **input_address, t_data *data)
{
	int		i;
	char	*str;
	char	quote;

	i = -1;
	str = *input_address;
	while (str[++i])
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			quote = str[i];
			i++;
			parser_redir_quotes(str, &i, quote);
		}
		if (str[i] == '>' || str[i] == '<')
		{
			handle_redir(input_address, i, data);
			return (1);
		}
		if (str[(i)] == '\\')
			i++;
	}
	return (0);
}
