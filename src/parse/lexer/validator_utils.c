#include "../../../include/minishell.h"

int	is_redir(int type)
{
	return (type == REDIR_IN || type == REDIR_OUT
		|| type == HERE_DOC || type == DREDIR_OUT);
}

t_token	*skip_spaces(t_token *token, int next)
{
	while (token && token->type == WHITE_SPACE)
	{
		if (next)
			token = token->next;
		else
			token = token->prev;
	}
	return (token);
}
