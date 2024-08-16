#include "../../include/minishell.h"

static char	*ft_get_env(char *key, t_envp_list *current)
{
	char	*value;

	value = NULL;
	while (current)
	{
		if (strs_are_equal(key, current->key))
		{
			value = ft_strdup(current->value);
			return (value);
		}
		current = current->next;
	}
	return (value);
}

static char	*ft_get_path(t_data *data)
{
	char	*path;

	path = ft_get_env("PWD", data->envp_list);
	//printf("FT_GET_PATH: %s\n", path);
	if (!path || strs_are_equal(path, "-"))
	{
		free(path);
		path = ft_get_env("OLDPWD", data->envp_list);
		//printf("FT_GET_OLDPATH: %s\n", path);
		if (!path[0])
			free(path);
	}
	return (path);
}

static void	ft_reasign(char *key, char *value, t_envp_list *current)
{
	while (current)
	{
		if (strs_are_equal(key, current->key))
		{
			free(current->value);
			current->value = ft_strdup(value + 1);
			return ;
		}
		current = current->next;
	}
}

/**
 * @brief Changes the current directory to the one specified by the path.
 *
 * @param old_pwd The current working directory.
 * @param data The data structure containing the environment variables.
 * @return 0 on success, 1 on failure.
 */
static int  ft_cd(char *old_pwd, t_data *data)
{
    char    *path;
    char    *home;

    path = ft_get_path(data);
    printf("PATH: %s\nOLDPWD:%s\n", path, old_pwd);
    if (!path || !strs_are_equal(path, ""))
    {
        home = ft_get_env("HOME", data->envp_list);
        printf("%s\n", home);
        if (chdir(home) != 0)
            return (free(home), print_error("CD: HOME not set"), 1);
        free(home);
    }
    else if ((chdir(path) != 0))
        return (print_error("CD: No such file or directory\n"), 1);
    else
    {
        ft_reasign("OLDPWD", old_pwd, data->envp_list);
        getcwd(old_pwd, sizeof(old_pwd));
        ft_reasign("PWD", old_pwd, data->envp_list);
    }
    return (EXIT_SUCCESS);
}

int cd(t_data *data)
{
	char	current_path[255];

	getcwd(current_path, sizeof(current_path));
	ft_cd(current_path, data);
	return (0);
}
