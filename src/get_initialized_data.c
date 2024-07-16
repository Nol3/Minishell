/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_initialized_data.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angcampo <angcampo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 13:24:31 by angcampo          #+#    #+#             */
/*   Updated: 2024/07/16 14:01:37 by angcampo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	**get_envp(char **envp)
{
	char	**tmp;
	char	**new;
	int		count;
	int		i;

	count = 0;
	tmp = envp;
	while (*tmp)
	{
		count++;
		tmp++;
	}
	new = (char **)malloc(sizeof(char *) * (count + 1));
	if (!new)
		return (NULL);
	i = -1;
	while (++i < count)
		new[i] = ft_strdup(envp[i]);
	new[i] = NULL;
	return (new);
}

static t_envp_list	*get_envp_list(char **envp)
{

}

static void	initialize_built_in_cmd(t_data *data)
{
	data->built_in_cmd[0] = ft_strdup("echo");
	data->built_in_cmd[1] = ft_strdup("cd");
	data->built_in_cmd[2] = ft_strdup("pwd");
	data->built_in_cmd[3] = ft_strdup("export");
	data->built_in_cmd[4] = ft_strdup("unset");
	data->built_in_cmd[5] = ft_strdup("env");
	data->built_in_cmd[6] = ft_strdup("exit");
	data->built_in_cmd[7] = NULL;
}

t_data	*get_initialized_data(char **envp)
{
	t_data	*data;

	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
		return (print_error("Malloc failed"));
	initialize_built_in_cmd(data);
	data->envp = get_envp(envp);
	if (!data->envp)
		return (print_error("Duping envp failed"));
	data->envp_list = get_envp_list(data->envp);
	if (!data->envp_list)
		return (print_error("Creating envp_list failed"));
	data->status = 0;
	data->exit = 0;
	data->token_list = NULL;
	data->cmd_list = NULL;
	return (data);
}
