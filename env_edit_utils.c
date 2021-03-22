#include "minishell.h"

static char		**export_new_env(char **env, char *id)
{
	char	*new_id;
	char	**new_env;
	int		old_envlen;
	int		i;

	i = 0;
	old_envlen = envlen(env);
	new_env = (char **)ft_calloc(old_envlen + 1, sizeof(char *));
	new_id = ft_strdup(id);
	if (new_env == NULL || new_id == NULL)
		return (NULL);
	while (env[i])
	{
		if ((new_env[i] = ft_strdup(env[i])) == NULL)
		{
			free_env(new_env);
			return (NULL);
		}
		i++;
	}
	new_env[i] = new_id;
	return (new_env);
}

int				env_add_id(char *id, t_data *data)
{
	int	i;
	char	**new_env;

	i = 0;
	if (ft_strrchr(id, '=') == NULL)
			return (0);
	while (data->env[i])
	{
		if (ft_strncmp(data->env[i], id, (ft_strrchr(id, '=') - id + 1)) == 0)	
		{
			data->env[i] = ft_strdup(id);
			return (data->env[i] ? 0 : -1);
		}
		i++;
	}
	if ((new_env = export_new_env(data->env, id)) == NULL)
		return (-1);
	free_env(data->env);
	data->env = new_env;
	return (0);
}

int				env_parse_id(char *id)
{
	int	i;

	i = 0;
	while (id[i] != '=' && id[i] != 0)
	{
		if (!(id[i] == '_' || ft_isalnum(id[i])))
			return (1);
		i++;
	}
	if (!i)
		return (1);
	return (0);
}
