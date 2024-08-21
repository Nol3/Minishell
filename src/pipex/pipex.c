/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcarden <alcarden@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 16:30:42 by alcarden          #+#    #+#             */
/*   Updated: 2024/08/21 16:30:43 by alcarden         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int				g_pack;

int	ft_pipex(t_data *data)
{
	int		status;
	int		cmd_count;

	data->current_cmd = data->cmd_list->first;
	status = 0;
	cmd_count = 0;
	if (data->cmd_list->size > 1)
		cmd_count = 1;
	while (data->current_cmd)
	{
		if (data->current_cmd->built_in != NOT_BUILT_IN)
			status = ft_exec_builtin(data);
		else
			status = ft_exec_cmd(data, cmd_count);
		g_pack = 0;
		data->status = status;
		data->current_cmd = data->current_cmd->next;
		cmd_count++;
	}
	return (EXIT_SUCCESS);
}

int	ft_exec_cmd(t_data *data, int cmd_count)
{
	g_pack = 1;
	return (ft_fork(data, cmd_count));
}

int	ft_fork(t_data *data, int cmd_count)
{
	int		status;
	pid_t	id;

	status = UNDEF_FD;
	id = fork();
	cmd_count = 0;
	if (id == 0 && cmd_count == 0)
		ft_child_process(data);
	else
	{
		waitpid(id, &status, 0);
		if (data->current_cmd->fd_in != UNDEF_FD
			&& data->current_cmd->fd_in != STDIN)
			close(data->current_cmd->fd_in);
		if (data->current_cmd->fd_out != UNDEF_FD
			&& data->current_cmd->fd_out != STDOUT)
			close(data->current_cmd->fd_out);
	}
	return (WEXITSTATUS(status));
}

static void	child_process_redir(t_cmd *node)
{
	ft_redir_fd_std(node->fd_in, STDIN, node->fd_in);
	ft_redir_fd_std(node->fd_out, STDOUT, node->fd_out);
}

int	ft_child_process(t_data *data)
{
	int		original_stdin;
	int		original_stdout;
	char	*absolute_path;
	int		exit_status;
	char	**environment_paths;

	exit_status = 0;
	environment_paths = get_paths(data->envp);
	absolute_path = abs_bin_path(data->current_cmd->args[0],
										environment_paths);
	ft_free_matrix(environment_paths);
	if (!absolute_path)
		exit(EXIT_SUCCESS);
	original_stdin = data->current_cmd->fd_in;
	original_stdout = data->current_cmd->fd_out;
	child_process_redir(data->current_cmd);
	if (execve(absolute_path, data->current_cmd->args, data->envp) < 0)
	{
		free(absolute_path);
		exit_status = EXIT_FAILURE;
		ft_redir_fd_std(original_stdin, exit_status, original_stdout);
		exit(exit_status);
	}
	return (exit_status);
}
