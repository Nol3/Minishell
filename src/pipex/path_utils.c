/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcarden <alcarden@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 16:30:53 by alcarden          #+#    #+#             */
/*   Updated: 2024/08/21 16:46:24 by alcarden         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	**get_paths(char *envp[])
{
	int		i;
	int		flag;
	char	**path_env_var;
	char	**paths;

	i = 0;
	flag = 0;
	if (!envp)
		return (NULL);
	while (envp[i] && flag == 0)
	{
		if (ft_strnstr(envp[i], "PATH", 4) && envp[i][4] == '=')
			flag = 1;
		if (flag == 0)
			i++;
	}
	if (envp[i] == NULL)
		return (NULL);
	path_env_var = ft_split(envp[i], '=');
	paths = ft_split(path_env_var[1], ':');
	ft_free_matrix(path_env_var);
	return (paths);
}

char	*abs_bin_path(char *cmd, char **envp)
{
	int		i;
	char	*slash_cmd;
	char	*possible_bin;

	i = 0;
	slash_cmd = NULL;
	possible_bin = NULL;
	if ((cmd[0] == '/') || (cmd[0] == '.' && cmd[1] == '/'))
		return (ft_valid_cmd(cmd));
	slash_cmd = ft_strjoin("/", cmd);
	if (access(slash_cmd, F_OK) == 0)
		return (slash_cmd);
	if (envp)
	{
		while (envp[i])
		{
			if (possible_bin)
				free(possible_bin);
			possible_bin = ft_strjoin(envp[i++], slash_cmd);
			if (access(possible_bin, F_OK) == 0)
				return (free(slash_cmd), possible_bin);
		}
	}
	perror("shell: command not found\n");
	return (free(slash_cmd), free(possible_bin), NULL);
}

char	*ft_valid_cmd(char *cmd)
{
	char	*valid_cmd;

	valid_cmd = strdup(cmd);
	if (access(cmd, F_OK) == 0)
	{
		if (access(cmd, X_OK) < 0)
		{
			perror("Permission denied\n");
			return (valid_cmd);
		}
		else
			return (valid_cmd);
	}
	return (valid_cmd);
}

void	ft_free_matrix(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (envp[i])
		{
			free(envp[i]);
			envp[i] = NULL;
		}
		i++;
	}
	free(envp);
	envp = NULL;
}
