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

static t_envp_list	*get_envp_list_node(char *str)
{
	t_envp_list	*new;
	char		*delimiter;

	new = (t_envp_list *)malloc(sizeof(t_envp_list));
	if (!new)
		return (NULL);
	delimiter = ft_strchr(str, '=');
	if (!delimiter)
		return (free(new), NULL);
	new->key = ft_substr(str, 0, delimiter - str);
	if (!new->key)
		return (free(new), NULL);
	if (!ft_strlen(new->key))
		return (free(new->key), free(new),
			print_error("Key not found"), NULL);
	new->value = ft_strdup(delimiter + 1);
	if (!new->value)
		return (free(new->key), free(new), NULL);
	new->next = NULL;
	return (new);
}

static t_envp_list	*export_variable(t_envp_list *current, t_envp_list *new)
{
	t_envp_list	*first;
	t_envp_list	*previous;

	first = current;
	previous = NULL;
	while (current)
	{
		if (strs_are_equal(new->key, current->key))
		{
			free(current->value);
			current->value = ft_strdup(new->value);
			free_envp_list(new);
			return (first);
		}
		previous = current;
		current = current->next;
	}
	if (previous)
		previous->next = new;
	else
		first = new;
	return (first);
}

int	ft_export(t_data *data)
{
	int			i;
	t_envp_list	*new;

	i = 0;
	while (data->current_cmd->args[++i])
	{
		new = get_envp_list_node(data->current_cmd->args[i]);
		if (new)
			data->envp_list = export_variable(data->envp_list, new);
	}
	data->status = 0;
	return (EXIT_SUCCESS);
}
