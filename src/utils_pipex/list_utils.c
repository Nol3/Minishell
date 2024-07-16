#include "../../include/minishell.h"

int ft_cmdlist_size(t_cmd *cmd_list)
{
	int		size;
	t_cmd	*current;

	size = 0;
	current = cmd_list;
	while (current)
	{
		size++;
		current = current->next;
	}
	return (size);
}

int	ft_is_builtin(t_data *data, char *str)
{
	int	cntr;

	cntr = 0;
	while (data->built_in_cmd[cntr])
	{
		if (ft_strncmp(str, data->built_in_cmd[cntr],
				ft_strlen(data->built_in_cmd[cntr]) + 1) == 0)
			return (TRUE);
		cntr++;
	}
	return (FALSE);
}

int	ft_built_in(t_data *data, t_cmd *node)
{
	int	status;
	int	original_fd_out;
	int	original_fd_in;

	original_fd_out = dup(STDOUT);
	original_fd_in = dup(STDIN);
	status = 0;
	ft_redir_fd_std(node->fd_in, STDIN, node->fd_in);
	ft_redir_fd_std(node->fd_out, STDOUT, node->fd_out);
	status = ft_exec_builtin(data, node->command);
	ft_redir_fd_std(node->fd_in, STDIN, original_fd_in);
	ft_redir_fd_std(node->fd_out, STDOUT, original_fd_out);
	return (status);
}

int	ft_fork(t_data *data, t_cmd *node, int cmd_number)
{
	int		status;
	pid_t	id;

	status = NO_FD;
	id = fork();
	if (id == 0)
	{
		if (ft_is_builtin(data, node->command[0]) == TRUE && cmd_number != 0)
		{
			status = ft_built_in(data, node);
			exit(status);
		}
		else
			ft_child_process(data, node);
	}
	else
	{
		waitpid(id, &status, 0);
		if (node->fd_in != NO_FD && node->fd_in != STDIN)
			close(node->fd_in);
		if (node->fd_out != NO_FD && node->fd_out != STDOUT)
			close(node->fd_out);
	}
	return (WEXITSTATUS(status));
}