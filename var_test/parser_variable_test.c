#include "test.h"

static char	*copy_variable(char *input, int var_len, char **env)
{
	char *var_on_input;
	char *var_on_env;

	if (!(var_on_input = (char *)malloc(sizeof(char) * (var_len + 1))))
		return (NULL);
	ft_strlcpy(var_on_input, input, var_len + 1);
	var_on_env = search_env(var_on_input);
	free(var_on_input);
	if (!var_on_env)
		var_on_env = ft_strdup("");
	else
		var_on_env += var_len + 1;
	return (var_on_env);
}

static char	*clear_var_table(char **var_table)
{
	int	i;

	i = 0;
	while (var_table[i])
	{
		free(var_table[i]);
		i++;
	}
	return (NULL);
}

static char	*expand_variable(char *input, char *var, int var_len)
{
	int		i;
	char	*new_input;
	char	*aux_input;
	char	**var_table;

	i = 0;
	if (!(var_table = ft_split_str(var, " \t")))
		return (NULL);
	if (!(new_input = ft_strdup(input)))
		return (clear_var_table(var_table));
	while (var_table[i])
	{
		aux_input = new_input;
		new_input = ft_strjoin(new_input, var_table[i]);
		free(aux_input);
		if (!new_input)
			return (clear_var_table(var_table));
		i++;
	}
	clear_var_table(var_table);
	aux_input = new_input;
	new_input = ft_strjoin(new_input, input + var_len);
	free(aux_input);
	return (new_input);
}

int			parser_variable(char *input, int var_pos, t_data *data)
{
	int		var_len;
	char	*var;
	char	*new_input;

	var_pos++;
	var_len = 0;
	if (is_blank(input[var_pos + i]) || is_op_ctrl(input[var_pos + i]))
		return (0);
	while (is_var(input[var_pos + var_len]))
		var_len++;
	if (!(var = copy_variable(input + var_pos, var_len, data->env)))
		return (-1);
	input[var_pos--] = 0;
	if (!var[0])
		new_input = ft_strjoin(input, "");
	else
		new_input = expand_variable(input, var);
	free(var);
	if (!new_input)
		return (-1);
	return (1);
}
