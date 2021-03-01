#include "minishell.h"

static char		**export_new_env(char **env, char *id)
{
	char	*new_id;
	char	**new_env;
	int		old_env_len;
	int		i;

	i = 0;
	old_env_len = env_len(env);
	new_env = (char **)ft_calloc(old_env_len + 1, sizeof(char *));
	new_id = ft_strdup(id);
	if (new_env == NULL || new_id == NULL)
		return (NULL);
	while (env[i])
	{
		if ((new_env[i] = ft_strdup(env[i])) == NULL)
		{
			free_env(new_env);
			return (NULL);
		}
		i++;
	}
	new_env[i] = new_id;
	return (new_env);
}

int				env_add_id(char *id, t_data *data)  /* 2 casos: la variable a guardar existe, se actualiza ese array                */
{                                                   /* o no encuentra coincidencia, crea nueva tabla con la nueva variable al final */
	int		i;                                      /* devuelve 0 con exito, -1 con fallo de asignacion de memoria dinamica         */
	char	**new_env;

	i = 0;
	if (ft_strrchr(id, '=') == NULL)                /* si el formato de id es NAME sin una variable, se ignora y no lanza fallo */
			return (0);
	while (data->env[i])
	{
		if (ft_strncmp(data->env[i], id, (ft_strrchr(id, '=') - id + 1)) == 0)  /* variable existe: la actualiza y vuelve       */	
		{
			data->env[i] = ft_strdup(id);
			return (data->env[i] ? 0 : -1);
		}
		i++;
	}
	if ((new_env = export_new_env(data->env, id)) == NULL)  /* variable no existe: crea nueva tabla    */
		return (-1);
	free_env(data->env);
	data->env = new_env;
	return (0);
}

int				env_parse_id(char *id)              /* analisis del string de la variable de entorno, id == NAME=VALUE  */
{                                                   /* devuelve 0 si el nombre es valido, 1 si encuentra error          */ 
	int		i;

	i = 0;
	while (id[i] != '=' && id[i] != 0)
	{
		if (!(id[i] == '_' || ft_isalnum(id[i])))   /* name solo admite caracteres [A-Za-z0-9_] */
			return (1);
		i++;
	}
	if (!i)                                         /* id no admite una cadena vacia como nombre de variable    */
		return (1);
	return (0);
}
