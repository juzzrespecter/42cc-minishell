#include "../minishell.h"

void	make_filename(char *src, char *dst, int i, int k)
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

int	get_name_len(char *str)
{
	int i;

	i = 0;
	while (str[i] != ' ' && str[i] != '|' && str[i] != ';' && str[i] != '>' &&
			str[i] != '<' && str[i])
	{
		if (str[i] == '\'')
		{
			while (str[++i] != '\'')
				;
			i++;
		}
		else if (str[i] == '"')
		{
			while (str[++i] != '"')
			{
				if (str[i] == '\\')
					i++;
			}
			i++;
		}
		else
			i++;
	}
	return (i);
}

char	*get_filename(char *str, int *j)
{
	int	i;
	int	k;
	char	*filename;
	
	i = get_name_len(str);				//chequeamos longitud del nombre del archivo
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
	int	fd;
	int	j;

	j = i;
	if (str[j + 1] == ' ')
		j++;
	filename = get_filename(&(str[j + 1]), &j);				//recogemos el nombre del archivo
	remove_redir_input(input, i, j);					//substraemos lo analizado para continuar con el parser
	fd = open(filename, O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);	//abrimos el archivo y si no exite lo crea
	free(filename);
	if (fd < 0)
	{
		ft_putstr_fd("Error: wrong permissions\n", 2);
		data->status = 1;
		data->redir = 0;
		return ;
	}
	dup2(fd, 1);			//en vez de escribir en stdout escribimos en el fd del archivo abierto o creado
	if (data->fd_out != 1)
		close(data->fd_out);
	data->fd_out = fd;
	parser_redir(input, data);
}

int	parser_redir(char **input, t_data *data)
{
	int	i;
	char	*str;
	char	quote;

	i = -1;
	str = *input;
	while (str[++i])
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			quote = str[i];
			i++;
			parser_redir_quotes(str, &i, quote);
		}
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
		if (str[(i)] == '\\')
			i++;
	}
	return (0);
}
