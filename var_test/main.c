#include "test.h"

int	parser_out(char *new_input)
{
	printf("-------\n\n%s\n\n-------\n", new_input);
	return (1);
}

int	parser_in(char *input, t_data *data)
{
	int	i = 0;

	while (input[i])
	{
		if (input[i] == '$')
			parser_variable(input, i, data);
		i++;
	}
	return (1);
}

int	main(int argc, char **argv, char **envp)
{
	char	buff[1000];
	t_data	data;

	data.env = envp;
	while (1)
	{
		write(1, ">- ", 3);
		bzero(buff, 1000);
		read(0, buff, 1000);
		parser_in(buff, &data);	
	}
	return (0);
}
