#include "../minishell.h"

void	parser_redir_quotes(char *str, int *i, char quote)
{
	int slash_count;

	while (str[*i] != quote)
	{
		slash_count = 0;
		while (str[*i] == '\\' && quote == '"')
		{
			slash_count++;
			(*i)++;
		}
		if (slash_count && !(slash_count % 2))
			(*i)--;
		(*i)++;
	}
}

void	remove_redir_input(char **input, int i, int j)
{
	char *tmp;
	char *new_input;

	tmp = ft_substr(input[0], 0, i);
	new_input = ft_strjoin(tmp, &(input[0][j + 1]));
	free(tmp);
	free(*input);
	*input = new_input;
}

void	redir_to_append(char *str, int i, char **input, t_data *data)
{
	char	*filename;
	int	fd;
	int	j;

	j = i;
	j++;
	if (str[j + 1] == ' ')
		j++;
	filename = get_filename(&(str[j + 1]), &j);
	remove_redir_input(input, i, j);					//substraemos lo analizado para continuar con el parser
	fd = open(filename, O_RDWR | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR); //exactamente igual que redir_to pero utilizando etiqueta O_APPEND al abrir filename
	free(filename);
	if (fd < 0)
	{
		ft_putstr_fd("Error: wrong permissions\n", 2);
		data->status = 1;
		data->redir = 0;
		return ;
	}
	dup2(fd, 1);
	if (data->fd_out != 1)
		close(data->fd_out);
	data->fd_out = fd;
	parser_redir(input, data);
}

void	redir_from(char *str, int i, char **input, t_data *data)
{
	char	*filename;
	int	fd;
	int	j;

	j = i;
	if (str[j + 1] == ' ')
		j++;
	filename = get_filename(&(str[j + 1]), &j);
	remove_redir_input(input, i, j);		//substraemos lo analizado para continuar con el parser
	fd = open(filename, O_RDONLY);			//abrimos sólo en modo lectura
	free(filename);
	if (fd < 0)
	{
		ft_putstr_fd("Error: Wrong file name or wrong permissions\n", 2);
		data->status = 1;
		data->redir = 0;
		return ;
	}
	dup2(fd, 0);					//en vez de leer de stdin leemos del fd
	if (data->fd_in != 0)
		close(data->fd_in);
	data->fd_in = fd;
	parser_redir(input, data);
}
