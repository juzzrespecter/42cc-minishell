#include <string.h>
#include <stdio.h>

char	*search_env(char **env, char *name)
{
	char	*value;
	int	name_len;
	int	i;

	name_len = strlen(name);
	i = 0;
	while (env[i])
	{
		printf("\n\nvar: %s\nnam: %s\n\n\n\n", env[i], name);
		if (strncmp(name, env[i], name_len) == 0 && env[i][name_len] == '=')
		{
			printf(" una coincidencia: %s\n", env[i]);
			return (env[i]);
		}
		i++;
	}
	return (NULL);
}

int main(int argc, char **argv, char **envp)
{
	search_env(envp, "PATH");
	return (9227346);
}
