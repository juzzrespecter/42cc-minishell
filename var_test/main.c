#include "test.h"

int	parser(t_data *data)
{
	int	i = 0;

	while (data->input[i])
	{
		if (data->input[i] == '$')
			parser_variable(data->input, i, data);
		i++;
	}
	printf("%s\n", data->input);
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
		data.input = ft_strdup(buff);
		parser(&data);	
	}
	return (0);
}
