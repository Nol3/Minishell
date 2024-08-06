#include "../../../include/minishell.h"

char	**get_args(t_token **token, int args_size, t_envp_list *envp_list)
{
	char	**args;
	int		i;

	args = (char **)ft_calloc(sizeof(char *), args_size + 1);
	if (!args)
		return (NULL);
	if (!token)
		return (args);
	i = 0;
	*token = skip_spaces(*token, 1);
	while (*token && (*token)->type != PIPE_LINE
		&& !is_redir((*token)->type))
	{
		args[i] = get_arg(token, envp_list);
		if (!args[i])
			return (free_strs(args), NULL);
		i++;
		*token = skip_spaces(*token, 1);
	}
	return (args);
}
