#include "../../../include/minishell.h"

static char	*get_value(char *key, t_envp_list *list)
{
	while (list && !strs_are_equal(key, list->key))
		list = list->next;
	if (list)
		return (list->value);
	return ("");
}

char	*expanded_token(t_token *token, t_envp_list *list)
{
	char		*value;
	char		*copy;

	if (token->type != ENV)
		return (NULL);
	value = get_value((token->content) + 1, list);
	copy = ft_strdup(value);
	if (!copy)
		return (NULL);
	return (copy);
}
