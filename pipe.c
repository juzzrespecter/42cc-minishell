#include "../minishell.h"

void	parent(char *input2, t_data *data, int pid, int *fds)
{
	int	oldfd;
	int	status;

	if (waitpid(pid, &status, 0) != pid) //espera por la finalización del hijo y devuelve su pid como confirmación tras sesgarlo
		exit(EXIT_FAILURE);	     // si no es así salimos y lanzamos error
	free(data->input);
	data->input = NULL;
	oldfd = dup(0);		//hacemos copia del fd de lectura (stdin)
	dup2(fds[0], 0);	//en vez de leer del stdin(0) hacemos que lea del fds[0]
	close(fds[0]);
	close(fds[1]);
	parser(input2, data);	//ejecutamos input2
	dup2(oldfd, 0);		//en vez de leer del stdin(0) hacemos que lea del oldfd, que era una copia del stdin(0)
	close(oldfd);
}

int	b_pipe(char *input1, char *input2, t_data *data)
{
	pid_t	pid;
	int	fds[2];				//fds[0] lectura y fds[1] escritura

	if (pipe(fds) < 0)			//si devuelve -1 error en la creacion del pipe
		exit(EXIT_FAILURE);
	pid = fork();				//pipe siempre antes de fork para que padre e hijo compartan variables
	if (pid == 0)				//si es 0 se ha creado el fork y se está ejecutando el hijo
	{
		free(input2);
		dup2(fds[1], 1);		//en vez de escribir en stdout(1) hacemos que escriba en fds[1]
		close(fds[0]);
		close(fds[1]);
		parser(input1, data);		//ejecutamos input1
	}
	else if (pid < 0)			//-1 error al creal el fork
		exit(EXIT_FAILURE);
	else					//>0 fork creado, se está ejecutando el padre y nos ha devuelto el PID del hijo
	{
		free(input1);
		input1 = NULL;
		parent(input2, data, pid, fds);	//vamos al padre para ejecutar input 2
	}
	return (1);
}
