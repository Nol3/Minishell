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
	if (data->current_cmd)
		ft_exec_builtin(data);
	while (data->current_cmd)
	{
		status = ft_exec_cmd(data, cmd_count);
		g_pack = 0;
		data->status = status;
		data->current_cmd = data->current_cmd->next;
		cmd_count++;
	}
	return (EXIT_SUCCESS);
}

int	ft_exec_builtin(t_data *data)
{
	int	exit;

	exit = 0;
	if (data->current_cmd->built_in == B_ECHO)
		exit = echo(data);
	else if (data->current_cmd->built_in == B_CD)
		exit = cd(data);
	else if (data->current_cmd->built_in == B_PWD)
		exit = ft_pwd();
	else if (data->current_cmd->built_in == B_EXPORT)
		exit = ft_export(data);
	else if (data->current_cmd->built_in == B_UNSET)
		exit = ft_unset(data);
	else if (data->current_cmd->built_in == B_ENV)
	{
		printf("env\n");
		exit = env(data);
	}
	else if (data->current_cmd->built_in == B_EXIT)
		exit = ft_exit(data);
	else
		return (EXIT_FAILURE);
	data->current_cmd = data->current_cmd->next;
	return (exit);
}

int	ft_exec_cmd(t_data *data, int cmd_count)
{
	// int	status;

	// status = 0;
	g_pack = 1;
	// t_redir
	return (ft_fork(data, cmd_count));
}

int	ft_fork(t_data *data, int cmd_count)
{
	int		status;
	pid_t	id;

	status = UNDEF_FD;
	id = fork();
	cmd_count = 0;
	if (id == 0 && cmd_count == 0) // child process
	{
		// check if it is a built-in command to-do
		ft_child_process(data);
	}
	else // parent process
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
	int		og_stdin;
	int		og_stdout;
	char	*tmp;
	int		status;
	char	**paths;

	tmp = NULL;
	paths = NULL;
	status = 0;
	og_stdin = dup(STDIN);
	og_stdout = dup(STDOUT);
	child_process_redir(data->current_cmd);
	paths = get_paths(data->envp);
	tmp = abs_bin_path(data->current_cmd->args[0], paths);
	if (!tmp)
		exit(EXIT_FAILURE);
	if (execve(tmp, data->current_cmd->args, data->envp) < 0)
	{
		free(tmp);
		ft_free_matrix(paths);
		ft_redir_fd_std(og_stdin, status, og_stdout);
		exit(EXIT_FAILURE);
	}
	return (status);
}

void	ft_redir_fd_std(int fd, int std, int fd2)
{
	if (fd != UNDEF_FD && fd != std)
	{
		if (dup2(fd2, std) < 0)
			print_error("REDIR_ERROR");
		close(fd);
	}
}

/*
---------------- builtin functions ----------------
*/

// int	ft_is_builtin(t_data *data, char *str)
// {
// 	int	cntr;

// 	cntr = 0;
// 	while (data->built_in_cmd[cntr])
// 	{
// 		if (ft_strncmp(str, data->built_in_cmd[cntr],
// 				ft_strlen(data->built_in_cmd[cntr]) + 1) == 0)
// 			return (TRUE);
// 		cntr++;
// 	}
// 	return (FALSE);
// }

// int	ft_built_in(t_data *data, t_cmd *node)
// {
// 	int	status;
// 	int	original_fd_out;
// 	int	original_fd_in;

// 	original_fd_out = dup(STDOUT);
// 	original_fd_in = dup(STDIN);
// 	status = 0;
// 	ft_redir_fd_std(node->fd_in, STDIN, node->fd_in);
// 	ft_redir_fd_std(node->fd_out, STDOUT, node->fd_out);
// 	status = ft_exec_builtin(data, node->command);
// 	ft_redir_fd_std(node->fd_in, STDIN, original_fd_in);
// 	ft_redir_fd_std(node->fd_out, STDOUT, original_fd_out);
// 	return (status);
// }
