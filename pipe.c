#include "minishell.h"

void	parent(char *input2, t_data *data, int pid, int *fds)
{
	int		oldfd;
	int		status;

	if (waitpid(pid, &status, 0) != pid)
		exit(EXIT_FAILURE);
	free(g_input);
	g_input = NULL;
	oldfd = dup(0);
	dup2(fds[0], 0);
	close(fds[0]);
	close(fds[1]);
	parser_start(input2, data);
	dup2(oldfd, 0);
	close(oldfd);
}

int		b_pipe(char *input1, char *input2, t_data *data)
{
	pid_t	pid;
	int		fds[2];

	if (pipe(fds) < 0)
		exit(EXIT_FAILURE);
	pid = fork();
	if (pid == 0)
	{
		free(input2);
		dup2(fds[1], 1);
		close(fds[0]);
		close(fds[1]);
		parsercore(input1, data, 1);
	}
	else if (pid < 0)
		exit(EXIT_FAILURE);
	else
	{
		free(input1);
		input1 = NULL;
		parent(input2, data, pid, fds);
	}
	return (1);
}
