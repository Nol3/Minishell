#include "../../include/minishell.h"
bool ft_new_line(char **str)
{
	if (ft_strncmp(str[1], "-n", 2) == 0 && str[1][2] == '\0')
		return (true);
	else
		return (false);
}

int	ft_echo(char **command)
{
	int i;

	i = 0;
	if (command[1] == NULL)
	{
		write(1, "\n", 1);
		return (0);
	}
	if (ft_strncmp(command[i], "-n", 2) == 0 && !command[i + 1])
		return (0);
	if (ft_strncmp(command[i], "-n", 2) == 0 && command[i][2] == '\0')
		i++;
	while (command[i])
	{
		ft_putstr_fd(command[i], 1);
		i++;
	}
	if (ft_new_line(command) == false)
		write(1, "\n", 1);
	return (0);
}

int echo(char **cmd)
{
	if (ft_strncmp(cmd[0], "echo", 4) == 0 && cmd[0][4] == '\0')
		return (ft_echo(cmd));
	else
		return (0);
}
