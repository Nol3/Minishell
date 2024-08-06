#include "../../../include/minishell.h"

t_token	*add_command_to_list(t_cmd_list *cmd_list, t_token *current)
{
	(void) cmd_list;
	return (current);
}

int	add_commands_from_input(t_data *data)
{
	t_token	*current;
	t_token	*updated;

	if (is_empty(data->token_list))
		return (0);
	current = data->token_list->first;
	data->cmd_list = (t_cmd_list *)ft_calloc(sizeof(t_cmd_list), 1);
	if (!data->cmd_list)
		return (0);
	while (current)
	{
		updated = add_command_to_list(data->cmd_list, current);
		if (updated == current)
			return (0);
		current = updated;
	}
	return (1);
}
