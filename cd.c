#include "minishell.c"

int	cd(char **argv, char **env)
{
	char	*path;
	char	*home;
	int	dir_out;

	home = search_env(env, "HOME");
	path = argv[1];
	if (path == NULL)
	{
		if (home == NULL)
		{
			print_error(argv[0], "HOME not found\n");
			return (1);
		}
		path = home + ft_strlen("HOME=");
	}
	if ((dir_out = chdir(path)) == -1)
		print_error(argv[0], strerror(errno));
	return ((dir_out == -1) ? 1 : 0);

}
