#include "../../include/minishell.h"

bool	ft_new_line(char **str)
{
	if (ft_strncmp(str[1], "-n", 2) == 0 && str[1][2] == '\0')
		return (true);
	else
		return (false);
}

int	ft_echo(char **command)
{
	int	i;

	i = 1;
	if (command[i] == NULL)
	{
		ft_putstr_fd("\n", 1);
		return (0);
	return (EXIT_SUCCESS);
		ft_putstr_fd(command[i], 1);
		if (command[i++])
			ft_putstr_fd(" ", 1);
	}
	if (ft_new_line(command) == true)
		ft_putstr_fd("\n", 1);
	return (EXIT_SUCCESS);
}

int	echo(t_data *data)
{
	if (ft_strncmp(data->current_cmd->args[0], "echo", 4) == 0
		&& data->current_cmd->args[0][4] == '\0')
	{
		return (ft_echo(data->current_cmd->args));
	}
	else
		return (EXIT_SUCCESS);
}
