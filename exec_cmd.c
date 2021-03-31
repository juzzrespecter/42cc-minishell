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
			break ;
		}
		i++;
	}
	aux_path = path;
	path = ft_strjoin(path, cmd);
	free(aux_path);
	return (path);
}

static char	**exec_get_paths(char *path_env, char *cmd)
{
	int		i;
	char	**paths;

	i = 0;
	paths = ft_split(path_env + 5, ':');
	if (paths == NULL)
		return (NULL);
	while (paths[i])
	{
		paths[i] = exec_mnt_path(paths[i], cmd);
		if (!paths[i])
		{
			free_inputs(paths);
			return (NULL);
		}
		i++;
	}
	return (paths);
}

static char	*exec_no_slash(char *path_env, char **argv, t_data *data)
{
	char		**paths;
	struct stat	buff;
	int			i;

	i = 0;
	paths = exec_get_paths(path_env, argv[0]);
	if (!paths)
		exit(janitor(argv, data, errno));
	while (paths[i])
	{
		if (!stat(paths[i], &buff))
			break ;
		i++;
	}
	if (!paths[i])
		exit(janitor(argv, data, 127));
	return (paths[i]);
}

int	exec_cmd(char **argv, t_data *data)
{
	char	*path_env;
	char	*cmd;

	if (!argv[0])
		exit(janitor(argv, data, 0));
	path_env = search_env(data->env, "PATH");
	cmd = argv[0];
	if (!slash_in_cmd(argv[0]) && path_env)
		cmd = exec_no_slash(path_env, argv, data);
	execve(cmd, argv, data->env);
	exit(janitor(argv, data, errno));
}
