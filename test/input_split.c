#include "minishell.h"

/*	separar words sin parsear (ni expansion, ni eliminar comillas)
 *
 *	expandir cada word por separado, borrando las comillas que no se encuentren dentro de la variable expandida
 *	si, resultado de la expansion, se encuentra un nuevo argumento, se copia la lista y se le mete a la ultima entrada
 */

/*	primero word_argvs
 *	luego montar lista expandiendo los word_argvs
 *	despues montar true_argv
 */
/*
int		split_crudo_len(char *input)
{
	int	token_len;
	int	len;
	int	i;

	i = 0;
	while (input[i])
	{
		token_len = is_word(input + i);
		if (token_len > 0)
			len++;
		i += token_len;
		i += is_blank(input[i]);
	}
	len++;
	return (len);
}

char	**split_crudo(char *input)
{
	char	**false_argv;
	int	token_len;
	int	count;
	int	i;

	i = 0;
	false_argv = (char **)malloc(sizeof(char *) * (split_crudo_len(input)));
	count = 0;
	while (input[i])
	{
		token_len = is_word(input + i);
		if (token_len > 0)
		{
			false_argv[count] = ft_substr(input, i, token_len);
			count++;
		}
		i += token_len;
		i += is_blank(input[i]);
	}
	false_argv[count] = NULL;
	return (false_argv);
}

t_list	*monta_lista(char **false_argv, t_data *data)
{
	t_list	*word;
	t_list	*word_list_head;
	int		i;
	int		quote_ctrl;
	int		j;
	int		var_len; // 0 == no se esta parseando variable, 1 == si lo esta haciendo
	int		word_len;
	int		k;	// control de longitud de la variable

	word_list_head = NULL;
	i = 0;
	j = 0;
	// hay que borrar las comillas cuando se guarden las palabras en la list
	// (checkea expand_and_control en el primer msh)
	while (false_argv[i])
	{
		word_len = 0;
		while (false_argv[i][j])
		{
			while (is_blank(false_argv[i][j]))
				j++;
			if (quote_ctrl != is_quote(src[i], quote_ctrl) && var == 0)
			{
				quote_ctrl = is_quote(false_argv[i][j]);
				j++;
			}
			if (false_argv[i][j] == '$' && quote_ctrl % 2 == 0)
			{
				// expand variable: { old word -> len, new word }
				var_len = parser_variable(&false_argv[i], j, data);
				// mientras no se recorra la longitud total de la variable { len }, la palabra se parseara
				// con las normas de una variable { los caracteres son o espacios o parte de una palabra } 
				// if < blank >;
				// 		lo que tengamos == new word,
				// 		continua
			}
			
			if (var_len > 0)
				var_len--;
			j++;
		}
	}
}

char	**input_split(char *input, t_data *data)
{
	char	**false_argv;
	char	**true_argv;
	t_list	*word_list;

	word_list_head = NULL;
	false_argv = split_crudo(input);
	word_list = monta_lista(false_argv, data);
	true_argv = copia_contents(word_list);
	return (true_argv);
}
*/
int		copy_literal_len(char *str, int quote)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (str[i])
	{
		if (str[i] == '"' || (ft_strchr("\\$\'<>", str[i]) && quote))
			len += 2;
		else
			len++;
		i++;
	}
	len++;
	return (len);
}

char	*copy_literal(char *str, int quote)
{
	char	*value;
	int		i;
	int		j;

	i = 0;
	j = 0;
	value = malloc(sizeof(char) * copy_literal_len(str));
	if (!value)
		return (NULL);
	while (str[i])
	{
		if (str[i] == '"' || (ft_strchr("\\$\'<>", str[i]) && quote))
		{
			value[j] = '\\';
			j++;
			value[j] = str[i];
		}
		else
			value[j] = str[i];
		i++;
		j++;
	}
	value[j] = '\0';
	return (value);
}

char			*expand_variables(char *input, t_data *data)
{
	char	*input_aux;
	int		i;
	int		var_out;
	int		quote_ctrl;

	i = 0;
	quote_ctrl = 0;
	while (input[i])
	{
		quote_ctrl = is_quote(input[i], quote_ctrl);
		if (input[i] == '$' && ((quote_ctrl % 2) == 0))
		{
			input_aux = input;
			var_out = parser_variable(&input, i, data);
			if (var_out == -1)
				return (NULL);
			i += var_out;
		}
		i++;
	}
	return (input);
}

int		input_split_size(char *input)
{
	int		quote_ctrl;
	int		size;
	int		i;

	size = 0;
	while (input[i])
	{
		while (input[i] && is_blank(input[i]))
			i++;
		while (input[i] && !is_blank(input[i]) && quote_ctrl == 0)
		{
			quote_ctrl = is_quote(input[i], quote_ctrl);

		}
	}
}

char **input_split(char *input, t_data *data)
{
	char	**argv;
	int		word_len;
	int		size;
	int		i;
	
	input = expand_variables(input, data);
	size = input_split_size(input);
	while (input[i])
	{
		

	}
}
