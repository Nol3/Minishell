#include "../../include/minishell.h"

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

static char	ft_get_path(const t_data *data)
{
	char	*path;

	path = ft_get_path(data->envp_list);
	if (path && strs_are_equal(path, "-"))
	{
		free(path);
		path = ft_get_env("OLDPWD", data->envp_list);
		if (!path[0])
			free(path);
	}
	return (path);
}

static void	ft_reasign(char *name, char *value)
{
	int		cnt;
	char	**tmp;
	char	*tmp2;

	cnt = 0;
	while (g_data.env[cnt])
	{
		tmp = ft_split(g_data.env[cnt], '=');
		if (ft_strncmp(tmp[0], name, ft_strlen(name)) == 0)
		{
			free(g_data.env[cnt]);
			tmp2 = ft_strjoin(name, "=");
			g_data.env[cnt] = ft_strjoin(tmp2, value);
			free(tmp2);
			tmp = ft_clean_matrix(tmp);
			return ;
		}
		tmp = ft_clean_matrix(tmp);
		cnt++;
	}
	g_data.vars_mod = 1;
}

/**
 * @brief Changes the current directory to the one specified by the path.
 *
 * @param old_pwd The current working directory.
 * @param data The data structure containing the environment variables.
 * @return 0 on success, 1 on failure.
 */
int	ft_cd(const char *old_pwd, const t_data *data)
{
	char	*path;
	char	*home;

	path = ft_get_path(data);
	if (!path)
	{
		home = ft_get_env("HOME", data->envp_list);
		if (chdir(home) != 0)
			return (free(home), ft_print_error("CD: HOME not set"), 1);
		free(home);
	}
	else if ((chdir(path) != 0))
		return (ft_print_error("CD: No such file or directory\n"), 1);
	else
	{
		ft_reasign("OLDPWD", old_pwd, data->envp);
		getcwd(old_pwd, sizeof(old_pwd));
		ft_reasign("PWD", old_pwd, data->envp);
		return (0);
	}
}

int cd(t_data data)
{
	char	current_path[255];

	getcwd(current_path, sizeof(current_path));
	ft_cd(current_path, &data);
	return (0);
}
