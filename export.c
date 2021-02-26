#include "minishell.h"

static int		export_print(char **envp)
{
	int		i;
	int 	j;
	char	*value;

	i = 0;
	while (envp[i])
	{
		value = envp[i];
		j = 0;
		while (value[j] != '=' && value[j] != 0)
			j++;
		write(1, "declare -x ", 11);
		write(1, value, j);
		write(1, "\"", 1);
		write(1, value + j, ft_strlen(value + j));
		write(1, "\"", 1);
		i++;
	}
	return (0);
}

int				export(char **argv, char **envp)
{
	int		i;
	int		i_env;
	int		key_len;

	if (argv[1] == NULL)
		return (export_print);
	i_env = 0;
	while (envp[i_env])
		i_env++;
	i = 1;
	while (argv[i])
	{
		if ((key_len = export_has_value(argv[i])) != 0)
		{
			if ((parse_id(argv[i])) == 0)
			{
				write(2, "bash: export: `", 15);
				write(2, argv[i], key_len);
				write(2, "': not a valid identifier\n", 27);
				return (1);
			}
			if ((envp[i_env] = ft_strtrim(argv[i], ' ') == NULL))
			{
				write(2, "bash: export: ", 14);
				write(2, strerror(errno), ft_strlen(strerror(errno)));
				return (1);
			}
			i_env++;
		}
		i++;
	}
	envp[i_env] = NULL;
	return (0);
}
