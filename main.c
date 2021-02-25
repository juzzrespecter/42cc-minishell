#include "minishell.h"

void	free_data(t_data *data)
{
	free_env(data->env);
	free(data->input);
	free(data->pwd);
	ft_putstr_fd("exit\n", 2);
	exit(EXIT_SUCCESS);
}

void	data_init(t_data *data, char **envp)
{
	data->env = copy_env(envp);
	data->pwd = getcwd(NULL, 0);
	data->fd_in = 0;
	data->fd_out = 1;
	data->input = NULL;
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	int	ret;

	data_init(&data, envp);
	if (!data.env)
		exit(EXIT_FAILURE);
	while (1)
	{
		free(data->input);
		sig_init();
		ft_putstr_fd("minishell> ", 2);
		ret = get_next_line(0, &data->input);
		if (!ret)
			free_data(&data);
		else
			parser(&data);
	}
	return (0);
}
