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
	//       no existe PATH: intenta ejecutar el comando
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

static char	*exec_mnt_path(char *path, char *cmd)
{
	int		i;
	char	*aux_path;

	i = 0;
	while (path[i])
	{
		if (!paths[i + 1] && !(paths[i] == '/'))
		{
			aux_path = path;
			path = ft_strjoin(path, "/");
			free(aux_path);
			if (!path)
				return (NULL);
		}
		aux_path = path;
		path = ft_strjoin(paths[i], cmd);
		free(aux_path);
		return (!path ? NULL : path);
}

static char	*clean_paths(char **paths)
{
	int	i;

	i = 0;
	while (paths[i])
	{
		free(paths[i]);
		i++;
	}
	return (NULL);
}

static char	**exec_get_paths(char *path_env, char *cmd)
{
	int	i;
	char	**paths;

	i = 0;
	if ((paths = ft_split(path_env + 5, ':')) == NULL)
		return (NULL);
	while (paths[i])
	{
		if (!(paths[i] = exec_mnt_path(paths[i], cmd)))
			return (clean_paths(paths));
		i++;
	}
	return (paths);
}

int			exec_cmd(char **argv, t_data *data)
{
	struct stat	buff;
	char		**paths;
	char		*path_env;
	int			i;

	i = 0;
	if (!argv[0])
		exit (janitor(argv, data, 0));
	path_env = search_env("PATH", data->env);
	if (!slash_in_cmd(argv[0]) && path_env)
	{
		if (!(paths = exec_get_paths(path_env, argv[0])))
			exit(janitor(argv, data, errno));
		while (paths[i])
		{
			if (!stat(paths[i], &buff))
				break;
			i++;
		}
		if (!paths[i])
			exit(janitor(argv, data, 127));
	}
	execve(cmd, argv, data->env);
	exit(janitor(argv, data, errno));
}
