#include "../minishell.h"

void	select_cmd(char **inputs, t_data *data)
{
	if (!ft_strcmp(inputs[0], "echo"))
		b_echo(inputs);
	else if (!ft_strcmp(inputs[0], "pwd"))
		b_pwd(data);
	else if (!ft_strcmp(inputs[0], "cd"))
		b_cd(inputs, data);
	else if (!ft_strcmp(inputs[0], "env"))
		b_env(data->env);
	else if (!ft_strcmp(inputs[0], "exit"))
		b_exit(inputs, data);
	else if (!ft_strcmp(inputs[0], "export"))
		b_export(inputs, data);
	else if (!ft_strcmp(inputs[0], "unset"))
		b_unset(inputs, data);
	else
	{
		exec(inputs, data);
	}
}

void	free_inputs(char **inputs)
{
	int	i;

	i = 0;
	while (inputs[i])
	{
		free(inputs[i]);
		i++;
	}
	free(inputs);
}

void	close_fds(t_data *data)
{
	if (data->fd_in != 0)
	{
		close(data->fd_in);
		data->fd_in = 0;
	}
	if (data->fd_out != 1)
	{
		close(data->fd_out);
		data->fd_out = 1;
	}
}

int	parser(char *input, t_data *data)
{
	char	*clean_input;	
	char	**inputs;
	int	oldfd[2];
	
	if (check_special(&input, data))		//chequeamos caracteres especiales | ; $	****TO DO****
		return (0);
	if (parser_error(input))			//chequeamos errores sintaxis 			****TO DO****
	{
		free(input);
		return (0);
	}
	oldfd[0] = dup(1);				//copia de stdout en oldfd[0]
	oldfd[1] = dup(0);				//copia de stdin en oldfd[1]
	clean_input = input_cleaner(input);		//limpiamos input				****TO DO****
	parser_redir(&input, data);			//gestionamos redireccionamientos		****TO DO****
	inputs = input_split(clean_input);		//dividimos input		 
	free(clean_input);
	select_cmd(inputs, data);			//seleccionamos comando a ejecutar
	free_inputs(inputs);
	dup2(oldfd[0], 1);				//en vez de escribir en stdout(1) hacemos que escriba en oldfd[0]			
	dup2(oldfd[1], 0);				//en vez de leer de stdin(0) hacemos que lea de oldfd[1]
	close_fds(data);
	close(oldfd[0]);
	close(oldfd[1]);
	return (0);
}
