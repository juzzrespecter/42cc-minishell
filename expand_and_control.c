#include "minishell.h"
#include <stdio.h>

char	*expand_and_control(char *str, t_data *data)
{
	char	*name_not_expanded;
	char	*name_expanded;
	int		word_count;

	name_not_expanded = ft_substr(str, 0, is_word(str));
	if (name_not_expanded == NULL)
	{
		g_status = print_error(NULL, NULL, strerror(errno), errno + 128);
		return (NULL);
	}
	name_expanded = expand_variables(name_not_expanded, data);
	if (name_expanded == NULL)
	{
		g_status = print_error(NULL, NULL, strerror(errno), errno + 128);
		free(name_not_expanded);
		return (NULL);
	}
	printf("nne: (%s), ne: (%s).\n", name_not_expanded, name_expanded);
	word_count = stringcount(name_expanded);
	if (word_count != 1)
	{
		g_status = print_error(NULL, name_not_expanded, "ambiguous redirect", 1);
		return (NULL);
	}
	free(name_not_expanded);
	return (name_expanded);
}
