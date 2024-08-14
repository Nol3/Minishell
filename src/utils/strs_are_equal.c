#include "../../include/minishell.h"

int	strs_are_equal(char *str1, char *str2)
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
