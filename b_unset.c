#include "minishell.h"

static char	**unset_rm_id(char *id, char **env)
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
			{
				free_env(new_env);
				return (NULL);
			}
			j++;
		}
		i++;
	}
	new_env[j] = NULL;
	return (new_env);
}

static int	unset_id_in_env(char *id, char **env)
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

int			b_unset(char **argv, t_data *data)
{
	int		i;
	int		err_status; 
	char	**new_env;

	i = 0;
	err_status = 0;
	while (argv[i + 1])
	{
		if (env_parse_id(argv[i + 1]) == 0)	
		{
			if (unset_id_in_env(argv[i + 1], data->env) == 0)
			{
				if ((new_env = unset_rm_id(argv[i + 1], data->env)) == NULL)
					return (errno + 128); 
				free_env(data->env);
				data->env = new_env;
			}
		}
		else
			err_status = print_error(argv[0], argv[i], "not a valid identifier", 1);
		i++;
	}
	return (err_status);
}
