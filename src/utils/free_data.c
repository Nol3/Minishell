#include "../../include/minishell.h"

static void	free_strs(char **strs)
{
	int	i;

	i = -1;
	while (strs[++i])
		free(strs[i]);
	free(strs);
}

static void	free_envp_list(t_data *data)
{
	t_envp_list	*current;
	t_envp_list	*to_delete;

	current = data->envp_list;
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

static void	free_token_list(t_data *data)
{
	free_list(data->token_list);
}

static void	free_cmd_list(t_data *data)
{
	t_cmd	*current;
	t_cmd	*to_delete;

	current = data->cmd_list;
	to_delete = NULL;
	while (current)
	{
		if (current->choosen_path)
			free_strs(current->choosen_path);
		if (current->command)
			free_strs(current->command);
		to_delete = current;
		current = current->next;
		free(to_delete);
	}
}

void	free_data(t_data *data)
{
	int	i;

	i = -1;
	while (++i < 7)
	{
		if (data->built_in_cmd[i])
			free(data->built_in_cmd[i]);
	}
	if (data->envp)
		free_strs(data->envp);
	free_envp_list(data);
	free_token_list(data);
	free_cmd_list(data);
	free(data);
}
