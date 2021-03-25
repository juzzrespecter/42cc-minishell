#include "minishell.h"

int	b_cd(char **argv, t_data *data)
{
	char	*path;
	char	*home;
	char	*pwd;
	char	*id;
	int		export_pwd_ret;

	path = argv[1];
	if (path == NULL)
	{
		if ((home = search_env(data->env, "HOME=")) == NULL)
		       return (print_error(argv[0], NULL, "HOME not set", 1));
		path = home + 5; 
	}
	if (chdir(path) == -1)
		return (print_error(argv[0], path, strerror(errno), errno + 128));
	if ((pwd = getcwd(NULL, 0)) == NULL)
		return (print_error(argv[0], NULL, strerror(errno), errno + 128));
	if ((id = ft_strjoin("PWD=", pwd)) == NULL)
		return (print_error(argv[0], NULL, strerror(errno), errno + 128));
	export_pwd_ret = env_add_id(id, data);
	free(data->pwd);
	data->pwd = ft_strdup(pwd);
	free(pwd);
	free(id);
	return (export_pwd_ret);
}
