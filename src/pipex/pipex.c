#include "../../include/minishell.h"

// void	ft_child_process(char **argv, char **envp, int *fd)
// {
// 	int		file_in;

// 	file_in = open(argv[1], O_RDONLY, 0777);
// 	if (file_in == -1)
// 		ft_error();
// 	dup2(fd[1], STDOUT_FILENO);
// 	dup2(file_in, STDIN_FILENO);
// 	close(fd[0]);
// 	ft_execute(argv[2], envp);
// }

// void	ft_parent_process(char **argv, char **envp, int *fd)
// {
// 	int		file_out;

// 	file_out = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
// 	if (file_out == -1)
// 		ft_error();
// 	dup2(fd[0], STDIN_FILENO);
// 	dup2(file_out, STDOUT_FILENO);
// 	close(fd[1]);
// 	ft_execute(argv[3], envp);
// }

int	ft_pipex(t_data data)
{
	t_cmd	*current;
	int		status;
	int		cmd_count;

	current = data->cmd_list;
	status = 0;
	cmd_count = 0;
	if (ft_cmdlist_size(current) > 1)
		cmd_count = 1;
	while (current)
	{
		status = ft_exec_cmd(data, current, cmd_count);
	}
}

int	ft_exec_cmd(t_data *data, t_cmd *node, int cmd_number)
{
	int	status;

	status = 0;
	if (ft_is_builtin(data, node->command[0]) == TRUE && cmd_number == 0)
	{
		status = ft_built_in(data, node);
		if (node->fd_in != NO_FD && node->fd_in != STDIN)
			close(node->fd_in);
		if (node->fd_out != NO_FD && node->fd_out != STDOUT)
			close(node->fd_out);
		return (status);
	}
	else
	{
		g_batch_flag = 1;
		return (ft_fork(data, node, cmd_number));
	}
}