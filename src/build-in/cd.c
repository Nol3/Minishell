#include "../../include/minishell.h"

void ft_cd(t_data *data, char **cmd)
{
	if (cmd[1] == NULL)
		ft_cd_home();
	else if (ft_strncmp(cmd[1], "-", 1) == 0)
	{
		if (cmd[1][1] == '\0')
			ft_cd_previus_directory(data);
		else
			return (1);
	}
	else if (ft_strncmp(cmd[1], "~", 1) == 0)
	{
		if (cmd[1][1] == '\0')
			ft_cd_home();
		else
			return (1);
	}
	else if (ft_strncmp(cmd[1], "..", 2) == 0)
	{
		if (cmd[1][2] == '\0')
			ft_cd_father();
		else
			return (1);
	}
	else if (ft_strncmp(cmd[1], ".", 1) == 0)
	{
		if (cmd[1][1] == '\0')
			ft_cd_confirm(data);
		else
			return (1);
	}
	else if (ft_strncmp(cmd[1], "/", 1) == 0)
	{
		if (cmd[1][1] == '\0')
			ft_cd_root();
		else
			return (1);
	}
	return (1);
	// else
	// {
	// 	if (chdir(cmd[1]) == -1)
	// 	{
	// 		print_error("cd: no directory");
	// 		return ;
	// 	}
	// }
}

//hacer las opciones de cd. (cd - cd ~ cd .. cd . cd /)

void ft_cd_previus_directory(t_data *data)
{
	char *old_pwd;

	old_pwd = getenv("OLDPWD");
	if (old_pwd == NULL)
	{
		print_error("cd: OLDPWD not set");
		return ;
	}
	else
	{
		chdir(old_pwd);
		printf("%s\n", old_pwd);
	}
	//ft_cd(old_pwd, data);
}

void  ft_cd_home(void)
{
	char *home;

	home = getenv("HOME");
	if (home == NULL)
	{
		print_error("cd: HOME not set");
		return ;
	}
	else
	{
		chdir(home);
		printf("%s\n", home);
	}	
	//ft_cd(home, data);
}

void ft_cd_father(void)
{
	char *current;
	char *father;

	current = getcwd(NULL, 0);
	father = ft_strrchr(current, '/');
	if (father == NULL)
	{
		print_error("cd: PWD not set");
		return ;
	}
	else
	{
		chdir(father);
		printf("%s\n", father);
	}
	//ft_cd(father, data);
}

void ft_cd_confirm(t_data data)
{
	printf("%s\n", "you are in the following directory:");
	printf("%s\n", data.envp_list->key);
	printf("%s\n", data.envp_list->value);
	return ;
}

void ft_cd_root(void)
{
	char *root;

	root = getenv("");
	if (root == NULL)
	{
		print_error("cd: ROOT not set");
		return ;
	}
	else
		chdir(root);
	//ft_cd(root, data);
}
