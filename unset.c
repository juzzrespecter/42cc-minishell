#include "minishell.c"

static char	**unset_rm_id(char *id, char **env)
{
	int		i;
	int		id_len;
	char	**new_env;

	new_env = (char **)ft_calloc((env_len(env) - 1), sizeof(char *));
	if (new_env == NULL)
		return (NULL);
	i = 0;
	id_len = ft_strlen(id);
	while (env[i])
	{
		if (!(ft_strncmp(id, env[i], id_len) == 0 && env[i][id_len] == '='))
			if ((new_env = ft_strdup(env[i])) == NULL)
			{
				free_env(new_env);
				return (NULL);
			}
		i++;
	}
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

int			unset(t_cmd *cmd, t_data *data)
{
	int		i;
	int		err_status;
	char	**new_env;

	i = 0;
	while (cmd->argv[i + 1])
	{
		if (env_parse_id(cmd->argv[i + 1]) == 0)
		{
			if (unset_id_in_env(id, data->env) == 0)
			{
				if ((new_env = unset_rm_id(id, data->env)) == NULL)
					return (errno + 128);
				free_env(data->env);
				data->env = new_env;
			}
		}
		else
		{
			err_status = 1;
			print_error(/* ... */);
		}
		i++;
	}
	return (err_status);
}
