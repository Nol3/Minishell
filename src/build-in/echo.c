#include "../../include/minishell.h"

void	ft_echo(t_data data)
{
	int		i;
	int		n_flag;

	i = 1;
	n_flag = 0;
	if (data->cmd_list->argv[i] && !ft_strcmp(data->cmd_list->argv[i], "-n"))
	{
		n_flag = 1;
		i++;
	}
	while (data->cmd_list->argv[i])
	{
		ft_putstr_fd(data->cmd_list->argv[i], STDOUT);
		if (data->cmd_list->argv[i + 1])
			ft_putchar_fd(' ', STDOUT);
		i++;
	}
	if (!n_flag)
		ft_putchar_fd('\n', STDOUT);
	data->status = 0;
}
