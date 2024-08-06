#include "../../../include/minishell.h"

static t_token	*add_command_to_list(t_cmd_list *cmd_list, t_token *current,
									int args_size, t_envp_list *envp_list)
{
	char			**args;
	t_redir_list	*redir_list;
	enum e_built_in	built_in;
	t_cmd			*cmd;

	args = get_args(&current, args_size, envp_list);
	if (!args)
		return (0);
	redir_list = get_redir_list(&current, envp_list);
	if (!redir_list)
		return (free_strs(args), NULL);
	built_in = get_built_in(args[0]);
	cmd = new_cmd(args, redir_list, built_in);
	if (!cmd)
		return (free_strs(args), free_redir_list(redir_list), NULL);
	add_cmd_last(cmd_list, cmd);
	return (current);
}

int	add_commands_from_input(t_data *data)
{
	t_token	*current;
	t_token	*updated;

	if (is_token_empty(data->token_list))
		return (0);
	current = data->token_list->first;
	data->cmd_list = init_cmd_list(data->cmd_list);
	if (!data->cmd_list)
		return (0);
	while (current)
	{
		updated = add_command_to_list(data->cmd_list, current,
				data->token_list->size, data->envp_list);
		if (updated == current)
			return (0);
		current = updated;
	}
	return (1);
}
