#include "../../include/minishell.h"

int	print_error(const char *str)
{
	ft_printf("Error:\n");
	if (str && str[0])
		ft_printf("%s\n", str);
	return (0);
}
