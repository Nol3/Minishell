#include "../../include/minishell.h"

int	ft_pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
	{
		ft_putstr_fd("minishell: pwd: error retrieving current directory.", STDERR);
		ft_putendl_fd(strerror(errno), STDERR_FILENO);
		return (1);
	}
	ft_putendl_fd(pwd, STDOUT_FILENO);
	free(pwd);
	return (0);
}
