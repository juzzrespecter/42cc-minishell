#include "minishell.c"

int	cd(t_cmd *cmd, t_data *data)
{
	char	*path;
	char	*home;
	char	*pwd;
	char	*id;
	int	export_pwd_ret;

	path = cmd->argv[1];
	if (path == NULL)
	{
		if ((home = search_env(env, "HOME=")) == NULL)
		       return (print_error(cmd->argv[1], "HOME not set"));
		path = home + 5;	
	}
	if (chdir(path) == -1 || (pwd = getcwd(pwd, NULL)) == NULL)
		return (print_error(cmd->argv[0], strerror(errno)));
	if ((id = ft_strjoin("PWD=", pwd)) == NULL)
		return (print_error(cmd->argv[0], strerror(errno)));
	free(pwd);
	export_pwd_ret = env_add_id(id, data);
	free(id);
	return (export_pwd_ret);
}
