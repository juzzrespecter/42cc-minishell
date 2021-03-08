#include "test.h"

int main(int argc, char **argv, char **envp)
{
	int		buff_size = 1000;
	char	buff[buff_size];
	t_data	data;

	while (1)
	{
		ft_bzero(buff, buff_size);
		read(0, buff, buff_size);
		if (parser_error(buff, &data))
			printf("token err: %s\n", data.err);
	}
	return (0);
}
