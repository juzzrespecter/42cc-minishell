#include "minishell.h"

int		b_echo(char **argv)
{
	int		n_flag;					/* flag -n: no imprime salto de linea al final de la cadena  */
	int		i;

	n_flag = 0;
	i = 0;
	if (argv[1] != NULL)
		if (ft_strncmp(argv[1], "-n", ft_strlen(argv[1])) == 0)	/* solo toma en cuenta el flag si es el primer argumento del comando	*/
			n_flag = 1;
	while (argv[i + 1] != NULL)
	{
		write(1, argv[i + 1], ft_strlen(argv[i + 1]));		/* imprime	en fd de output	*/
		if (argv[i + 2] != NULL)
			write(1, " ", 1);
		else
			if (n_flag == 0)									/* ignora el salto de linea si flag -n == true	*/
				write(1, "\n", 1);
		i++;
	}
	return (0);
}
