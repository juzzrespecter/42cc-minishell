#include "../minishell.h"

char	*find_next_input(char *str)
{
	char	quote;
	int	slash_count;

	str--;
	while (*(++str))
	{
		if (*str == '"' || *str == '\'')
		{
			quote = *(str++);
			while (*str != quote)
			{
				slash_count = 0;
				while (*str == '\\' && quote == '"' && ++slash_count)
					str++;
				if (slash_count && !(slash_count % 2))
					str--;
				str++;
			}
		}
		if (*str == ' ')
			return (str + 1);
	}
	return (str);
}

void	copy_newsplit(char *src, char *dst, char quote)
{
	while (*src != ' ' && *src)
	{
		if (*src == '\'')
		{
			quote = *(src++);
			while (*src != quote)
				*(dst++) = *(src++);
			src++;
		}
		else if (*src == '"')
		{
			quote = *(src++);
			while (*src != quote)
			{
				if (*src == '\\' && (*(src + 1) == quote ||
					*(src + 1) == '\\' || *(src + 1) == '$'))
					src++;
				*(dst++) = *(src++);
			}
			src++;
		}
		else
			*(dst++) = *(src++);
	}
	*dst = '\0';
}

char	*newsplit(char *src)
{
	int	len;
	char	*dst;
	char	quote;

	quote = 0;
	len = ft_strlen(src);
	dst = malloc((len + 1) * sizeof(char));
	if (!dst)
		exit(EXIT_FAILURE);
	copy_newsplit(src, dst, quote);		//copia dentro de newsplit
	return (dst);
}

size_t	stringcount(char *str)
{
	int	i;
	char	quote;
	int	slash_count;

	i = 1;
	str--;
	while (*(++str))
	{
		if (*str == '"' || *str == '\'')
		{
			quote = *(str++);
			while (*str != quote)
			{
				slash_count = 0;
				while (*str == '\\' && quote == '"' && ++slash_count)
					str++;
				if (slash_count && !(slash_count % 2))
					str--;
				str++;
			}
		}
		if (*str == ' ')
			i++;
	}
	return (i);
}

char	**input_split(char *str)
{
	char	**inputs;
	size_t	count;
	size_t	i;

	count = stringcount(str);	//cuenta el numero strings en la entrada tomando el espacio como separador de tokens y teniendo en cuenta las comillas simples y dobles cogiendo lo hay dentro como un único input
	inputs = malloc((count + 1) * sizeof(char *));
	if (!inputs)
		exit(EXIT_FAILURE);
	i = 0;
	while (i < count)
	{
		inputs[i++] = newsplit(str);	//crea un string y lo rellena hasta el primer espacio o con el contenido dentro de las comillas
		if (i > 0 && !inputs[i - 1])
			return (NULL);
		str = find_next_input(str);	//me devuelve el string comenzando a partir del último espacio encontrado
	}
	inputs[i] = NULL;
	return (inputs);
}
