#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int		redir_parser()
{
	// redir: [n][<,>,>>][word]
}

int		variable_parser()
{
	// no implementado en minishell, solo se usa en export/unset
	// debe tener un '='
	// VAR=[VALUE]
	// VAR -> [0-9A-Za-z_]
	// VALUE ->word_parser()
	// tantoo VAR como VALUE aceptan expansion de $
	// VAR no acepta comillas -> si hay una comilla en VAR la totalidad de la palabra se interpretara como un comando y no como una asignacion de variable
}

char	**variable_expansion(char *var, char **env)
{
	// parse var hasta encontrar { "\"", <blank> }

}

char	**word_expansion(char *word, char **env)
{
	// quita comillas
	// sustituye variables de entorno

	char 	*words_expanded[1000];
	char	**aux_words;
	char	*aux;
	int		expand_vars;	// true or false
	int		copy_literal;	// true or false
	int		i = 0;

	while (word[i])
	{
		//  caso comillas simples
		
		//    si dquote == true, copia literal
		//    else
		//      si squote == true, desactiva squote (cierra comillas simples)
		//      si squote == false, activa squote (abre comillas simples)
		//
		//  caso comillas dobles
		//    si squote == true, copia literal
		//    else
		//      si dquote == true, desactiva squote (cierra comillas simples)
		//      si dquote == false, activa squote (abre comillas simples)
		//      
		//  caso env var
		//     si squote == true, copia literal
		//     else  la variable se expande
			if (word[i] == '$')
			{
				aux_words = variable_expansion(word + i, env);
			}
		
	}
}

char	**cmd_parser(char *input) // en este punto ya no deberia haber ninguna comilla abierta
{
	char	*args[1000];
	char	**arg_expanded;
	int		input_count = 0;
	int		i = 0;

	// ...
	while (input[input_count])
	{
		// if is_redir
		// if word found
		//   input[input_found] = ...
		//
		// if word with comillas found
		// 	 input[input_found] = func_borrar_comillas ...
		//
		// if word with variables de entorno found
		//   arg_expanded = func_expandir_variables
		//   while (arg_expanded[j] != 0)
		//     args[i] = arg_expanded[j]
	}
	args[i] = NULL;
	while (args[i])
	{
		printf("%s\n", args[i]);
		i++;
	}
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	char	buffer[1000];

	read(0, buffer, 1000);
	cmd_parser(buffer, envp);
	return (0);
}



// empty commands:
//   ;  ""  ; --> intenta ejecutar una cadena vacia
//   ;      ; --> error de sitaxis
//   ; $var ; --> con var="", ignora el comando
