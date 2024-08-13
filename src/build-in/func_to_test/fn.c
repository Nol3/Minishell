// analizar estas funciones para cd

// void	ft_cd(t_info *i)
// {
// 	i->c->pwd = get_pwd(i->c);
// 	i->c->input = get_directory_path(i);
// 	if (i->c->input && (!ft_strcmp(i->c->input, "")
// 			|| !ft_strcmp(i->c->input, "-")))
// 		check_oldpwd(i);
// 	else if (chdir(i->c->input) != 0 \
// 	&& i->c->input != NULL && ft_strcmp(i->c->input, "~") != 0 \
// 	&& ft_strcmp(i->c->input, "-") != 0)
// 	{
// 		write (2, "cd: ", 4);
// 		write (2, i->par->args[0], ft_strlen(i->par->args[0]));
// 		write (2, ": No such file or directory\n", 28);
// 		i->status = 1;
// 	}
// 	else
// 	{
// 		changer_oldpwd_env(i->c, i->c->pwd);
// 		changer_pwd_env(i->c);
// 	}
// }

// void	changer_oldpwd_env(t_cmd *c, char *oldpwd)
// {
// 	t_env	*curr;

// 	curr = c->list_env;
// 	while (curr)
// 	{
// 		if (ft_strcmp(curr->key, "OLDPWD") == 0)
// 		{
// 			free(curr->value);
// 			curr->value = ft_strdup(oldpwd);
// 		}
// 		curr = curr->next;
// 	}
// 	free(oldpwd);
// }

// void	changer_pwd_env(t_cmd *c)
// {
// 	t_env	*curr;

// 	curr = c->list_env;
// 	while (curr)
// 	{
// 		if (ft_strcmp(curr->key, "PWD") == 0)
// 		{
// 			c->pwd = get_pwd(c);
// 			free(curr->value);
// 			curr->value = ft_strdup(c->pwd);
// 		}
// 		curr = curr->next;
// 	}
// 	free(c->pwd);
// }

// char	*get_pwd(t_cmd *c)
// {
// 	c->pwd = getcwd(NULL, 0);
// 	if (c->pwd == NULL)
// 		perror("error");
// 	return (c->pwd);
// }

// int	clear_env(t_info *i)
// {
// 	t_env	*curr;

// 	curr = i->c->list_env;
// 	while (i->c->curr)
// 	{
// 		if (!(ft_strcmp(curr->key, "HOME") == 0))
// 			return (0);
// 		curr = curr->next;
// 	}
// 	return (1);
// }

// para unset

// void	ft_unset(t_info *i)
// {
// 	if (i->par->args[0] == NULL)
// 		return ;
// 	else if (top_the_list(i))
// 		return ;
// 	else if (middle_the_list(i))
// 		return ;
// 	else if (finish_the_list(i))
// 		return ;
// }

// int	top_the_list(t_info *i)
// {
// 	t_env	*tmp;

// 	tmp = i->c->list_env;
// 	if (ft_strcmp(tmp->key, i->par->args[0]) == 0)
// 	{
// 		i->c->list_env = tmp->next;
// 		free(tmp->key);
// 		free(tmp->value);
// 		free(tmp);
// 		i->status = 0;
// 		return (1);
// 	}
// 	return (0);
// }

// int	middle_the_list(t_info *i)
// {
// 	t_env	*tmp;
// 	t_env	*to_free;

// 	tmp = i->c->list_env;
// 	while (tmp != NULL && tmp->next != NULL)
// 	{
// 		if (ft_strcmp(tmp->next->key, i->par->args[0]) == 0)
// 		{
// 			to_free = tmp->next;
// 			tmp->next = tmp->next->next;
// 			free(to_free->key);
// 			free(to_free->value);
// 			free(to_free);
// 			i->status = 0;
// 			return (1);
// 		}
// 		tmp = tmp->next;
// 	}
// 	return (0);
// }

// int	finish_the_list(t_info *i)
// {
// 	t_env	*tmp;
// 	t_env	*prev;

// 	tmp = i->c->list_env;
// 	prev = NULL;
// 	while (tmp->next != NULL)
// 	{
// 		prev = tmp;
// 		tmp = tmp->next;
// 	}
// 	if (ft_strcmp(tmp->key, i->par->args[0]) == 0)
// 	{
// 		free(tmp->key);
// 		free(tmp->value);
// 		free(tmp);
// 		if (prev != NULL)
// 			prev->next = NULL;
// 		else
// 			i->c->list_env = NULL;
// 		i->status = 0;
// 		return (1);
// 	}
// 	return (0);
// }

