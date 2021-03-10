#include "../minishell.h"

int	parsercore(char *input, t_data *data, int piped)
{
	char	*clean_input;	
	char	**inputs;
	int	oldfd[2];
	
	if (parser_error(input))			//chequeamos errores sintaxis 			****TO DO****
	{
		free(input);
		return (0);
	}
	oldfd[0] = dup(1);				//copia de stdout en oldfd[0]
	oldfd[1] = dup(0);				//copia de stdin en oldfd[1]
	clean_input = input_cleaner(input);		//limpiamos input				****TO DO****
	parser_redir(&input, data);			//gestionamos redireccionamientos		
	inputs = input_split(clean_input);		//dividimos input		 
	free(clean_input);
	select_cmd(inputs, data);			//seleccionamos comando a ejecutar
	free_inputs(inputs);
	dup2(oldfd[0], 1);				//en vez de escribir en stdout(1) hacemos que escriba en oldfd[0]			
	dup2(oldfd[1], 0);				//en vez de leer de stdin(0) hacemos que lea de oldfd[1]
	close_fds(data);
	close(oldfd[0]);
	close(oldfd[1]);
	if (piped)
	{
		free_inputs(data->env);
		if (g_input)
			free(g_input);
		free(data->pwd);
		exit(EXIT_SUCCESS);
	}
	return (0);
}

int	parser_semicolon(char *input, int semicolon_pos, t_data *data)
{
	char	*new_input;
	int	space;

	space = 0;
	if (input[semi_pos - 1] == ' ')
		space = 1;
	new_input = ft_strdup(&input[semicolon_pos + 1]);
	input[semicolon_pos - space] = '\0';
	parsercore(input, data);
	if (d->status != 130)
		return (parser(new_input, data));
	else
		free(new_input);
	return (0);
}

int	parser_pipe(char *input, int pipe_pos, t_data *data)
{
	char	*new_input;
	int	space;

	space = 0;
	if (input[pipe_pos - 1] == ' ')
		space = 1;
	new_input = ft_strdup(&input[pipe_pos + 1]);
	input[pipe_pos - space] = '\0';
	return (b_pipe(input, new_input, data));
}

int	check_special(char **input, int *i, t_data *data)
{
	if ((*input)[*i] == '\'')
	{
		(*i)++;
		while ((*input)[*i] != '\'')
			(*i)++;
	}
	else if ((*input)[*i] == '|')
	{
		parser_pipe((*input), *i, data);	//divive input en los dos inputs que necesita el pipe, con lo que hay delante y detrás del pipe
		return (1);
	}
	else if ((*input)[*i] == ';')
	{
		parser_semicolon((*input), *i, data);	//coge hasta el primer ";" y lo manda al parsercore.
		return (1);				//y crea un nuevo input para el resto y lo manda de nuevo a aquí a analizar
	}
	else if ((*input)[*i] == '$')
		parser_variable(input, i, data);	
	(*i)++;
	return (0);
}

int	parser(char *input, t_data *data)
{
	int i;
	int slash_count;

	int = 0;
	g_input = NULL;
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
				if (input[i] == '$' && !(slash_count % 2))
					parser_variable(&input, &i, data);
				if (slash_count && !(slash_count % 2))
					i--;
				i++;
			}
		}
		if (check_special(&input, &i, data))
			return (0);
	]	
	return (parsercore(input, data,0));
}
