#include <unistd.h>
#include <stdio.h>
#include "libft.h"

int	parser(char *new_input)
{
	printf("%s\n", new_input);
	return (0);
}

int	parser_variable(char *input, int var_pos, t_data *data)
{
	int		i;
	int		var_len;
	char	*var_name;
	char	*env_var;
	char	**env_var_expanded;
	char	*prev_input;
	char 	*post_input;
	char	*aux_input;
	char	*new_input;

	i = 1;
	var_len = 0;
	if (is_blank(input[var_pos + i]) || is_op_ctrl(input[var_pos + i]))
		parser(input);		/* $ no es un marcador de expansion de var */
	while (is_word(input[var_pos + i]))
	{
		var_len++;
		i++;
	}
	var_name = (char *)malloc(sizeof(char) * (var_len + 1));
	ft_strlcpy(var_name, input + i, var_len + 1);
	prev_input = (char *)malloc(sizeof(char) * i);
	ft_strlcpy(prev_input, input, i);
	post_input = ft_strdup(input + var_len);
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
			aux_input = prev_input;
			prev_input = ft_strjoin(prev_input, env_var_expanded[i]);
			free(aux_input);
			i++;
		}
	}
	new_input = ft_strjoin(prev_input, post_input);
	free(prev_input);
	free(post_input);
	parser(new_input, data);
}

int	main(int argc, char **argv, char **envp)
{
	char	buffer[1000];

	while (1)
	{
		bzero(buffer, 1000);
		read (0, buffer, 1000);
		parser_variable(buffer, envp);	
	}
	return (0);
}
