#include "../../include/minishell.h"

int				g_pack;

int	ft_cmdlist_size(t_cmd *cmd_list)
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

int	ft_pipex(t_data *data)
{
	t_cmd	*current;
	int		status;
	int		cmd_count;

	current = data->current_cmd;
	status = 0;
	cmd_count = 0;
	if (ft_cmdlist_size(current) > 0)
		cmd_count = 1;
	while (current)
	{
		status = ft_exec_cmd(data, current, cmd_count);
		g_pack = 0;
		data->status = status;
		current = current->next;
		cmd_count++;
	}
	return (EXIT_SUCCESS);
}

enum e_built_in	get_builtin_type(const char *cmd)
{
	if (strcmp(cmd, "echo") == 0)
		return (B_ECHO);
	else if (strcmp(cmd, "cd") == 0)
		return (B_CD);
	else if (strcmp(cmd, "pwd") == 0)
		return (B_PWD);
	else if (strcmp(cmd, "export") == 0)
		return (B_EXPORT);
	else if (strcmp(cmd, "unset") == 0)
		return (B_UNSET);
	else if (strcmp(cmd, "env") == 0)
		return (B_ENV);
	else if (strcmp(cmd, "exit") == 0)
		return (B_EXIT);
	else
		return (NOT_BUILT_IN);
}

int	ft_exec_builtin(t_data *data, char *cmd)
{
	enum e_built_in	builtin_type;

	(void)data;
	builtin_type = get_builtin_type(cmd);
	// if (builtin_type == B_ECHO)
	// 	return (ft_echo(data->current_cmd->args));
	// else if (builtin_type == B_CD)
	// 	return (ft_cd(data, data->current_cmd->args));
	// else if (builtin_type == B_PWD)
	// 	return (ft_pwd());
	// else if (builtin_type == B_EXPORT)
	// 	return (ft_export(data, data->current_cmd->args));
	// else if (builtin_type == B_UNSET)
	// 	return (ft_unset(data, data->current_cmd->args));
	// else if (builtin_type == B_ENV)
	// 	return (ft_env(data));
	// else if (builtin_type == B_EXIT)
	// 	return (ft_exit(data, data->current_cmd->args));
	// else
		return (EXIT_FAILURE);
}

int	ft_exec_cmd(t_data *data, t_cmd *node, int cmd_count)
{
	int	status;

	status = 0;
	//ft_exec_builtin(t_data *data, char *cmd);
	g_pack = 1;
	// t_redir
	return (ft_fork(data, node, cmd_count));
}

int	ft_fork(t_data *data, t_cmd *node, int cmd_count)
{
	int		status;
	pid_t	id;

	status = UNDEF_FD;
	id = fork();
	cmd_count = 0;
	if (id == 0 && cmd_count == 0) // child process
	{
		// check if it is a built-in command to-do
		ft_child_process(data, node);
	}
	else // parent process
	{
		waitpid(id, &status, 0);
		if (node->fd_in != UNDEF_FD && node->fd_in != STDIN)
			close(node->fd_in);
		if (node->fd_out != UNDEF_FD && node->fd_out != STDOUT)
			close(node->fd_out);
	}
	return (WEXITSTATUS(status));
}

static void	child_process_redir(t_cmd *node)
{
	ft_redir_fd_std(node->fd_in, STDIN, node->fd_in);
	ft_redir_fd_std(node->fd_out, STDOUT, node->fd_out);
}

int	ft_child_process(t_data *data, t_cmd *node)
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
	child_process_redir(node);
	paths = get_paths(data->envp);
	tmp = abs_bin_path(node->args[0], paths);
	if (!tmp)
		exit(EXIT_FAILURE);
	if (execve(tmp, node->args, data->envp) < 0)
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