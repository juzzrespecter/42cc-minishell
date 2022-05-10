#include "minishell.h"

static int	select_from_builtins(char **inputs, t_data *data)
{
	if (!ft_strncmp(inputs[0], "echo", ft_strlen("echo") + 1))
		b_echo(data, inputs);
	else if (!ft_strncmp(inputs[0], "pwd", ft_strlen("pwd") + 1))
		b_pwd(data);
	else if (!ft_strncmp(inputs[0], "cd", ft_strlen("cd") + 1))
		b_cd(inputs, data);
	else if (!ft_strncmp(inputs[0], "env", ft_strlen("env") + 1))
		b_env(data);
	else if (!ft_strncmp(inputs[0], "exit", ft_strlen("exit") + 1))
		b_exit(inputs, data);
	else if (!ft_strncmp(inputs[0], "export", ft_strlen("export") + 1))
		b_export(inputs, data);
	else if (!ft_strncmp(inputs[0], "unset", ft_strlen("unset") + 1))
		b_unset(inputs, data);
	else
		return (0);
	return (1);
}

static void	status_handler(int status_exit, t_data *data)
{
	data->status = status_exit;
	if (data->status_signal > 0)
	{
		data->status = data->status_signal;
		data->status_signal = 0;
	}
}

void	select_cmd(char **inputs, t_data *data)
{
	int		wait_status;
	int		builtin_true;
	pid_t	process_pid;

	if (!data->redir)
	{
		data->redir = 1;
		return ;
	}
	builtin_true = select_from_builtins(inputs, data);
	if (builtin_true == 0)
	{
		process_pid = fork();
		if (process_pid == -1)
			exit(EXIT_FAILURE);
		sig_exec_init();
		if (process_pid == 0)
			exec_cmd(inputs, data);
		wait(&wait_status);
		sig_init();
		status_handler(WEXITSTATUS(wait_status), data);
	}
}
