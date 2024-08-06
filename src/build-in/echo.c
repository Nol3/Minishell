#include "../../include/minishell.h"
bool ft_new_line(char **str)
{
	if (ft_strncmp())
		return (true);
	else
		return (false);
}

void	ft_echo(t_cmd *cmd, char **command)
{

}

int echo(t_data *data, char **cmd)
{
	if (ft_strncmp(cmd[0], "echo", 4) == 0 && cmd[0][4] == '\0')
		return (ft_echo(data->cmd_list, cmd));
	else
		return (0);
}