#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

//  func redir
//    parsea las redirecciones
//    las divide en int fd y path
//    fd = open(path, {opciones que dependen de { <, >, >> }
//    como devuelve todos los redireccionamientos??
//      { caso -> cmd1 >file1 >file2 5>file3 <file4 12>file5 }
//      tiene que abrir todos los ficheros y devolver todos los fd para cerrarlos antes de ejecutar el comando

int	pipeline(char *input1, char *input2, int fd_read, t_data *data)
{
	int		fd_pipe[2];
	int		exec_out;

	if (pipe(fd_pipe) == -1)
	{
		if (prev_fd_in != -1)
			close(prev_fd_in);
		return (errno);
	}
	if ((exec_out = exec_cmd(input1, fd_read, fd_pipe[1], data)) == -1)	
	{


}

// func pipalinea:
// encuentra pipa
// fork -> hijo llama a pipalinea, padre espera waitpid(proceso pipa)
// en proceso pipa(input1, input2, read_fd, data){ ---> primera entrada, read_fd = -1
// monta pipa (read_fd', write_fd)
// llama a exec_cmd(input1, read_fd, write_fd, data)
// parsea input2, si encuentra { | }, 
//   input1 = input2 hasta |, input2 = input2'
//   pipalinea(input1', input2', read_fd', data)
// condicion de salida: encuentra { ; , <nl> }


int	parser_input(char *input, t_data *data)
{
	// check syntax error y devuelve a main if true
	//
	// parsea hasta encontrar op ctrl { ; | /n }
	//   ; || /n --> exec_cmd(input, -1, -1, data)
	//   | --> pipeline(input, input + i, -1 , data)
	while (!is_op_ctrl(input[i]))
		i++;
	if (input[i] == '|')
	{
		pipeline(input, input + i, -1, data);
		i = move_until_next_command(input)	// { ; o <nl> }
	}
	if (input[i] == ';')
	{
		exec_cmd(input, data);
		i = move_until_next_command(input);
	}
	return (data->exit_value);
}


// [read] -> [parser_input] -> [check_syntax_error] -> [error] -> to main...
//                                     ---------------> [ok] -> [parse_until_op_ctrl] (loop cmd)
//                                     |                        /        |        \
//                                     |                      /          |          \
//                                     |                 [ <pipe> ]   [  ;  ]      [ <newline> ]
//                                     |                     |           |               |
//                                     |                   fork()     [exec_cmd]       to main...
//                                     |                     |           | 
//                                     |                     |           |
//                                     |                     |           |
//                                     |              (padre): waitpid   |
//                                     |            (hijo): [pipeline]   |
//                                     |                    |            |
//                                     -------------------------------- --
//
