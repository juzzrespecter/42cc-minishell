#include "minishell.h"

static int	slash_in_cmd(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '/')
			return (1);
		i++;
	}
	return (0);
}

static char	*exec_mnt_path(char *path, char *cmd)
{
	int		i;
	char	*aux_path;

	i = 0;
	while (path[i])
	{
		if (!path[i + 1] && !(path[i] == '/'))
		{
			aux_path = path;
			path = ft_strjoin(path, "/");
			free(aux_path);
			if (!path)
				return (NULL);
			break;
		}
		i++;
	}
	aux_path = path;
	path = ft_strjoin(path, cmd);
	free(aux_path);
	return (path);
}

static char	**clean_paths(char **paths)
{
	int	i;

	i = 0;
	while (paths[i])
	{
		free(paths[i]);
		i++;
	}
	return (NULL);
}

static char	**exec_get_paths(char *path_env, char *cmd)
{
	int	i;
	char	**paths;

	i = 0;
	if ((paths = ft_split(path_env + 5, ':')) == NULL)
		return (NULL);
	while (paths[i])
	{
		if (!(paths[i] = exec_mnt_path(paths[i], cmd)))
			return (clean_paths(paths));
		i++;
	}
	return (paths);
}

int			exec_cmd(char **argv, t_data *data)
{
	struct	stat buff;
	char	**paths;
	char	*path_env;
	char	*cmd;
	int		i;

	i = 0;
	if (!argv[0])
		exit(janitor(argv, data, 0));
	path_env = search_env(data->env, "PATH");
	cmd = argv[0];
	if (!slash_in_cmd(argv[0]) && path_env)
	{
		if (!(paths = exec_get_paths(path_env, argv[0])))
			exit(janitor(argv, data, errno));
		while (paths[i])
		{
			if (!stat(paths[i], &buff))
				break;
			i++;
		}
		if (!paths[i])
			exit(janitor(argv, data, 127));
		cmd = paths[i];
	}
	execve(cmd, argv, data->env);
	exit(janitor(argv, data, errno));
}
