#include "../../include/minishell.h"

void	ft_env(t_data *data)
{
	t_envp_list *current;

	current = data->envp_list;
	while (current)
	{
		ft_putstr_fd(current->key, STDOUT);
		ft_putchar_fd('=', STDOUT);
		ft_putstr_fd(current->value, STDOUT);
		ft_putchar_fd('\n', STDOUT);
		current = current->next;
	}
	data->status = 0;
}

int env(t_data *data)
{
	char **cmd;

	cmd = data->current_cmd->args;
	if (cmd[1])
	{
		print_error("env");
		return (1);
	}
	else if (ft_strncmp(cmd[0], "env", 3) == 0 && cmd[0][3] == '\0')
		ft_env(data);
	else
	{
		print_error("bad command");
		return (1);
	}
	return (0);
}
