#include "../../../include/minishell.h"

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
	if (!file || file[0] == '\0')
		return (NULL);
	redir = new_redir(file, type);
	if (!redir)
		return (NULL);
	return (redir);
}

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
