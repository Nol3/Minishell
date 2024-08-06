#include "../../include/minishell.h"

int	ft_pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
	{
		ft_putstr_fd("minishell: pwd: error retrieving current directory.", STDERR);
		ft_putendl_fd(strerror(errno), STDERR);
		return (1);
	}
	ft_putendl_fd(pwd, STDOUT);
	free(pwd);
	return (0);
}

int	pwd(char **cmd)
{
	if (ft_strncmp(cmd[0], "pwd", 3) == 0 && cmd[0][3] == '\0')
		return (ft_pwd());
	else
		return (2);
}
