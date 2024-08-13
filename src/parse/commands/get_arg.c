#include "../../../include/minishell.h"

static char	*concatenated_words(char *str1, char *str2)
{
	char	*result;
	int		i;
	int		j;

	result = (char *)ft_calloc(sizeof(char),
			ft_strlen(str1) + ft_strlen(str2) + 1);
	if (!result)
		return (free(str1), free(str2), NULL);
	i = -1;
	while (str1[++i])
		result[i] = str1[i];
	j = -1;
	while (str2[++j])
		result[i + j] = str2[j];
	free(str1);
	free(str2);
	return (result);
}

static char	*get_aux_in_quotes(t_token *token, t_envp_list *envp_list)
{
	if (token->type == WHITE_SPACE)
		return (ft_strdup(" "));
	if (token->type == ENV && token->state == IN_DQUOTE)
		return (expanded_token(token, envp_list));
	return (ft_strdup(token->content));
}

static char	*get_aux_general(t_token *token, t_envp_list *envp_list)
{
	if (token->type == WORD)
		return (ft_strdup(token->content));
	if (token->type == ENV)
		return (expanded_token(token, envp_list));
	if (token->type == DOUBLE_QUOTE || token->type == QUOTE)
		return (ft_strdup(""));
	return (NULL);
}

char	*get_arg(t_token **token, t_envp_list *envp_list)
{
	char	*arg;
	char	*aux;

	arg = (char *)ft_calloc(sizeof(char), 1);
	aux = NULL;
	if (*token && ((*token)->type == WHITE_SPACE))
		*token = skip_spaces(*token, 1);
	while (*token)
	{
		if ((*token)->state == GENERAL)
			aux = get_aux_general(*token, envp_list);
		else
			aux = get_aux_in_quotes(*token, envp_list);
		if (!aux)
			return (arg);
		arg = concatenated_words(arg, aux);
		if (!arg)
			return (NULL);
		*token = (*token)->next;
		aux = NULL;
	}
	return (arg);
}
