#include "../../include/minishell.h"

void ft_cd(const char *path, t_data *data)
{
	char *new_path;
	char *old_path;

	old_path = getcwd(NULL, 0);
	if (chdir(path) == -1)
	{
		print_error("cd: no directory");
		free(old_path);
		return ;
	}
	new_path = getcwd(NULL, 0);
	if (new_path == NULL)
	{
		print_error("cd: error retrieving current directory, cannot access parent directories.");
		free(old_path);
		return ;
	}
	if (data->envp_list)
	{
		free(data->envp_list->value);
		data->envp_list->value = new_path;
	}
	else
	{
		//data->envp_list = malloc(sizeof(t_envp_list));
		data->envp_list->key = "PWD";
		data->envp_list->value = new_path;
		data->envp_list->next = NULL;
	}
	if (old_path)
		free(old_path);
}
