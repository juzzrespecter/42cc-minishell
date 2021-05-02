#include "minishell.h"

int	is_print(char c)
{
	if ((c >= 32 && c <= 126) || c == 9)
		return (1);
	return (0);
}

void	history_mode(t_data *data)
{
	char	buffer[4];

	while (1)
	{
		tputs(data->termc->keystart, 1, putchar_2);
		ft_memset(buffer, 0, 4);
		read(0, buffer, 3);
		if (set_sig(data))
			return ;
		if (!ft_strcmp(buffer, data->termc->up_key))
			history_up(data);
		else if (!ft_strcmp(data->termc->down_key, buffer))
			history_down(data);
		else if (buffer[0] == '\x04')
			end_of_file(data);
		else if (buffer[0] == 127)
			delete_char(data);
		else if (is_print(buffer[0]) && buffer[1] == '\0')
			append_to_holder(buffer, data);
		else if (buffer[0] == '\n' || buffer[0] == '\r')
		{
			return_input(data);
			return ;
		}
	}
}

void	set_termcaps(t_data *data)
{
	data->termc->keystart = tgetstr("ks", 0);
	data->termc->clear_line = tgetstr("dl", 0);
	data->termc->up_key = tgetstr("ku", 0);
	data->termc->down_key = tgetstr("kd", 0);
	data->termc->cariage_return = tgetstr("cr", 0);
	data->termc->keyend = tgetstr("ke", 0);
	if (!data->termc->keystart
		|| !data->termc->clear_line
		|| !data->termc->up_key
		|| !data->termc->down_key
		|| !data->termc->cariage_return
		|| !data->termc->keyend)
		free_data(data, EXIT_FAILURE);
}

int	set_history_mode(t_data *data)
{
	char	*termtype;
	int		i;

	if (isatty(STDIN_FILENO))
	{
		termtype = getenv("TERM");
		if (!termtype)
		{
			write(STDOUT_FILENO, "TERM config not set, exiting...\n", 34);
			free_data(data, EXIT_FAILURE);
		}
		i = tgetent(0, termtype);
		data->termc = ft_calloc(1, sizeof(t_termc));
		if (i != 1 || !data->termc)
			free_data(data, EXIT_FAILURE);
		bzero(&data->modified, sizeof(struct termios));
		tcgetattr(0, &data->origin);
		tcgetattr(0, &data->modified);
		data->modified.c_iflag &= ~(IGNBRK | BRKINT | ICRNL
				| INLCR | PARMRK | INPCK | ISTRIP | IXON);
		data->modified.c_lflag &= ~(ICANON | ECHO);
		set_termcaps(data);
	}
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &data->modified);
	return (1);
}
