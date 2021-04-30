#include "minishell.h"

static char	*copy_variable(char *input, int var_len, int quote, char **env)
{
	char	*var_on_input;
	char	*var_on_env;

	var_on_input = (char *)malloc(sizeof(char) * (var_len + 1));
	if (!var_on_input)
		return (NULL);
	ft_strlcpy(var_on_input, input, var_len + 1);
	var_on_env = search_env(env, var_on_input);
	free(var_on_input);
	if (!var_on_env)
		var_on_env = ft_strdup("");
	else
		var_on_env = copy_literal(var_on_env + var_len + 1, quote);
	return (var_on_env);
}

static char	*concat_variable(char *input, char *var, int input_pos)
{
	char	*new_input;
	char	*aux_input;

	new_input = ft_strdup(input);
	if (!new_input)
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

static int	expand_exit_status(char **input_ptr, int var_pos, int status)
{
	char	*new_input;
	char	*aux_input;
	char	*input;

	input = *input_ptr;
	new_input = ft_itoa(status);
	if (!new_input)
		return (-1);
	input[var_pos - 1] = 0;
	aux_input = new_input;
	new_input = ft_strjoin(input, new_input);
	free(aux_input);
	if (!new_input)
		return (-1);
	aux_input = new_input;
	new_input = ft_strjoin(new_input, input + var_pos + 1);
	free(aux_input);
	*input_ptr = new_input;
	if (!new_input)
		return (-1);
	return (1);
}

static int	parser_variable(char **input_ptr, int pos, int quote, t_data *data)
{
	int		var_len;
	int		len;
	char	*var;
	char	*new_input;
	char	*input;

	pos++;
	input = *input_ptr;
	if (input[pos] == '?')
		return (expand_exit_status(input_ptr, pos, data->status));
	var_len = is_var(input + pos);
	if (var_len == 0)
		return (1);
	var = copy_variable(input + pos, var_len, quote, data->env);
	if (!var)
		return (-1);
	input[pos - 1] = 0;
	len = ft_strlen(var);
	new_input = concat_variable(input, var, var_len + pos);
	free(var);
	if (!new_input)
		return (-1);
	free(input);
	*input_ptr = new_input;
	return (len);
}

char	*expand_variables(char *input, t_data *data)
{
	int		i;
	int		var_out;
	int		quote_ctrl;

	i = 0;
	quote_ctrl = 0;
	while (input[i])
	{
		quote_ctrl = is_quote(input[i], quote_ctrl);
		if (input[i] == '\\' && input[i + 1] == '$' && quote_ctrl == 2)
			i += 2;
		if (input[i] == '$' && ((quote_ctrl % 2) == 0))
		{
			var_out = parser_variable(&input, i, quote_ctrl, data);
			if (var_out == -1)
				return (NULL);
			i += var_out;
		}
		else
			i++;
	}
	return (input);
}
