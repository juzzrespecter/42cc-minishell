#include "minishell.h"

int			parser_pipe(char *input, int pipe_pos, t_data *data)
{
	char	*new_input;
	int		space;

	space = 0;
	if (input[pipe_pos - 1] == ' ')
		space = 1;
	new_input = ft_strdup(&input[pipe_pos + 1]);
	input[pipe_pos - space] = '\0';
	return (b_pipe(input, new_input, data));
}

int			parser_semicolon(char *input, int semicolon_pos, t_data *data)
{
	char	*new_input;
	int		space;

	space = 0;
	if (input[semicolon_pos - 1] == ' ')
		space = 1;
	new_input = ft_strdup(&input[semicolon_pos + 1]);
	input[semicolon_pos - space] = '\0';
	parsercore(input, data, 0);
	if (g_status != 130)
		return (parser_start(new_input, data));
	else
		free(new_input);
	return (0);
}

int			check_special(char **input, int *i, t_data *data)
{
	if ((*input)[*i] == '\'')
	{
		(*i)++;
		while ((*input)[*i] != '\'')
			(*i)++;
	}
	else if ((*input)[*i] == '|')
	{
		parser_pipe((*input), *i, data);
	}
	else if ((*input)[*i] == ';')
	{
		parser_semicolon((*input), *i, data);
		return (1);
	}
//	else if ((*input)[*i] == '$')
//		parser_variable(input, i, data);
	(*i)++;
	return (0);
}

int			parser(char *input, t_data *data, int piped)
{
	int		i;
	int		slash_count;

	i = 0;
	while (input[i])
	{
		if (input[i] == '"')
		{
			i++;
			while (input[i] != '"')
			{
				slash_count = 0;
				while (input[i] == '\\' && ++i)
					slash_count++;
//				if (input[i] == '$' && !(slash_count % 2))
//					parser_variable(&input, &i, data);
				if (slash_count && !(slash_count % 2))
					i--;
				i++;
			}
		}
		if (check_special(&input, &i, data))
			return (0);
	}
	return (parsercore(input, data, piped));
}
