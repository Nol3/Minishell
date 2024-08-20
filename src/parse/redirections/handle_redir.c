#include "../../../include/minishell.h"

static int	redir_in(t_cmd *cmd, t_redir *redir)
{
	if (cmd->fd_in > 2)
		close(cmd->fd_in);
	cmd->fd_in = open(redir->file, O_RDONLY);
	if (cmd->fd_in == -1)
		return (print_error("When opening file"), 0);
	if (!redir->next && cmd->fd_in > 2)
	{
		close(cmd->fd_in);
		cmd->fd_in = 0;
	}
	return (1);
}

static int	redir_out(t_cmd *cmd, t_redir *redir)
{
	if (cmd->fd_out > 2)
		close(cmd->fd_out);
	if (redir->type == REDIR_OUT)
		cmd->fd_out = open(redir->file,
				O_WRONLY | O_CREAT | O_TRUNC,
				0644);
	else
		cmd->fd_out = open(redir->file,
				O_WRONLY | O_CREAT | O_APPEND,
				0644);
	if (cmd->fd_out == -1)
		return (0);
	return (1);
}
/*
REDIR_IN = '<',
	REDIR_OUT = '>',
	HERE_DOC,
	DREDIR_OUT,
*/

static int	here_doc(t_cmd *cmd, char *here_doc)
{
	char	*input;
	int		fd[2];

	input = NULL;
	if (!here_doc || pipe(fd) < 0)
		return (-1);
	input = readline("> ");
	while (input && !strs_are_equal(input, here_doc))
	{
		ft_putstr_fd(input, fd[1]);
		ft_putstr_fd("\n", fd[1]);
		free(input);
		input = readline("> ");
	}
	free(input);
	close(fd[1]);
	cmd->fd_in = fd[0];
	return (1);
}

int	handle_redir(t_cmd *cmd, t_redir *redir)
{
	if (redir->type == REDIR_IN)
		return (redir_in(cmd, redir));
	if (redir->type == REDIR_OUT
		|| redir->type == DREDIR_OUT)
		return (redir_out(cmd, redir));
	else if (redir->type == HERE_DOC)
		return (here_doc(cmd, redir->file));
	return (1);
}
