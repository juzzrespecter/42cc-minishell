#include "minishell.h"

static int		export_print(t_data *data)  /* imprime las variables de la forma: declare -x NAME="VALUE"   */
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
		write(1, "declare -x ", 11);
		write(1, value, j);
		write(1, "\"", 1);
		write(1, value + j, ft_strlen(value + j));
		write(1, "\"\n", 2);
		i++;
	}
	return (0);
}

int			b_export(char **argv, t_data *data)        /* guarda nuevas variables en la lista de variables de entorno a exportar en procesos hijo	*/
{
	int		i;
	int		err_status;                                 /* error de salida: con solo un argumento que falle la validacion   */
                                                        /* export() retorna 1, aunque el resto de argumentos hayan sido     */
	err_status = 0;                                     /* exportados correctamente                                         */
	i = 0;
	if (argv[1] == NULL)
		return (export_print(data));       /* sin argumentos, export imprime las variables a ser exportadas, que   */
	while (argv[i] != NULL)                        /* como no nos piden que gestionemos variables locales, son todas.      */
	{
		if (env_parse_id(argv[i]) == 0)            /* func parse id: el nombre de la variable solo permie [A-Za-z0-9_]     */
		{
			if (env_add_id(argv[i], data) == -1)   /* guarda la variable en la lista de variabes de entorno                */
				return (errno + 128);
		}
		else
			err_status = print_error(argv[i], "not a valid identifier");
		i++;
	}
	return (err_status);
}
