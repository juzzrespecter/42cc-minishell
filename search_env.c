#include "minishell.h"

/* recibe como parametros el KEY de la variable (p.ej USER para var USER=username) */
/* compara el key con el inicio de la variable y comprueba que esta termina en "=" para evitar falsos positivos */
/* (p. ej. comparando PATH con la variable distinta PATHNAME */
/* devuelve string en caso de exito, puntero a nulo si no ha encontrado coincidencia */

char	*search_env(char **env, char *name)
{
	int	name_len;
	int	i;

	name_len = ft_strlen(name);
	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(name, env[i], name_len) && env[i][name_len] == '=')
			return (env[i]);
		i++;
	}
	return (NULL);
}
