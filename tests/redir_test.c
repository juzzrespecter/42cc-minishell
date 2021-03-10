#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

/*	>"/path/to/file" == stdout to file fd			
 *	<"/path/to/file" == stdin to file fd			*/

/*	ls -la >textfile; grep redir_test.c <textfile	*/

int	main(int argc, char **argv, char **envp)
{
	int		fd_file;
	char	*path_to_file = "./textfile";

	if (fork() == 0)
	{
		char	*argv[] = {"/bin/ls", "-la", NULL};

		if ((fd_file = open(path_to_file, O_CREAT | O_TRUNC | O_WRONLY, 0666)) == -1)
		{
			write(1, strerror(errno), strlen(strerror(errno)));
			exit(EXIT_FAILURE);
		}
		dup2(fd_file, STDOUT_FILENO);
		close(fd_file);
		if (execve(argv[0], argv, envp) == -1)
		{
			write(1, strerror(errno), strlen(strerror(errno)));
			exit(EXIT_FAILURE);
		}
	}
	wait(NULL);									/* ; */
	if (fork() == 0)
	{
		char	*argv[] = {"/usr/bin/grep", "redir_test.c", NULL};

		if ((fd_file = open(path_to_file, O_RDONLY)) == -1)
		{
			write(1, strerror(errno), strlen(strerror(errno)));
			exit(EXIT_FAILURE);
		}
		if ((dup2(fd_file, STDIN_FILENO)) == -1)
		{
			write(1, strerror(errno), strlen(strerror(errno)));
			exit(EXIT_FAILURE);
		}
		close(fd_file);
		if (execve(argv[0], argv, envp) == -1)
		{
			write(1, strerror(errno), strlen(strerror(errno)));
			exit(EXIT_FAILURE);
		}
	}
	close(fd_file);
	wait(NULL);
	return (EXIT_SUCCESS);
}
