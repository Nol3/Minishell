#include "../../../include/minishell.h"

int	in_charset(char c)
{
	return (c == '\'' || c == '\"' || c == '<' || c == '>' || c == '|'
		|| c == '$' || ft_isspace(c) || c == '\n' || c == '\0');
}

char	*ft_strndup(char *s1, size_t n)
{
	size_t	size;
	char	*res;
	size_t	i;

	size = (size_t)ft_strlen(s1);
	if (n < size)
		size = n;
	res = (char *)malloc((size + 1) * sizeof(char));
	if (res == 0)
		return (res);
	i = -1;
	while (++i < size)
		res[i] = s1[i];
	res[size] = '\0';
	return (res);
}
