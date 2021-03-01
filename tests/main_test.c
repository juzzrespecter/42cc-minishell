#include "minishell.h"
#include <stdio.h>

int	export(t_cmd *cmd, t_data *data);

int	env_len(char **env) {
	int	len;

	len = 0;
	while (env[len])
		len++;
	return (len++);
}
char	**copy_env(char **env) {
	int	i;
	char	**new_env;

	i = 0;
	new_env = malloc(sizeof(char *) * (env_len(env) + 1));
	while (env[i])
	{
		new_env[i] = ft_strdup(env[i]);
		i++;
	}
	new_env[i] = NULL;
	return (new_env);
}

void	print_env(t_data *data)
{
	int i;

	i = 0;
	while (data->env[i])
	{
		printf("%s\n", data->env[i]);
		i++;
	}
}

void	free_env(char **env)
{
	int i = 0;

	while (env[i])
	{
		free(env[i]);
		i++;
	}
}

int main(int argc, char **argv, char **envp)
{
	t_data *data = malloc(sizeof(t_data) * 1);
	data->env = copy_env(envp);
	t_cmd *cmd = malloc(sizeof(t_cmd) * 1);
	char	*argv_exp[] = {"export","PATH=flema",NULL};

	cmd->argv = argv_exp;
	cmd->fd_in = STDIN_FILENO;
	cmd->fd_out = STDOUT_FILENO;
	cmd->fd_err = STDERR_FILENO;

	int exp_return = export(cmd, data);
	printf("return: (%d)\n\n", exp_return);
	print_env(data);
}
