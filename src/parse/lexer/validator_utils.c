#include "../../../include/minishell.h"

/*
static void	print_node(t_token *token)
{
	int	i;

	i = 0;
	printf("content: ");
	while (i < token->len)
		putchar(token->content[i++]);
	printf(", len: %i", token->len);
	printf(", state: %i", token->state);
	printf(", token: %i\n", token->type);
}
*/

int	is_redir(int type)
{
	return (type == REDIR_IN || type == REDIR_OUT
		|| type == HERE_DOC || type == DREDIR_OUT);
}

t_token	*skip_spaces(t_token *token, int next)
{
	if (next)
		token = token->next;
	else
		token = token->prev;
	while (token && token->type == WHITE_SPACE)
	{
		if (next)
			token = token->next;
		else
			token = token->prev;
	}
	return (token);
}
