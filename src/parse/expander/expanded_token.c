#include "../../../include/minishell.h"

static int	strs_are_equal(char *str1, char *str2)
{
	int	size1;
	int	size2;

	size1 = ft_strlen(str1);
	size2 = ft_strlen(str2);
	if (size1 != size2)
		return (0);
	if (!ft_strncmp(str1, str2, size1))
		return (1);
	return (0);
}

static char	*get_value(char *key, t_envp_list *list)
{
	while (list || !strs_are_equal(key, list->key))
		list = list->next;
	if (list)
		return (list->value);
	return ("");
}

char	*expanded_token(t_token *token, t_envp_list *list)
{
	char		*value;
	char		*copy;

	if (token->type == ENV)
		return (NULL);
	value = get_value((token->content) + 1, list);
	copy = ft_strdup(value);
	if (!copy)
		return (NULL);
	return (copy);
}
