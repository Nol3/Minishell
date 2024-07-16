#include "../include/minishell.h"

/*
static void	print_data(t_data *data)
{
	//int	i;

	//i = -1;
	//while (data->envp[++i])
	//	ft_printf("%s\n", data->envp[i]);
	while (data->envp_list)
	{
		ft_printf("key: %s, value: %s\n",
			data->envp_list->key,
			data->envp_list->value);
		data->envp_list = data->envp_list->next;
	}
}
*/

int	main(int argc, char **argv, char **enpv)
{
	t_data	*data;

	(void) argv;
	if (argc != 1)
		return (print_error("No args allowed"));
	data = get_initialized_data(enpv);
	if (!data)
		return (print_error("Data initialization failed"));
	//print_data(data);
}
