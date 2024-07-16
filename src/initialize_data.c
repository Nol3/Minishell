/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_data.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angcampo <angcampo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 12:40:11 by angcampo          #+#    #+#             */
/*   Updated: 2024/07/16 12:55:55 by angcampo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"



/*
We need as built_in_cmd:
	0: echo with option -n.
	1: cd with only a relative or absolute path.
	2: pwd (no flags).
	3: export (no flags).
	4: unset (no flags).
	5: env (no flags or arguments).
	6: exit (no flags).
*/
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

int	initialize_data(t_data *data, char **envp)
{
	initialize_built_in_cmd(data);
	data->status = 0;
	data->exit = 0;
	data->envp = envp;
	data->envp_list = NULL;
	data->token_list = NULL;
	data->cmd_list = NULL;
}
