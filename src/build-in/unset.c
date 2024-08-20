#include "../../include/minishell.h"

static void	free_envp_list(t_envp_list *list)
{
	t_envp_list	*current;
	t_envp_list	*to_delete;

	current = list;
	to_delete = NULL;
	while (current)
	{
		if (current->key)
			free(current->key);
		if (current->value)
			free(current->value);
		to_delete = current;
		current = current->next;
		free(to_delete);
	}
}

static t_envp_list	*unset_variable(t_envp_list *current, char *key)
{
	t_envp_list	*first;
	t_envp_list	*previous;

	first = current;
	previous = NULL;
	while (current)
	{
		if (strs_are_equal(key, current->key))
		{
			if (!previous)
				first = current->next;
			if (previous)
				previous->next = current->next;
			current->next = NULL;
			free_envp_list(current);
			return (first);
		}
		previous = current;
		current = current->next;
	}
	return (first);
}

int	ft_unset(t_data *data)
{
	int			i;
	char		*key;

	i = 0;
	while (data->current_cmd->args[++i])
	{
		key = data->current_cmd->args[i];
		if (key)
			data->envp_list = unset_variable(data->envp_list, key);
	}
	data->status = 0;
	update_envp(data);
	return (EXIT_SUCCESS);
}
