#include "../../include/minishell.h"

void	ft_env(t_data *data)
{
	t_envp_list	*current;

	current = data->envp_list;
	while (current)
	{
		ft_printf("%s=%s\n",
			current->key,
			current->value);
		current = current->next;
	}
}

int	env(t_data *data)
{
	if (data->current_cmd->args[1])
	{
		print_error("env");
		return (1);
	}
	else if (ft_strncmp(data->current_cmd->args[0], "env", 3) == 0
		&& data->current_cmd->args[0][3] == '\0')
		ft_env(data);
	else
	{
		print_error("bad command");
		return (1);
	}
	return (0);
}
