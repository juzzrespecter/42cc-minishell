#include "minishell.h"

static int		export_print(t_data *data)
{
	int		i;
	int 	j;
	char	*value;

	i = 0;
	while (data->env[i])
	{
		value = data->env[i];
		j = 0;
		while (value[j] != '=' && value[j] != 0)
			j++;
		write(1, "declare -x ", 11);
		write(1, value, j);
		write(1, "\"", 1);
		write(1, value + j, ft_strlen(value + j));
		write(1, "\"\n", 2);
		i++;
	}
	return (0);
}

int			b_export(char **argv, t_data *data)
{
	int		i;
	int		err_status;
	err_status = 0;
	i = 0;
	if (argv[1] == NULL)
		return (export_print(data));
	while (argv[i] != NULL)
	{
		if (env_parse_id(argv[i]) == 0)
		{
			if (env_add_id(argv[i], data) == -1)
				return (errno + 128);
		}
		else
			err_status = print_error(argv[0], argv[i], "not a valid identifier", 1);
		i++;
	}
	return (err_status);
}
