#include "minishell.h"

int	janitor(char **argv, t_data *data, int err_code)
{
	int	i;
	int	stat;

	i = 0;
	stat = err_code;
	if (argv != NULL)
	{
		if (err_code == 127)
			stat = print_error(argv[0], NULL, "command not found", err_code);
		if (err_code == 2)
			stat = print_error(argv[0], NULL, strerror(errno), 127);
		if (err_code == 13)
			stat = print_error(argv[0], NULL, strerror(errno), 126);
		if (err_code != 0 && err_code != 2 && err_code != 13 && err_code != 127)
			stat = print_error(argv[0], NULL, strerror(errno), errno + 128);
		free_inputs(argv);
	}
	data->status = stat;
	free_env(data->env);
	return (stat);
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

int	print_error(char *cmd, char *arg, char *err_msg, int exit_code)
{
	write(2, "minishell: ", 11);
	if (cmd != NULL)
	{
		write(2, cmd, ft_strlen(cmd));
		write(2, ": ", 2);
	}
	if (arg != NULL)
	{
		write(2, arg, ft_strlen(arg));
		write(2, ": ", 2);
	}
	write(2, err_msg, ft_strlen((err_msg)));
	write(2, "\n", 1);
	return (exit_code);
}

int	parser_err_msg(char *token)
{
	char	*err_msg;
	char	*aux_str;

	if (token == NULL)
		return (print_error(NULL, NULL, strerror(errno), errno + 128));
	err_msg = ft_strjoin("syntax error near unexpected token `", token);
	free(token);
	if (err_msg == NULL)
		return (print_error(NULL, NULL, strerror(errno), errno + 128));
	aux_str = err_msg;
	err_msg = ft_strjoin(err_msg, "\'");
	free(aux_str);
	if (err_msg == NULL)
		return (print_error(NULL, NULL, strerror(errno), errno + 128));
	g_data.status = print_error(NULL, NULL, err_msg, 258);
	free(err_msg);
	return (258);
}
