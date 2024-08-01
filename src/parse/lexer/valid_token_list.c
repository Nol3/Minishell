#include "../../../include/minishell.h"

static int	error_with_pipe(t_token *token)
{
	t_token	*prev;
	t_token	*next;

	prev = skip_spaces(token, 0);
	next = skip_spaces(token, 1);
	if ((!prev || !next) || (prev->type != WORD
			&& next->type != WORD && !is_redir(next->type)))
		return (1);
	return (0);
}

static int	error_with_redir(t_token *token)
{
	t_token	*next;

	next = skip_spaces(token, 1);
	if (!next || (next->type != WORD && next->type != ENV))
		return (1);
	return (0);
}

static int	error_with_quotes(t_token **token)
{
	t_token	*current;

	current = *token;
	current = current->next;
	while (current && current->type != (*token)->type)
		current = current->next;
	*token = current;
	if (!current)
		return (0);
	return (1);
}

int	valid_token_list(t_token_list *list)
{
	t_token	*current;

	if (!list)
		return (0);
	current = list->first;
	while (current)
	{
		if ((current->type == PIPE_LINE)
			&& (error_with_pipe(current)))
			return (print_error("syntax error near pipe token"));
		else if ((is_redir(current->type))
			&& (error_with_redir(current)))
			return (print_error("syntax error near redir token"));
		else if ((((current->type == DOUBLE_QUOTE)
					|| (current->type == QUOTE)))
			&& (error_with_quotes(&current)))
			return (print_error("syntax error near double or single quotes"));
		current = current->next;
	}
	return (1);
}
