#include "minishell.h"

static void	sort_env_cmp(char **env_sorted, int pos)
{
	int	cmp_out;
	int	len_env;
	char	*str_aux;

	len_env = ft_strlen(env_sorted[pos]) + 1;
	cmp_out = ft_strncmp(env_sorted[pos], env_sorted[pos + 1], len_env);
	if (cmp_out > 0)
	{
		str_aux = env_sorted[pos];
		env_sorted[pos] = env_sorted[pos + 1];
		env_sorted[pos + 1] = str_aux;
	}
}	

static char	**sort_env(char **env)
{
	char **env_sorted;
	int	env_len;
	int	i;
	int	j;

	env_sorted = copy_env(env);
	env_len = envlen(env_sorted);
	i = 0;
	j = 0;
	while (i < env_len)
	{
		while (env_sorted[j])
		{
			if (env_sorted[j + 1] != NULL)
				sort_env_cmp(env_sorted, j);
			j++;	
		}
		j = 0;
		i++;
	}
	return (env_sorted);
}

static int	export_print(t_data *data)
{
	int		i;
	int		j;
	char	*value;
	char **env_sorted;

	env_sorted = sort_env(data->env);
	i = 0;
	while (env_sorted[i])
	{
		value = env_sorted[i];
		j = 0;
		while (value[j] != '=' && value[j] != 0)
			j++;
		write(1, "declare -x ", 11);
		write(1, value, j);
		write(1, "=\"", 2);
		write(1, value + j + 1, ft_strlen(value + j + 1));
		write(1, "\"\n", 2);
		i++;
	}
	free_env(env_sorted);
	return (0);
}

int	b_export(char **argv, t_data *data)
{
	int		i;
	int		err;

	err = 0;
	i = 1;
	if (argv[1] == NULL)
		return (export_print(data));
	while (argv[i] != NULL)
	{
		if (check_var(argv[i], 1) != 0)
		{
			if (env_add_id(argv[i], data) == -1)
				return (errno + 128);
		}
		else
			err = print_error(argv[0], argv[i], "not a valid identifier", 1);
		i++;
	}
	return (err);
}
