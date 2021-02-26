#include "minishell.h"

char	*search_env(char **env, char *key)
{
	char	*value;
	int	key_len;
	int	i;

	key_len = ft_strlen(key);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(key, env[i], key_len))
			return (env[i]);
		i++;
	}
	return (NULL);
}
