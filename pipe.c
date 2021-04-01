#include "minishell.h"

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

static void	parent_waits(pid_t last_pid, t_data *data)
{
	int	wait_out;
	int	wait_status;

	waitpid(last_pid, &wait_status, 0);
	wait_out = 1;
	while (wait_out > 0)
		wait_out = wait(NULL);
	exit(janitor(NULL, data, WEXITSTATUS(wait_status)));
}

static void	pipe_cmd(t_pipe *pipe_s, int pipe_write, t_data *data)
{
	int		dup_wr;
	int		dup_rd;

	dup_wr = 0;
	dup_rd = 0;
	pipe_s->child_pid = fork();
	if (pipe_s->child_pid == 0)
	{
		if (pipe_write != -1)
			dup_wr = dup2(pipe_write, STDOUT_FILENO);
		if (pipe_s->pipe_read != -1)
			dup_rd = dup2(pipe_s->pipe_read, STDIN_FILENO);
		close_pipes(pipe_write, pipe_s->pipe_read);
		if (dup_wr == -1 || dup_rd == -1)
		{
			free(pipe_s->cmd);
			exit(janitor(NULL, data, errno));
		}
		parsercore(pipe_s->cmd, data, 1);
	}
	close_pipes(pipe_write, pipe_s->pipe_read);
	free(pipe_s->cmd);
	if (pipe_s->child_pid == -1)
		exit(janitor(NULL, data, errno));
}

static int	b_pipe_next(t_pipe *pipe_s, int fd[2], char *input, int i)
{
	int	len;

	pipe_s->pipe_read = fd[0];
	len = pipe_s->cmd_len + 1;
	i += len;
	pipe_s->cmd_len = cmd_len(input + i);
	pipe_s->next_pipe = 1 * (input[i + pipe_s->cmd_len] == '|');
	return (len);
}

void	b_pipe(char *input, t_data *data)
{
	t_pipe	pipe_s;	
	int		i;
	int		fd[2];
	int		pipe_ret;

	i = 0;
	pipe_s.next_pipe = 1;
	pipe_s.cmd_len = cmd_len(input);
	pipe_s.pipe_read = -1;
	while (pipe_s.next_pipe)
	{
		pipe_s.cmd = ft_substr(input, i, pipe_s.cmd_len);
		pipe_ret = pipe(fd);
		if (pipe_ret == -1)
		{
			free(pipe_s.cmd);
			exit(janitor(NULL, data, errno));
		}
		pipe_cmd(&pipe_s, fd[1], data);
		i += b_pipe_next(&pipe_s, fd, input, i);
	}
	pipe_s.cmd = ft_substr(input, i, pipe_s.cmd_len);
	pipe_cmd(&pipe_s, -1, data);
	parent_waits(pipe_s.child_pid, data);
}
