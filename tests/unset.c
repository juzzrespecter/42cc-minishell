#include "minishell.h"

int	unset(char **argv, char **envp)
{
	int	i;
	int	j;
	int	var_len;

/*	argv[1] == 0 NULL == error */	
	i = 0;
	j = 0;
	while (argv[i])
	{
		var_len = ft_strlen(argv[i]);
		while (envp[j])
		{
			if (ft_strncmp(argv[i], envp[j], var_len) == 0)
				/* mover todo el array de envp una posicion, NULL a la ultima cadena */
			{
				break;
			}
		}
	}
}
