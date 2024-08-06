#include "../../include/minishell.h"



void	console_initialization(t_data *data)
{
	char	*input;

	while (data->exit != 1)
	{
		input = readline("Minishell$ ");
		if (!input)
		{
			free(input);
			ft_printf("Bye\n");
			data->exit = 1;
			continue ;
		}
		if (!add_tokens_from_input(data, input))
			continue ;
		if (!valid_token_list(data->token_list))
			continue;
		if (!add_commands_from_input(data))
			continue ;
		ft_pipex(data);
		// if (*input != '\0')
		// 	add_history(input);
		// restore_lists(&data, input);
	}
	//clear_history();
}
