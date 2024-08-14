#include "../include/minishell.h"

/*
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes
--suppressions=suppressions.supp --log-file=valgrind-out.txt ./minishell
*/

int	main(int argc, char **argv, char **enpv)
{
	t_data	*data;
	int		status;

	(void) argv;
	if (argc != 1)
		return (print_error("No args allowed"));
	data = get_initialized_data(enpv);
	if (!data)
		return (print_error("Data initialization failed"));
	//print_data(data);
	console_initialization(data);
	status = data->status;
	free_data(data);
	return (status);
}
