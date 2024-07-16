#include "../include/minishell.h"

int	main(int argc, char **argv, char **enpv)
{
	t_data	*data;

	(void) argv;
	if (argc != 1)
		return (print_error("No args allowed"));
	data = get_initialized_data(enpv);
	if (!data)
		return (print_error("Data initialization failed"));
}
