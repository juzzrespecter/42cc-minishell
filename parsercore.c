#include "minishell.h"

static int	select_from_builtins(char **inputs, t_data *data)
{
	if (!ft_strncmp(inputs[0], "echo", ft_strlen("echo") + 1))
		b_echo(inputs);
	else if (!ft_strncmp(inputs[0], "pwd", ft_strlen("pwd") + 1))
		b_pwd(data);
	else if (!ft_strncmp(inputs[0], "cd", ft_strlen("cd") + 1))
		b_cd(inputs, data);
	else if (!ft_strncmp(inputs[0], "env", ft_strlen("env") + 1))
		b_env(data->env);
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
		if (process_pid == 0)
			exec_cmd(inputs, data);
		wait(&wait_status);
		g_status = WEXITSTATUS(wait_status);
	}
}

void	close_fds(t_data *data)
{
	if (data->fd_in != 0)
	{
		close(data->fd_in);
		data->fd_in = 0;
	}
	if (data->fd_out != 1)
	{
		close(data->fd_out);
		data->fd_out = 1;
	}
}

void	exit_pipe(t_data *data)
{
	free_inputs(data->env);
	free(data->pwd);
	exit(g_status);
}

int	parsercore(char *clean_input, t_data *data, int piped)
{
	char	**inputs;
	int		oldfd[2];

	oldfd[0] = dup(1);
	oldfd[1] = dup(0);
	clean_input = input_cleaner(clean_input);
	parser_redir(&clean_input, data);
	clean_input = expand_variables(clean_input, data);
	clean_input = input_cleaner(clean_input);
	if (*clean_input != 0)
	{
		inputs = input_split(clean_input);
		free(clean_input);
		select_cmd(inputs, data);
		free_inputs(inputs);
	}
	dup2(oldfd[0], 1);
	dup2(oldfd[1], 0);
	close_fds(data);
	close(oldfd[0]);
	close(oldfd[1]);
	if (piped)
		exit_pipe(data);
	return (0);
}
