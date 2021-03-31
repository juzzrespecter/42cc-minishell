#include "minishell.h"

static char	**b_unset_memalloc_error(char **to_free)
{
	free_env(to_free);
	return (NULL);
}

static char	**b_unset_rm_id(char *id, char **env)
{
	int		i;
	int		j;
	int		id_len;
	char	**new_env;

	new_env = (char **)ft_calloc((envlen(env) - 1), sizeof(char *));
	if (new_env == NULL)
		return (NULL);
	i = 0;
	j = 0;
	id_len = ft_strlen(id);
	while (env[i])
	{
		if (!(ft_strncmp(id, env[i], id_len) == 0 && env[i][id_len] == '='))
		{
			new_env[j] = ft_strdup(env[i]);
			if (new_env[j] == NULL)
				return (b_unset_memalloc_error(new_env));
			j++;
		}
		i++;
	}
	new_env[j] = NULL;
	return (new_env);
}

static int	b_unset_id_in_env(char *id, char **env)
{
	int	i;
	int	id_len;

	i = 0;
	id_len = ft_strlen(id);
	while (env[i])
	{
		if (ft_strncmp(id, env[i], id_len) == 0 && env[i][id_len] == '=')
			return (0);
		i++;
	}
	return (1);
}

int	b_unset(char **argv, t_data *data)
{
	int		i;
	int		err;
	char	**new_env;

	i = 0;
	err = 0;
	while (argv[i + 1])
	{
		if (env_parse_id(argv[i + 1]) == 0)
		{
			if (b_unset_id_in_env(argv[i + 1], data->env) == 0)
			{
				new_env = b_unset_rm_id(argv[i + 1], data->env);
				if (new_env == NULL)
					return (print_error(NULL, NULL, \
								strerror(errno), errno + 128));
				free_env(data->env);
				data->env = new_env;
			}
		}
		else
			err = print_error(argv[0], argv[i], "not a valid identifier", 1);
		i++;
	}
	return (err);
}
