#include "../../../include/minishell.h"

int	tokenize_word(t_token_list *list, char *str, enum e_token_state state)
{
	(void) list;
	(void) str;
	(void) state;
	return (1);
}

int	tokenize_quote(t_token_list *list, enum e_token_state *state, int quote)
{
	(void) list;
	(void) quote;
	(void) state;
	return (1);
}

int	tokenize_env(t_token_list *list, char *str, enum e_token_state state)
{
	(void) list;
	(void) str;
	(void) state;
	return (1);
}

int	tokenize_redir(t_token_list *list, char *str, enum e_token_state state)
{
	(void) list;
	(void) str;
	(void) state;
	return (1);
}
