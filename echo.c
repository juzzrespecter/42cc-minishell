#include "minishell.h"

int		echo(t_cmd *cmd)
{
	int		n_flag;					/* flag -n: no imprime salto de linea al final de la cadena  */
	int		i;
	int		fd_out;
	char	**argv;

	n_flag = 0;
	i = 0;
	fd_out = cmd->fd_out;
	argv = cmd->argv;
	if (argv[1] != NULL)
		if (ft_strncmp(argv[1], "-n", ft_strlen(argv[1])) == 0)	/* solo toma en cuenta el flag si es el primer argumento del comando	*/
			n_flag = 1;
	while (argv[i + 1] != NULL)
	{
		write(fd_out, argv[i + 1], ft_strlen(argv[i + 1]));		/* imprime	en fd de output	*/
		if (argv[i + 2] != NULL)
			write(fd_out, " ", 1);
		else
			if (n_flag == 0)									/* ignora el salto de linea si flag -n == true	*/
				write(fd_out, "\n", 1);
		i++;
	}
	return (0);
}
