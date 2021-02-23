#include "minishell.h"

int		exec_cmd(char **argv, char **envp)
{
	/* func comprobar si argv[0] es builtin */

	if ((execve(argv[0], argv, envp)) == -1)
		printf("error");

	/* func free mem */
}
