#include "minishell.h"

void	free_env(char **env)
{
	int	i;
	int	env_len;

	i = 0;
	env_len = envlen(env);
	while (i < env_len)
	{
		free(env[i]);
		i++;
	}
	free(env);
}

int	envlen(char **env)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	return (++i);
}

char	**copy_env(char **env)
{
	char	**data_env;
	int		i;

	i = 0;
	data_env = malloc(sizeof(char *) * envlen(env));
	if (!data_env)
		exit(EXIT_FAILURE);
	while (env[i])
	{
		data_env[i] = ft_strdup(env[i]);
		i++;
	}
	data_env[i] = 0;
	return (data_env);
}

void	b_env(t_data *data)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	while (data->env[i])
	{
		str = ft_strnstr(data->env[i], "=", ft_strlen(data->env[i]));
		if (str)
		{
			j = 0;
			while (data->env[i][j])
			{
				write(1, &data->env[i][j], 1);
				j++;
			}
			ft_putchar('\n');
		}
		i++;
	}
	data->status = 0;
}
