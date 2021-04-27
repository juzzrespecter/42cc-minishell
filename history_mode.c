#include "minishell.h"

int		is_print(char c)
{
	if ((c >= 32 && c <= 126) || c == 9)
		return (1);
	return (0);
}

void	history_mode(t_data *data)
{
	char	buffer[4];
	int		i;

	while (1)
	{
		tputs(data->termc->keystart, 1, putchar_2);
		ft_memset(buffer, 0, 4);
		i = read(0, buffer, 3);
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

int		set_history_mode(t_data *data)
{
	char	*termtype;
	int i;

	if (isatty(STDIN_FILENO))
	{
		termtype = getenv("TERM");
		if (!termtype)
		{
			write(STDOUT_FILENO, "TERM config not set, exiting...\n", 34);
			free_data(data, EXIT_FAILURE);
		}
		i = tgetent(0, termtype);
		if (i != 1)
			free_data(data, EXIT_FAILURE);
		if (!(data->termc = malloc(sizeof(t_termc))))
			free_data(data, EXIT_FAILURE);
		ft_memset((data->termc), 0, sizeof(t_termc));
		//data->in_terminal = 1;
		bzero(&data->modified, sizeof(t_termios));
		tcgetattr(0, &data->origin);
		tcgetattr(0, &data->modified);
		data->modified.c_iflag &= ~(IGNBRK | BRKINT | ICRNL | INLCR | PARMRK | INPCK | ISTRIP | IXON);
		data->modified.c_lflag &= ~(ICANON | ECHO);
		//data->modified.c_cc[VMIN] = 1;
		//data->modified.c_cc[VTIME] = 0;
		if (!(data->termc->keystart = tgetstr("ks", 0))
				|| !(data->termc->clear_line = tgetstr("dl", 0))
				|| !(data->termc->up_key = tgetstr("ku", 0))
				|| !(data->termc->down_key = tgetstr("kd", 0))
				|| !(data->termc->cariage_return = tgetstr("cr", 0))
				|| !(data->termc->keyend = tgetstr("ke", 0)))
			free_data(data, EXIT_FAILURE);
		//data->in_terminal = 1;
	}
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &data->modified);
	return (1);
}
