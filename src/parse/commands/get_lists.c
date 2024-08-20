#include "../../../include/minishell.h"

/*

t_redir_list	*get_redir_list(t_token **token, t_envp_list *envp_list)
{
	t_redir_list	*redir_list;
	t_redir			*redir;

	redir_list = NULL;
	redir_list = init_redir_list(redir_list);
	if (!redir_list)
		return (NULL);
	if (!token)
		return (redir_list);
	while (*token && (*token)->type != PIPE_LINE)
	{
		while ((*token) && (*token)->type != PIPE_LINE
			&& !is_redir((*token)->type))
			*token = (*token)->next;
		if ((*token) && is_redir((*token)->type))
		{
			redir = get_redir(token, envp_list);
			if (!redir)
				return (free_redir_list(redir_list), NULL);
			add_redir_last(redir_list, redir);
		}
	}
	return (redir_list);
}

char	**get_args(t_token **token, int args_size, t_envp_list *envp_list)
{
	char	**args;
	int		i;

	args = (char **)ft_calloc(sizeof(char *), args_size + 2);
	if (!args)
		return (NULL);
	if (!token)
		return (args);
	i = 0;
	if (*token && ((*token)->type == WHITE_SPACE))
		*token = skip_spaces(*token, 1);
	while (*token && (*token)->type != PIPE_LINE
		&& !is_redir((*token)->type))
	{
		args[i] = get_arg(token, envp_list);
		if (!args[i])
			return (free_strs(args), NULL);
		if (args[i][0] == '\0')
			free(args[i--]);
		i++;
		if (*token && ((*token)->type == WHITE_SPACE))
			*token = skip_spaces(*token, 1);
	}
	return (args);
}

*/

static t_redir	*get_redir(t_token **token, t_envp_list *envp_list)
{
	t_redir				*redir;
	enum e_token_type	type;
	char				*file;

	type = (*token)->type;
	if (!is_redir(type))
		return (NULL);
	*token = (*token)->next;
	file = get_arg(token, envp_list);
	if (!file)
		return (NULL);
	if (file[0] == '\0')
		return (print_error("No such file or directory"), NULL);
	redir = new_redir(file, type);
	if (!redir)
		return (NULL);
	return (redir);
}

void	get_lists(t_token **token, t_envp_list *envp_list,
				char **args, t_redir_list *redir_list)
{
	int		i;
	t_redir	*redir;

	if (!token)
		return ;
	i = -1;
	while (*token && (*token)->type != PIPE_LINE)
	{
		if (*token && ((*token)->type == WHITE_SPACE))
			*token = skip_spaces(*token, 1);
		if ((*token) && !is_redir((*token)->type))
		{
			args[++i] = get_arg(token, envp_list);
			if (args[i] && args[i][0] == '\0')
				free(args[i--]);
		}
		else if ((*token) && is_redir((*token)->type))
		{
			redir = get_redir(token, envp_list);
			add_redir_last(redir_list, redir);
		}
		if ((i >= 0 && !args[i]) || !redir)
			return (free_strs(args), free_redir_list(redir_list));
	}
}
