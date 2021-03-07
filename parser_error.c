#include "minishell.h"
#define WORD 1
#define OP_CTRL 2

// no contar en los errores de sintaxis los tokens de control no implementados en minishell

const char *op_tokens[] {
	";",
	"|",
	"<",
	">",
	">>",
	"\n"
}

// redir: 1<1>1 lanza error en token 1, token 1 es interpretado como file_path en la primera
// redireccion y como [n] en la segunda
// WORD entre dos REDIR_OP, sin separador de espacios, y parseable como fd (es un numero)

static int	is_syntax_error(char *input, int prev_token)
{
	int	i;

	i = 0;
	// control tokens {; | newline} -> error si no vienen precedidos por WORD
	// redirection tokens {> < >>} -> error si vienen precedidos por REDIR_OP

	// prov, pilla token de la lista de tokens reconocida
	// comprueba condiciones de error
	
	// if op_token == redir_token
	// call redir_syntax_error

	/*while (input[i] && i < 2 && is_ctrl_op(input[i]))
	{
		op_token[i] = input[i];
		i++;
	}
	if (prev_token == OP_CTRL || i == 2)
		return (1);
	ft_bzero(op_token, 3); */
	return (0);
}

int			parser_error(char *input, t_data *data)
{
	int		i;
	int		prev_token;
	int		quote_ctrl[2];


	i = 0;
	quote_ctrl[0] = 0;
	quote_ctrl[1] = 0;
	while (input[i])
	{
		is_quote(input[i], quote_ctrl)
		if (is_word(input[i]) || (quote_ctrl[0] || quote_crtl[1]))
			prev_token = WORD;
		if (is_ctrl_op(input[i] && !(quote_ctrl[0] || quote_ctrl[1])))
		{
			if (is_syntax_error(input + i, prev_token))
			{
				print_error(data->sh_name, "syntax error near unexpected token", op_token);
				return (1);
			}
			prev_token = OP_CTRL;
		}
		i++;
	}
	return (0);
}
