#include "../minishell.h"

void	handle_sig(int sig)
{
	if (sig == SIGINT)		//si recibimos señal salida Ctrl-C
	{
		data->status = 130;	//Bash exit code status es 130 para salida con Ctrl-C
		if (g_input)
			ft_putstr_fd("\nDANFER_minishell> ", 2);
		if (g_input)
			free(g_input);
		g_input = ft_strdup("\0");
	}
	else if (sig == SIGQUIT)	//si recibimos señal de salida de teclado Ctrl-\//
		write(2, "\b\b  \b\b", 6);
}

void	sig_init(void)
{
	if (signal(SIGINT, handle_sig) == SIG_ERR) //atrapamos la señal SIGINT con la función signal, y la manejamos con la función handle_sig
		exit(EXIT_FAILURE);		//si da error salimos
	else if (signal(SIGQUIT, handle_sig) == SIG_ERR)//atrapamos la señal SIGQUIT con la función signal, y la manejamos con la función handle_sig
		exit(EXIT_FAILURE);
}

