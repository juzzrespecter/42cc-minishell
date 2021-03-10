#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

/*	fd_pipe[2] ; fd_pipe[1] == write to pipe
 *				 fd_pipe[0] == read from pipe		*/

/*	*/

/*	cerrar todos los fd de la pipa antes de llamar a
 *	wait, si queda algun fd vinculado a la pipa que
 *  escribe abierto, la pipa que lee se queda 
 *	esperando a que esta cierre						*/

/*	func imita ( bash> ls -la | grep pipe_test.c )	*/

int	main(int argc, char **argv, char *envp[])
{
	int	fd_pipe[2];

	if ((pipe(fd_pipe)) == -1)
	{
		write(1, strerror(errno), strlen(strerror(errno)));
		exit(EXIT_FAILURE);
	}
	if (fork() == 0)
	{
		char	*argv[] = {"/bin/ls", "-la", NULL}; 

		dup2(fd_pipe[1], STDOUT_FILENO);
		close(fd_pipe[0]);
		close(fd_pipe[1]);
		if (execve(argv[0], argv, envp) == -1)
			write(1, strerror(errno), strlen(strerror(errno)));
		exit(EXIT_FAILURE);
	}
	if (fork() == 0)
	{
		char	*argv[] = {"/usr/bin/grep", "pipe_test.c", NULL};

		dup2(fd_pipe[0], STDIN_FILENO);
		close(fd_pipe[0]);
		close(fd_pipe[1]);
		if (execve(argv[0], argv, envp) == -1)
			write(1, strerror(errno), strlen(strerror(errno)));
		exit(EXIT_FAILURE);
	}
	close(fd_pipe[0]);
	close(fd_pipe[1]);
	wait(NULL);
	return (EXIT_SUCCESS);
}
