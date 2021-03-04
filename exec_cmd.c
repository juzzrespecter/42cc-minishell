#include "minishell.h"

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
	int	i;
	int	j;
	char	*aux_path;
	char	**paths;

	i = 0;
	j = 0;
	if ((paths = ft_split(path_env + 5, ':')) == NULL)
		return (NULL);
	while (paths[i])
	{
		while (paths[i][j])
		{
			if (!paths[i][j + 1] && !(paths[i][j] == '/'))
			{
				aux_path = paths[i];
				paths[i] = ft_strjoin(paths[i], "/");
				free(aux_path);
			}
			if (!paths[i])
				return (NULL);
			j++;
		}
		j = 0;
		i++;
	}
	return (paths);
}

int			exec_cmd(char **argv, t_data *data)
{
	char		*cmd;
	char		**paths;
	int		i;
	struct stat	buff;

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
			if (!(cmd = ft_strjoin(paths[i], argv[0])))
			{
				print_error(data->sh_name, argv[0], strerror(errno));
				exit(errno + 128);
			}
			if (!stat(cmd, &buff))
				break;
			i++;
			free(cmd);
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
	exit(errno + 128);
}
