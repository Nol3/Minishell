#include "../../include/minishell.h"

void	ft_export(t_data data)
{
	t_envp_list	*current;
	//t_envp_list	*tmp;
	//int			i;

	current = data.envp_list;
	while (current)
	{
		if (current->key && current->value)
			printf("declare -x %s=\"%s\"\n", current->key, current->value);
		else if (current->key)
			printf("declare -x %s\n", current->key);
		current = current->next;
	}
	data.status = 0;
}
