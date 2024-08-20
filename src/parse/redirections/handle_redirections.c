#include "../../../include/minishell.h"

static int	handle_pipe(t_cmd *cmd, int *fd_in)
{
	int	fd[2];

	if (pipe(fd) == -1)
		return (print_error("Pipe error"), 0);
	printf("PIPE: fd[] = {%i, %i}\n", fd[0], fd[1]);
	if (cmd->fd_out > 2)
		close(fd[1]);
	else
		cmd->fd_out = fd[1];
	*fd_in = fd[0];
	return (1);
}

static int	handle_redir_list(t_cmd *cmd, int *fd_in)
{
	if (!cmd->redir_list || is_redir_empty(cmd->redir_list))
	{
		cmd->fd_in = *fd_in;
	}
	return (1);
}

int	handle_redirections(t_data *data)
{
	int		fd_in;
	int		ok;
	t_cmd	*cmd;

	if (!data || !data->cmd_list || is_cmd_empty(data->cmd_list))
		return (0);
	cmd = data->cmd_list->first;
	fd_in = STDIN;
	ok = 1;
	while (cmd && ok)
	{
		ok = handle_redir_list(cmd, &fd_in);
		if (ok && cmd->next)
			ok = handle_pipe(cmd, &fd_in);
		printf("CMD: fd[] = {%i, %i}\n", cmd->fd_in, cmd->fd_out);
		cmd = cmd->next;
	}
	return (1);
}
