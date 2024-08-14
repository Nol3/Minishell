#include "../../include/minishell.h"

int	ft_exit(t_data *data)
{
	data->exit = 1;
	printf("Bye\n");
	return (EXIT_SUCCESS);
}
