#include "minishell.h"

static char	*b_cd_pathfinder(char *first_arg, char **env)
{
	char	*path;

	path = first_arg;
	if (path == NULL)
	{
		path = search_env(env, "HOME");
		if (path == NULL)
		{
			print_error("cd", NULL, "HOME not set", 1);
			return (NULL);
		}
		path = path + 5;
	}
	return (path);
}

int	b_cd(char **argv, t_data *data)
{
	char	*path;
	char	*pwd;
	char	*id;
	int		export_pwd_ret;

	path = b_cd_pathfinder(argv[1], data->env);
	if (path == NULL)
		return (g_status);
	if (chdir(path) == -1)
		return (print_error(argv[0], path, strerror(errno), 1));
	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
		return (print_error(argv[0], NULL, strerror(errno), errno + 128));
	id = ft_strjoin("PWD=", pwd);
	if (id == NULL)
		return (print_error(argv[0], NULL, strerror(errno), errno + 128));
	export_pwd_ret = env_add_id(id, data);
	free(data->pwd);
	data->pwd = ft_strdup(pwd);
	free(id);
	free(pwd);
	if (data->pwd == NULL || export_pwd_ret == -1)
		return (print_error(argv[0], NULL, strerror(errno), errno + 128));
	g_status = 0;
	return (0);
}
