#include "../../../include/minishell.h"

static int	strs_are_equal(char *str1, char *str2)
{
	int	size1;
	int	size2;

	size1 = ft_strlen(str1);
	size2 = ft_strlen(str2);
	if (size1 != size2)
		return (0);
	if (!ft_strncmp(str1, str2, size1))
		return (1);
	return (0);
}

enum e_built_in	get_built_in(char *command)
{
	if (strs_are_equal(command, "echo"))
		return (B_ECHO);
	if (strs_are_equal(command, "cd"))
		return (B_CD);
	if (strs_are_equal(command, "pwd"))
		return (B_PWD);
	if (strs_are_equal(command, "export"))
		return (B_EXPORT);
	if (strs_are_equal(command, "unset"))
		return (B_UNSET);
	if (strs_are_equal(command, "env"))
		return (B_ENV);
	if (strs_are_equal(command, "exit"))
		return (B_EXIT);
	return (NOT_BUILT_IN);
}
