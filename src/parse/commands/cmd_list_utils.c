#include "../../../include/minishell.h"

int	is_cmd_empty(t_cmd_list *list)
{
	return (list->first == NULL);
}

t_cmd_list	*init_cmd_list(t_cmd_list *list)
{
	list = (t_cmd_list *)ft_calloc(sizeof(t_cmd_list), 1);
	if (!list)
		return (NULL);
	return (list);
}

t_cmd	*new_cmd(char **args, t_redir_list *redir_list,
				enum e_built_in built_in)
{
	t_cmd	*new;

	new = (t_cmd *)ft_calloc(sizeof(t_cmd), 1);
	if (!new)
		return (NULL);
	new->args = args;
	new->redir_list = redir_list;
	new->built_in = built_in;
	return (new);
}

void	add_cmd_last(t_cmd_list *list, t_cmd *new)
{
	if (is_cmd_empty(list))
		list->first = new;
	else
	{
		list->last->next = new;
		new->prev = list->last;
	}
	list->last = new;
	list->size++;
}

void	free_cmd_list(t_cmd_list *list)
{
	t_cmd	*tmp;

	if (!list)
		return ;
	tmp = list->first;
	while (tmp)
	{
		free_strs(tmp->args);
		free_strs(tmp->choosen_path);
		free_redir_list(tmp->redir_list);
		free(tmp);
		tmp = tmp->next;
	}
	free(list);
}
