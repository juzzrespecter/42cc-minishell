#include "minishell.h"

static int		export_print(t_data *data, int fd_out)
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
		write(fd_out, "declare -x ", 11);
		write(fd_out, value, j);
		write(fd_out, "\"", 1);
		write(fd_out, value + j, ft_strlen(value + j));
		write(fd_out, "\"\n", 2);
		i++;
	}
	return (0);
}

/*static void		export_print_error(char *id, int fd_err)
{
	write(fd_err, "bash: export: '", 15);
	write(fd_err, id, ft_strlen(id));
	write(fd_err, "': not a valid identifier\n", 26);
}*/

int				export(t_cmd *cmd, t_data *data)
{
	int		i;
	int		err_status;

	err_status = 0;
	i = 0;
	if (cmd->argv[1] == NULL)
		return (export_print(data, cmd->fd_out));
	while (cmd->argv[i] != NULL)
	{
		if (env_parse_id(cmd->argv[i]) == 0)
		{
			if (env_add_id(id, data) == -1)
				return (errno + 128);
		}
		else
		{
			err_status = 1;
			export_print_error(cmd->argv[i], cmd->fd_err);
		}
		i++;
	}
	return (err_status);
}
