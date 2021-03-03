#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "libft.h"
#include <sys/stat.h>

	// del input tenemos que recoger los comandos validos (cualquier word que no sea una redireccion)
	// guardamos comandos en argv, argv[0] es el comando a ejecutar, el resto son los argumentos del comando
	// parse argv[0] en busca de slashes:
	//   hay un slash: montar en argv[0], execve(argv[0], argv, data->env)
	//   no hay un slash:
	//   check builtins:
	//     existe un builtin con ese nombre -> llamada a funcion (parece que en pipalineas se forkea este proceso tambien???)
	//     no existe un builtin:
	//       comprobar variable de entorno PATH:
	//       si existe: montar argv[0] con cada path en la variable y comprobar si existe
	//         existe PATH/argv[0], execve(PATH/argv[0], argv, data->env)
	//         no existe: return error
	//       no existe PATH: return error
	//
	// si recibe una lista de comandos vacia, ignora la ejecucion y devuelve 0
	// (a este punto solo se puede llegar con la expansion de una variable que resulte en una cadena vacia)
	// p. ej >~ export var="" ; $var;


	// faltan las redirecciones de stdin, stdout, stderr si las hubieran

typedef struct s_data {
	char **env;
	char *sh_name;
}				t_data;
char	*search_env(char **env, char *name);

int	print_error(char *sh, char *cmd, char *err)
{
	printf("%s: %s: %s\n", sh, cmd, err);
	return (345);
}

static int	slash_in_cmd(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '/')
			return (1);
		i++;
	}
	return (0);
}

static char	**cmd_get_paths(char *path_env)
{
	int		i;
	int		paths_count;
	char	**paths;

	i = 0;
	paths_count = 0;
	while (path_env[i])
	{
		if (path_env[i] == ':')
			paths_count++;
		i++;
	}
	if ((paths = ft_split(path_env + 5, ':')) == NULL)
		return (NULL);
	return (paths);
}

int			exec_cmd(char **argv, t_data *data)
{
	char	*cmd;
	char	*path_env;
	char	**paths;
	char	*full_path;
	int		i;
	int		stat_out;
	struct stat buff;

	i = 0;
	cmd = argv[0];
	if (!cmd)
		return (0);
	if (!slash_in_cmd(argv[0]))
	{
		if (!(path_env = search_env(data->env, "PATH")))  /* no hay variable PATH en el entorno */
		{
			print_error(data->sh_name, argv[0], "No such file or directory");
			exit(127);
		}
		if (!(paths = cmd_get_paths(path_env)))  /* error al asginar memoria dinamica */
		{
			print_error(data->sh_name, argv[0], strerror(errno));
			exit(errno + 128);
		}
		if (!paths[0]) /* variable PATH vacia */
		{
			print_error(data->sh_name, argv[0], "No such file or directory");
			exit(127);
		}
		while (paths[i])
		{
			if (!(full_path = ft_strjoin(paths[i], "/")))
			{
				print_error(data->sh_name, argv[0], strerror(errno));
				exit(errno + 128);
			}
			if (!(cmd = ft_strjoin(full_path, argv[0])))
			{
				print_error(data->sh_name, argv[0], strerror(errno));
				exit(errno + 128);
			}
			free(full_path);
			if ((stat_out = stat(cmd, &buff)) == 0)
				break;
			i++;
		}
		if (paths[i] == NULL)
		{
			print_error(data->sh_name, argv[0], "No such file or directory");
			exit(127);
		} 
	}
	execve(cmd, argv, data->env);
	print_error(data->sh_name, cmd, strerror(errno));  /* llega al fin de la funcion si execve devuelve -1 */
	/* func cerrar fds, free argv */
	printf("hola\n");
	exit(errno + 128);
}
