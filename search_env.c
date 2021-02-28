#include "minishell.h"

char	*search_env(char **env, char *name)
{
	char	*value;
	int	name_len;
	int	i;

	name_len = ft_strlen(name) + 1;
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(name, env[i], name_len))
			return (env[i]);
		i++;
	}
	return (NULL);
}
