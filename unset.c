#include "minishell.h"

static char	**unset_rm_id(char *id, char **env)							/* monta un nuevo array de strings con las variables de */
{																		/* salta la marcada por unset. Probablemente haya una	*/
	int		i;															/* forma mas inteligente de hacer esto.					*/
	int		j;
	int		id_len;
	char	**new_env;

	new_env = (char **)ft_calloc((env_len(env) - 1), sizeof(char *)); 
	if (new_env == NULL)
		return (NULL);
	i = 0;
	j = 0;
	id_len = ft_strlen(id);
	while (env[i])
	{
		if (!(ft_strncmp(id, env[i], id_len) == 0 && env[i][id_len] == '='))	/* si no encuentra coincidencia, copia en new_env	*/
		{
			new_env[j] = ft_strdup(env[i]);
			if (new_env[j] == NULL)
			{
				free_env(new_env);
				return (NULL);
			}
			j++;
		}
		i++;
	}
	new_env[j] = NULL;
	return (new_env);													/* devuelve la nueva tabla	*/
}

static int	unset_id_in_env(char *id, char **env)						/* busca coincidencias entre la variable pasada como	*/
{																		/* argumento y alguna variable de entorno 				*/
	int	i;																/* retorna 0 if success, 1 if failure					*/
	int	id_len;

	i = 0;
	id_len = ft_strlen(id);
	while (env[i])
	{
		if (ft_strncmp(id, env[i], id_len) == 0 && env[i][id_len] == '=')
			return (0);
		i++;
	}
	return (1); 
}

int			unset(t_cmd *cmd, t_data *data)
{
	int		i;
	int		err_status;													/* como en export, se guarda si ha habido un 	*/
	char	**new_env;													/* fallo en una de las peticiones de unset		*/

	i = 0;
	err_status = 0;
	while (cmd->argv[i + 1])
	{
		if (env_parse_id(cmd->argv[i + 1]) == 0)						/* nombre de las variables solo permiten [A-Za-z0-9_]					*/
		{
			if (unset_id_in_env(cmd->argv[i + 1], data->env) == 0)		/* busca coincidencia entre el argumento y el nombre de alguna variable	*/
			{
				if ((new_env = unset_rm_id(cmd->argv[i + 1], data->env)) == NULL)	/* copia la lista de variables sin la coincidente			*/
					return (errno + 128);								/* exit status: 128 + err signal	*/
				free_env(data->env);
				data->env = new_env;
			}
		}
		else
			err_status = print_error(cmd->argv[0], \
					"not a valid identifier", cmd->fd_err);
		i++;
	}
	return (err_status);
}
