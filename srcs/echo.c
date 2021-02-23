#include "minishell.h"

int		echo(char **argv)
{
	if (write(1, argv[1], strlen(argv[1])) == -1)
		return (1);
	return(0);
}
