#include "../minishell.h"

void	redir_from(char *str, int i, char **input, t_data *data)
{
	char	*filename;
	int	fd;
	int	j;

	j = i;
	if (str[j + 1] == ' ')
		j++;
	filename = get_filename(&(str[j + 1]), &j);
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
	tmp = ft_substr(input[0], 0, i);		//substraemos lo analizado para continuar con el parser
	new_input = ft_strjoin(tmp, &(input[0][j + 1]));
	free(tmp);
	free(*input);
	*input = new_input;
	parser_redir(input, data);
}

void	redir_to_append(char *str, int i, char **input, t_data *data)
{
	char	*filename;
	char 	*tmp;
	char 	*new_input;
	int	fd;
	int	j;

	j = i;
	if (str[j + 1] == ' ')
		j++;
	filename = get_filename(&(str[j + 1]), &j); 				
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
	tmp = ft_substr(input[0], 0, i);	
	new_input = ft_strjoin(tmp, &(input[0][j + 1]));
	free(tmp);
	free(*input);
	*input = new_input;
	parser_redir(input, data);
}

void	fill_filename(char *src, char *dst, int i, int k)
{
	while (src[i] != ' ' && src[i] != '|' && src[i] != ';' && src[i] != '>' &&
			src[i] != '<' && src[i])
	{
		if (src[i] == '\'')
		{
			while (src[++i] != '\'')
				dst[k++] = src[i];
			i++;
		}
		else if (src[i] == '"')
		{
			while (src[++i] != '"')
			{
				if (src[i] == '\\')
					i++;
				dst[k++] = src[i];
			}
			i++;
		}
		else
			dst[k++] = src[i++];
	}
	dst[k] = '\0';
}

char	*get_filename(char *str, int *j)
{
	int	i;
	int	k;
	char	*filename;
	
	i = 0;
	while (str[i] != ' ' && str[i] != '|' && str[i] != ';' && str[i] != '>' && str[i] != '<' && str[i])	
		i++;					//chequeamos longitud del nombre del archivo
	*j += i;
	filename = malloc((i + 1) * sizeof(char));	// creamos var filename con esa longitud
	if (!filename)
		return (NULL);
	i = 0;
	k = 0;
	fill_filename(str, filename, i, k);		//rellenamos la var filename
	return (filename);
}

void	redir_to(char *str, int i, char **input, t_data *data)
{
	char	*filename;
	char 	*tmp;
	char 	*new_input;
	int	fd;
	int	j;

	j = i;
	if (str[j + 1] == ' ')
		j++;
	filename = get_filename(&(str[j + 1]), &j); 				//recogemos el nombre del archivo
	fd = open(filename, O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR); 	//abrimos el archivo y si no exite lo crea
	free(filename);
	if (fd < 0)
	{
		ft_putstr_fd("Error: wrong permissions\n", 2);
		data->status = 1;
		data->redir = 0;
		return ;
	}
	dup2(fd, 1);				//en vez de escribir en stdout escribimos en el fd del archivo abierto o creado
	if (data->fd_out != 1)
		close(data->fd_out);
	data->fd_out = fd;
	tmp = ft_substr(input[0], 0, i);	//substraemos lo analizado y creamos un nuevo input con el resto para llamar de nuevo a parser_redir
	new_input = ft_strjoin(tmp, &(input[0][j + 1]));
	free(tmp);
	free(*input);
	*input = new_input;
	parser_redir(input, data);
}

int	parser_redir(char **input, t_data *data)
{
	int		i;
	char	*str;

	i = -1;
	str = *input;
	while (str[++i])
	{
		if (str[i] == '>' || str[i] == '<')
		{
			if (str[i] == '>' && str[i + 1] != '>')
				redir_to(str, i, input, data);		// > redirecciona stdout hacia un archivo, lo crea si no existe y si existe lo sobreescribe
			else if (str[i] == '>' && str[i + 1] == '>')
				redir_to_append(str, i, input, data);	// >> igual que el anterior pero si existe concatena la salida al final de este
			else if (str[i] == '<' && str[i + 1] != '<')
				redir_from(str, i, input, data);	// < redirecciona stdin desde un archivo, el contenido del archivo es la entrada o input del comando
			return (1);
		}
	}
	return (0);
}
