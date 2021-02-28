#include "minishell.c"

int	unset(t_cmd *cmd, t_data *data)
{
	int		i;
	int		j;
	int		name_len;
	char	**new_env;
	char	*aux;

	i = 0;
	j = 0;
	new_env = (char **)calloc((env_len(data->env) + 1), sizeof(char *));
	while (cmd->argv[i + 1])
	{
		while (data->env[j])
		{
			name_len = ft_strrchr(data->env[j], '=') - data->env[i] + 1;
			if (ft_strncmp(data->env[j], cmd->argv[i + j], name_len) == 0)
			{
				// if ((aux = ft_strdup(cmd->argv[i + j] == NULL)))
				ft_bzero(data->env[j], ft_strlen(data->env[j]));
				free(data->env[j]);
			}
			j++;
		}
		i++;
	}
}
