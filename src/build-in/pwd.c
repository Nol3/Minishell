#include "../../include/minishell.h"

int	ft_pwd(t_data *data)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
	{
		ft_putstr_fd("minishell: pwd: error retrieving current directory.", STDERR);
		ft_putendl_fd(strerror(errno), STDERR_FILENO);
		return (1);
	}
	ft_putendl_fd(pwd, data->current_cmd->fd_out);
	free(pwd);
	return (0);
}
