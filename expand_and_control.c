#include "minishell.h"

int	count_words(char *str_expanded)
{
	int	i;
	int	count;
	int	word_len;

	i = 0;
	count = 0;
	while (str_expanded[i])
	{
		while (str_expanded[i] && is_blank(str_expanded[i]))
			i++;
		word_len = is_word(str_expanded + i);
		if (word_len > 0)
			count++;
		i += word_len;
		while (str_expanded[i] && is_blank(str_expanded[i]))
			i++;
	}
	return (count);
}

char	*expand_and_control(char *str, t_data *data)
{
	int		count;
	char	*token;
	char	*var_check;
	char	*filename;

	var_check = ft_strchr(str, '$');
	if (var_check != NULL)
	{
		token = ft_strdup(str);
		str = expand_variables(str, data);
		count = count_words(str);
		if (count > 1)
		{
			data->redir = 0;
			g_status = print_error(NULL, token, "ambiguous redirect", 1);
			free(token);
			return (NULL);
		}
		free(token);
	}
	filename = copy_word(str);
	free(str);
	return (filename);
}
