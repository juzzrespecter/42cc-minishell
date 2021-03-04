#include "minishell.h"

static int	is_var(char input)
{
	if (ft_isalnum(input) || input == '_')
		return (1);
	return (0);
}

int	parser_variable(char *input, int var_pos, t_data *data)
{
	int		i;
	int		var_len;
	char	*var_name;
	char	*env_var;
	char	**env_var_expanded;
	char	*input_prev;
	char 	*input_post;
	char	*aux_input;
	char	*new_input;

	i = 1;
	var_len = 0;
	if (is_blank(input[var_pos + i]) || is_op_ctrl(input[var_pos + i]))
		parser(input);		/* $ no es un marcador de expansion de var */
	while (is_var(input[var_pos + i]))
	{
		var_len++;
		i++;
	}
	var_name = (char *)malloc(sizeof(char) * (var_len + 1));
	ft_strncpy(var_name, input + i, var_len + 1);
	input_prev = (char *)malloc(sizeof(char) * i);
	ft_strncpy(input_prev, input, i);
	input_post = ft_strdup(input + var_len);
	env_var = search_env(var_name, data->env);
	free(input);
	if (!env_var)
	{
		env_var = ft_strdup("");
		aux_input = prev_input;
		prev_input = ft_strjoin(prev_input, env_var);
		free(aux_input);
	}
	else
	{
		i = 0;
		env_var += var_name;
		env_var_expanded = ft_split_str(env_var, " \t");
		while (env_var_expanded[i])
		{
			aux_input = input_prev;
			input_prev = ft_strjoin(input_prev, env_var_expanded[i]);
			free(aux_input);
			i++;
		}
	}
	new_input = ft_strjoin(prev_input, post_input);
	free(prev_input);
	free(post_input);
	parser(new_input, data);
}
