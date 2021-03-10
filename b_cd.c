#include "minishell.h"

int	b_cd(char *argv, t_data *data)
{
	char	*path;                                                              /* path al directorio de destino                                */
	char	*home;                                                              /* variable de entorno HOME                                     */
	char	*pwd;                                                               /* variable de entorno PWD (se actualiza con cada llamada a cd  */
	char	*id;                                                                /* id: string en el array de strings env para actualizar PWD    */
	int		export_pwd_ret;

	path = argv[1];
	if (path == NULL)                                                           /* si cd se ejecuta sin argumento, usa la variable de entorno HOME  */
	{
		if ((home = search_env(data->env, "HOME=")) == NULL)
		       return (print_error(argv[1], "HOME not set", cmd->fd_err)); /* sin argumento y sin HOME, cd lanza error y sale con 1            */
		path = home + 5;                                                        /* desplaza el puntero a HOME hasta el inicio del path              */ 
	}
	if (chdir(path) == -1 || (pwd = getcwd(NULL, 0)) == NULL)                   /* lanza chdir e intenta recibir el nuevo path absoluto por getcwd  */
		return (print_error(argv[0], strerror(errno), cmd->fd_err));
	if ((id = ft_strjoin("PWD=", pwd)) == NULL)                                 /* monta el id (name=value) para guardarlo en env                   */
		return (print_error(argv[0], strerror(errno), cmd->fd_err));
	free(pwd);
	export_pwd_ret = env_add_id(id, data);
	free(id);
	return (export_pwd_ret);
}
