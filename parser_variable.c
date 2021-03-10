#include "minishell.h"

static char	*copy_variable(char *input, int var_len, char **env)
{
	char *var_on_input;
	char *var_on_env;

	if (!(var_on_input = (char *)malloc(sizeof(char) * (var_len + 1))))
		return (NULL);
	ft_strlcpy(var_on_input, input, var_len + 1);
	var_on_env = search_env(env, var_on_input);
	free(var_on_input);
	if (!var_on_env)
		var_on_env = ft_strdup("");
	else
		var_on_env = ft_strdup(var_len + 1);
	return (var_on_env);
}

static char	*expand_variable(char *input, char *var, int input_pos)
{
	char	*new_input;
	char	*aux_input;

	if (!(new_input = ft_strdup(input)))
		return (NULL);
	aux_input = new_input;
	new_input = ft_strjoin(new_input, var);
	free(aux_input);
	if (!new_input)
		return (NULL);
	aux_input = new_input;
	new_input = ft_strjoin(new_input, input + input_pos);
	free(aux_input);
	return (new_input);
}

static int	expand_exit_status(char input,int var_pos, int exit_status)
{
	char	*new_input;
	char	*aux_input;

	if (!(new_input = ft_itoa(exit_status)))
		return (-1);
	input[var_pos - 1] = 0;
	aux_input = new_input;
	new_input = ft_strjoin(input, new_input);
	free(aux_input);
	if (!new_input)
		return (-1);
	aux_input = new_input;
	new_input = ft_strjoin(new_input, input + 1);
	free(aux_input);
	return (!new_input ? -1 : 1);
}

/* parser_variable: recibe la cadena y la posicion de la posible variable a expandir.
 * devuelve (1) con exito, (-1) con fallo de asignacion de memoria.
 *    trabaja cuatro casos: con $?, expande la variable con el valor del codigo de salida almacenado en data->exit_code,
 *    con un nombre de variable no valido, retorna (1) sin editar la cadena, con $VAR definida en el entorno, expande la
 *    variable, y con $VAR sin definir, la sustituye por una cadena vacia.
 *
 *    expand_exit_status(); sustituye la variable $? por el codigo de salida del ultimo comando ejecutado.
 *    copy_variable(); se encarga de buscar coincidencias entre la variable en input y las variables del entorno,
 *       devuelve NULL en caso de error, la cadena con la variable en caso de exito.
 *    expand_variable(); sustituye la variable obtenida en copy_variable en la cadena input.
 *       devuelve la nueva cadena con la variable expandida en caso de exito, NULL en caso de error.
 */

int			parser_variable(char *input, int var_pos, t_data *data)
{
	int		var_pos;
	char	*var;
	char	*new_input;

	var_pos++;
	if (input[i] == '?')
		return (expand_exit_status(input, var_pos, data->exit_status);
	if (!is_var(input[i]))
		return (1);
	var_len = is_var(input[var_pos + var_len]);
	if (!(var = copy_variable(input + var_pos, var_len, data->env)))
		return (-1);
	input[var_pos - 1] = 0;
	new_input = expand_variable(input, var, var_len + var_pos);
	free(var);
	if (!new_input)
		return (-1);
	free(data->input);
	data->input = new_input;
	return (1);
}
