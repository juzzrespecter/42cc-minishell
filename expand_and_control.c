#include "minishell.h"

char	*expand_and_control(char *str, t_data *data)
{
	int		count;
	char	*var_check;
	char	*str_expanded;

	var_check = ft_strchr(str, '$');
	if (var_check == NULL)
		return (str);
	str_expanded = expand_variables(str, data);
	count = stringcount(str_expanded);
	if (count > 1)
	{
		data->redir = 0;
		g_status = print_error(NULL, str, "ambiguous redirect", 1);
		return (NULL);
	}
	return (str_expanded);
}
