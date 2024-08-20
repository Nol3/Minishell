#include "../../include/minishell.h"

static bool	ft_new_line(char **str)
{
	if (ft_strncmp(str[1], "-n", 2) == 0 && str[1][2] == '\0')
		return (true);
	else
		return (false);
}

static int	ft_echo(t_data *data)
{
	int		i;

	i = 1;
	if (!data->current_cmd->args[1])
	{
		ft_putstr_fd("\n", data->current_cmd->fd_out);
		return (EXIT_SUCCESS);
	}
	if (ft_strncmp(data->current_cmd->args[i], "-n", 2) == 0 && !data->current_cmd->args[i + 1])
		return (EXIT_SUCCESS);
	while (ft_strncmp(data->current_cmd->args[i], "-n", 2) == 0 && data->current_cmd->args[i][2] == '\0')
		i++;
	while (data->current_cmd->args[i])
	{
		ft_putstr_fd(data->current_cmd->args[i], data->current_cmd->fd_out);
		i++;
	}
	if (ft_new_line(data->current_cmd->args) == false)
		write(data->current_cmd->fd_out, "\n", 1);
	return (EXIT_SUCCESS);
}

int	echo(t_data *data)
{
	if (ft_strncmp(data->current_cmd->args[0], "echo", 4) == 0
		&& data->current_cmd->args[0][4] == '\0')
	{
		return (ft_echo(data));
	}
	else
		return (EXIT_SUCCESS);
}
