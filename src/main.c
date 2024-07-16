#include "../include/minishell.h"

static void	print_data(t_data *data)
{
	t_envp_list	*current;

	current = data->envp_list;
	while (current)
	{
		ft_printf("key: %s, value: %s\n",
			current->key,
			current->value);
		current = current->next;
	}
}

/*
valgrind --leak-check=full --track-origins=yes --log-file=valgrind-out.txt ./minishell
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
	print_data(data);
	//initialize_console(data);
	status = data->status;
	free_data(data);
	return (status);
}
