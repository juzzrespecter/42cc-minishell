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
	char	*str_expanded;
	char	*filename;

	var_check = ft_strchr(str, '$');
	if (var_check == NULL)
		return (str);
	token = ft_strdup(str);
	str_expanded = expand_variables(token, data);
	count = count_words(str_expanded);
	if (count > 1)
	{
		data->redir = 0;
		g_status = print_error(NULL, str, "ambiguous redirect", 1);
		return (NULL);
	}
	filename = copy_word(str_expanded);
	return (filename);
}
