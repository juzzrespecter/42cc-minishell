#include "minishell.h"

static int	cmd_len(char *input) 
{
	int	len;
	int	quote_ctrl;

	len = 0;
	quote_ctrl = 0;
	while ((quote_ctrl != 0 || !(input[len] == '\n' \
				|| input[len] == ';' || input[len] == '|')) && input[len])
	{
		quote_ctrl = is_quote(input[len], quote_ctrl);
		len++;
	}
	return (len);
}

static int	close_pipes(int pipe_read, int pipe_write)
{
	int	close_read;
	int	close_write;

	close_read = 0;
	close_write = 0;
	if (pipe_read != -1)
		close_read = close(pipe_read);
	if (pipe_write != -1)
		close_write = close(pipe_write);
	return (1 * ((close_read != -1 && close_write != -1)));
	
}

static void		parent_waits(t_data *data)
{
	int	wait_out;
	int	wait_status;

	// aqui hay que pillar el exit_status del ultimo comando ejecutado, no el ultimo terminado
	wait_out = 1;
	while (wait_out > 0)
		wait_out = wait(&wait_status);
	exit(janitor(NULL, data, WEXITSTATUS(wait_status)));
}

static void	pipe_cmd(char *cmd, int pipe_write, int pipe_read, t_data *data)
{
	int	dup_wr;
	int	dup_rd;
	pid_t	child_pid;

	dup_wr = 0;
	dup_rd = 0;
	child_pid = fork();
	if (child_pid == 0)
	{
		if (pipe_write != -1)
			dup_wr = dup2(pipe_write, STDOUT_FILENO);
		if (pipe_read != -1)
			dup_rd = dup2(pipe_read, STDIN_FILENO);
		close_pipes(pipe_write, pipe_read);
		if (dup_wr == -1 || dup_rd == -1)
		{
			free(cmd);
			exit (janitor(NULL, data, errno));
		}
		parsercore(cmd, data, 1);
	}
	close_pipes(pipe_write, pipe_read);
	free(cmd);
	if (child_pid == -1)
		exit (janitor(NULL, data, errno));
}

void			b_pipe(char *input, t_data *data)
{	
	int	i;
	int	len;
	int	fd[2];
	int	pipe_read;
	int	pipe_ret;
	int	next_pipe;
	char	*cmd;

	i = 0;
	next_pipe = 1;
	len = cmd_len(input);
	pipe_read = -1;
	while (next_pipe)
	{
		cmd = ft_substr(input, i, len);
		pipe_ret = pipe(fd);
		if (pipe_ret == -1)
		{
			free(cmd);
			exit(janitor(NULL, data, errno));	
		}
		pipe_cmd(cmd, fd[1], pipe_read, data);
		pipe_read = fd[0];
		i += len + 1;
		len = cmd_len(input + i);
		next_pipe = 1 * (input[i + len] == '|');
	}
	cmd = ft_substr(input, i, len);
	pipe_cmd(cmd, -1, pipe_read, data);
	parent_waits(data);
}
