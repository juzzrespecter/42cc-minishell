#include "minishell.h"

static int		export_print(t_data *data, int fd_out)	/* imprime las variables de la forma: declare -x NAME="VALUE"	*/
{
	int		i;
	int 	j;
	char	*value;

	i = 0;
	while (data->env[i])
	{
		value = data->env[i];
		j = 0;
		while (value[j] != '=' && value[j] != 0)
			j++;
		write(fd_out, "declare -x ", 11);
		write(fd_out, value, j);
		write(fd_out, "\"", 1);
		write(fd_out, value + j, ft_strlen(value + j));
		write(fd_out, "\"\n", 2);
		i++;
	}
	return (0);
}

int				export(t_cmd *cmd, t_data *data)		/* guarda nuevas variables en la lista de variables de entorno a exportar en procesos hijo	*/
{
	int		i;
	int		err_status;									/* error de salida: con solo un argumento que falle la validacion	*/
														/* export() retorna 1, aunque el resto de argumentos hayan sido		*/
	err_status = 0;										/* exportados correctamente											*/
	i = 0;
	if (cmd->argv[1] == NULL)
		return (export_print(data, cmd->fd_out));		/* sin argumentos, export imprime las variables a ser exportadas, que	*/
	while (cmd->argv[i] != NULL)						/* como no nos piden que gestionemos variables locales, son todas.		*/
	{
		if (env_parse_id(cmd->argv[i]) == 0)			/* func parse id: el nombre de la variable solo permie [A-Za-z0-9_]		*/
		{
			if (env_add_id(cmd->argv[i], data) == -1)	/* guarda la variable en la lista de variabes de entorno				*/
				return (errno + 128);
		}
		else
			err_status = print_error(cmd->argv[i], \	/* lanza el error de identificador no valido, pero procesa todos los args */
			"not a valid identifier", cmd->fd_err);
		i++;
	}
	return (err_status);
}
