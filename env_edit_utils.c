#include "minishell.h"

static char	**export_new_env(char **env, char *id)
{
	char	**new_env;
	int		old_envlen;
	int		i;

	i = 0;
	old_envlen = envlen(env);
	new_env = (char **)ft_calloc(old_envlen + 1, sizeof(char *));
	if (new_env == NULL)
		return (NULL);
	while (env[i])
	{
		new_env[i] = ft_strdup(env[i]);
		if (new_env[i] == NULL)
		{
			free_env(new_env);
			return (NULL);
		}
		i++;
	}
	new_env[i] = ft_strdup(id);
	if (new_env[i] == NULL)
		return (NULL);
	return (new_env);
}

int	env_add_id(char *id, t_data *data)
{
	int		i;
	char	**new_env;

	i = 0;
	if (ft_strrchr(id, '=') == NULL)
		return (0);
	while (data->env[i])
	{
		if (ft_strncmp(data->env[i], id, (ft_strrchr(id, '=') - id + 1)) == 0)
		{
			free(data->env[i]);
			data->env[i] = ft_strdup(id);
			if (!data->env[i])
				return (-1);
			return (0);
		}
		i++;
	}
	new_env = export_new_env(data->env, id);
	if (new_env == NULL)
		return (-1);
	free_env(data->env);
	data->env = new_env;
	return (0);
}

char	*search_env(char **env, char *name)
{
	int	name_len;
	int	i;

	name_len = ft_strlen(name);
	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(name, env[i], name_len) && env[i][name_len] == '=')
			return (env[i]);
		i++;
	}
	return (NULL);
}

int	check_var(char *var, int export_true)
{
	int	len;

	len = is_var(var);
	if (len == 0)
		return (0);
	if (var[len] == 0 || (var[len] == '=' && export_true == 1))
		return (1);
	return (0);
}
