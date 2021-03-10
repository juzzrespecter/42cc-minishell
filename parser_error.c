#include "test.h"
# define PREV_TOKEN 0
# define WORD 1 
# define CTRL 2
# define REDIR 3

/* condiciones de error para words:
 *      word es a la vez used_as_fd && used_as_filepath
 * 	        used_as_fd 			== is_digit && next_char == redir
 *          used_as_filepath 	== is_word && prev_token == redir
 *
 * flags
 *      flags[0] == prev_token:		{ 0: word, 1: ctrl, 2: redir }
 *      flags[1] == is_quoted:		{ 0: no, 1: single_quotes, 2: double_quotes, 3: escaped }
 */

static int	is_fd(char *input)
{
	int	i;

	i = 0;
	while (input[i] && !ft_strrchr(";|\t <>", input[i]))
	{
		if (!ft_isdigit(input[i]))
			return (0);
		i++;
	}
	return (i);
}

static int	parser_word(char *input, int token_len, int flags[2], t_data *data)
{
	int	next_char;
	int	fd_true;

	next_char = 1 * (input[token_len] == '>' || input[token_len] == '<');
	fd_true = is_fd(input);
	if ((next_char && fd_true && (flags[PREV_TOKEN] == REDIR)))
	{
		data->err = ft_substr(input, 0, token_len);
		return (0);
	}
	flags[PREV_TOKEN] = WORD;
	return (1);
}

static int	parser_ctrl(char *input, int token_len, int flags[2], t_data *data)
{
	int	token;

	token = CTRL;
	if (input[0] == '>' || input[0] == '<')
		token = REDIR;
	if ((token == REDIR && flags[PREV_TOKEN] == REDIR) \
			|| (token == CTRL && flags[PREV_TOKEN] != WORD))
	{
		data->err = ft_substr(input, 0, token_len);
		return (0);
	}
	flags[PREV_TOKEN] = token;
	return (1);
}

/* parser error: recibe el input y comprueba posibles errores de sintaxis. 
 * devuelve (0) en caso de exito y (258) (codigo de error) en caso de encontrar un error.
 *   
 *   parser_word(); controla posibles errores en un token WORD
 *   en caso de que el shell pueda interpretar el mismo token como un descriptor de fichero
 *   en una redireccion y un path a un fichero en otra redireccion ( p. ej: > 1> /path/to/file.txt )
 *   retorna (0) como error.
 *
 *   parser_ctrl(); controla errores en un token CTRL ( operador de control, { ;, <, >, >>, <newline>, | } )
 *   en caso de que encuentre una redireccion (REDIR) sin un WORD que interprete como fichero, o un token
 *   de control de comandos ( ; y | ) precedidos de un comando vacio ( sin argumentos ni redirecciones), 
 *   retorna (0) como error.
 */

int			parser_error(char *input, t_data *data)
{
	int	flags[2];
	int	i;
	int	token_len;

	i = 0;
	ft_bzero(flags, sizeof(int) * 2);
	while (input[i])
	{
		if ((token_len = is_word(input + i, flags)))
		{
			if (!(parser_word(input + i, token_len, flags, data)))
				return (258);
			i += token_len;
		}
		if ((token_len = is_ctrl_op(input + i)))
		{
			if (!(parser_ctrl(input + i, token_len, flags, data)))
				return (258);
			i += token_len;
		}
		i += is_blank(input[i]);
	}
	return (0);
}
 
