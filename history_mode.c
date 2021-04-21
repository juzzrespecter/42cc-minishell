#include "minishell.h"

int		is_print(char c)
{
	if ((c >= 32 && c <= 126) || c == 9)
		return (1);
	return (0);
}

void	history_mode(t_data *data, char **holder)
{
	char	buffer[4];
	int		i;

	tputs(data->termc->keystart, 1, putchar_2);
	while (1)
	{
		ft_memset(buffer, 0, 4);
		tcsetattr(0, TCSANOW, &data->modified);
		i = read(0, &buffer, 3);
		if (set_sig(holder))
			break;
		if (!ft_strcmp(buffer, data->termc->up_key))
			history_up(holder, data);
		else if (!ft_strcmp(data->termc->down_key, buffer))
			history_down(holder, data);
		else if (buffer[0] == '\x04')
			end_of_file(data, *holder);
		else if (buffer[0] == 127)
		{
			delete_char(holder, data);
			continue;
		}
		else if (is_print(buffer[0]) && buffer[1] == '\0')
			append_to_holder(buffer, holder, data);
		else if (buffer[0] == '\n' || buffer[0] == '\r')
		{
			return_input(data, *holder);
			break;
		}
	}
}

int		set_history_mode(t_data *data)
{
	char	*termtype;
	int i;

	if(isatty(0))
	{
		termtype = getenv("TERM");
		// if (!termtype)
		// 	exit(1);
		i = tgetent(0, termtype);
		if (i != 1)
			return (0);
		if (!(data->termc = malloc(sizeof(t_termc))))
			return (0);
		ft_memset((data->termc), 0, sizeof(t_termc));
		data->in_terminal = 1;
		tcgetattr(0, &data->origin);
		tcgetattr(0, &data->modified);
		data->modified.c_lflag &= ~(ICANON);
		data->modified.c_lflag &= ~(ECHO);
		data->modified.c_cc[VMIN] = 0;
		data->modified.c_cc[VTIME] = 0;
		if (!(data->termc->keystart = tgetstr("ks", 0))
			|| !(data->termc->clear_line = tgetstr("dl", 0))
			|| !(data->termc->up_key = tgetstr("ku", 0))
			|| !(data->termc->down_key = tgetstr("kd", 0))
			|| !(data->termc->cariage_return = tgetstr("cr", 0))
			|| !(data->termc->keyend = tgetstr("ke", 0)))
			return (0);
		data->in_terminal = 1;
	}
	return (1);
}