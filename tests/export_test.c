#include "minishell.h"

static int		export_print(t_data *data, int fd_out)
{
	int		i;
	int 	j;
	char	*value;

	i = 0;
	while (data->env[i])
	{
		value = data->env[i];
		j = 0;
		while (value[j] != '=' && value[j] != 0)
			j++;
		write(fd_out, "declare -x ", 11);
		write(fd_out, value, j);
		write(fd_out, "\"", 1);
		write(fd_out, value + j, ft_strlen(value + j));
		write(fd_out, "\"\n", 2);
		i++;
	}
	return (0);
}

static void		export_print_error(char *id, int fd_err)
{
	write(fd_err, "bash: export: '", 15);
	write(fd_err, id, ft_strlen(id));
	write(fd_err, "': not a valid identifier\n", 26);
}

static char		**export_new_env(char **env, char *id)
{
	char	*new_id;
	char	**new_env;
	int		old_env_len;
	int		i;

	i = 0;
	old_env_len = env_len(env);
	new_env = (char **)calloc(old_env_len + 1, sizeof(char *));
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
	new_env[i + 1] = NULL;
	return (new_env);
}

static int		export_add_id(char *id, t_data *data)
{
	int		i;
	char	**new_env;

	i = 0;
	while (data->env[i])
	{
		if (ft_strncmp(data->env[i], id, (ft_strrchr(id, '=') - id + 1)) == 0)
		{
			data->env[i] = ft_strdup(id);
			return (data->env[i] ? 0 : 128 + errno);
		}
		i++;
	}
	if ((new_env = export_new_env(data->env, id)) == NULL)
		return (errno + 128);
	free_env(data->env);
	data->env = new_env;
	return (0);
}

static int		export_parse_id(char *id, t_data *data)
{
	int		i;
	int		found_err;

	i = 0;
	found_err = 0;
	while (id[i] != '=' && id[i] != 0)
	{
		if (!(id[i] == '_' || ft_isalnum(id[i])))
			return (1);
		i++;
	}
	if (!i)
		return (1);	
	if (ft_strrchr(id, '=') == NULL)
			return (0);
	return (export_add_id(id, data));
}	

int				export(t_cmd *cmd, t_data *data)
{
	int		i;
	int		err_status;
	int		export_out;

	err_status = 0;
	i = 0;
	if (cmd->argv[1] == NULL)
		return (export_print(data, cmd->fd_out));
	while (cmd->argv[i] != NULL)
	{
		if ((export_out = export_parse_id(cmd->argv[i], data)) != 0)
		{
			err_status = 1;
			export_print_error(cmd->argv[i], cmd->fd_err);
		}
		if (export_out > 1)
			return (errno + 128);
		i++;
	}
	return (err_status);
}
