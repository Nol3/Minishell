#include "../../../include/minishell.h"

int	is_empty(t_token_list *list)
{
	return (list->first == NULL);
}

t_token_list	*init_list(t_token_list *list)
{
	list = (t_token_list *)ft_calloc(sizeof(t_token_list), 1);
	if (!list)
		return (NULL);
	return (list);
}

t_token	*new_token(char *content, int len,
						enum e_token_type type, enum e_token_state state)
{
	t_token	*new;
	char	*copy;

	new = (t_token *)ft_calloc(sizeof(t_token), 1);
	if (!new)
		return (NULL);
	copy = ft_strndup(content, len);
	if (!copy)
		return (free(new), NULL);
	new->content = copy;
	new->len = len;
	new->type = type;
	new->state = state;
	return (new);
}

void	add_token_last(t_token_list *list, t_token *new)
{
	if (is_empty(list))
		list->first = new;
	else
	{
		list->last->next = new;
		new->prev = list->last;
	}
	list->last = new;
	list->size++;
}

void	free_list(t_token_list *list)
{
	t_token	*tmp;

	if (!list)
		return ;
	tmp = list->first;
	while (tmp)
	{
		free(tmp->content);
		free(tmp);
		tmp = tmp->next;
	}
	free(list);
}
