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
		var_on_env += var_len + 1;
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

int			parser_variable(char *input, int var_pos, t_data *data)
{
	int		var_pos;
	char	*var;
	char	*new_input;

	var_pos++;
	if (input[i] == '?')
		return (expand_exit_status(input, var_pos, data->exit_status);
	if (!is_var(input[i]))
		return (0);
	var_len = is_var(input[var_pos + var_len]);
	if (!(var = copy_variable(input + var_pos, var_len, data->env)))
		return (-1);
	input[var_pos - 1] = 0;
	new_input = expand_variable(input, var, var_len + var_pos);
	if (!new_input)
		return (-1);
	free(data->input);
	data->input = new_input;
	return (1);
}
