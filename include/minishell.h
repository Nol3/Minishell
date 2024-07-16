#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_token
{
	int				key;
	char			*content;
	int				len;
	struct s_token	*next;
}	t_token;

typedef struct s_envp_list
{
	char				*key;
	char				*value;
	struct s_envp_list	*next;
}						t_envp_list;

typedef struct s_cmd
{
	char				**command;
	char				**choosen_path;
	int					fd_in;
	int					fd_out;
	struct s_cmd		*next;
}						t_cmd;

typedef struct s_data
{
	char				*built_in_cmd[8];
	int					status;
	int					exit;
	char				**envp;
	t_envp_list			*envp_list;
	t_token				*token_list;
	t_cmd				*cmd_list;
}						t_data;

/*
Prints "Error\n" then prints str with another \n if str isn't empty
@param str
@return 0
*/
int		print_error(const char *str);

/*
Returns an initialized t_data if everything went ok,
returns NULL if not.
@param envp
@return int
*/
t_data	*get_initialized_data(char **envp);

/*
Liberates all data from the struct
*/
void	free_data(t_data *data);

/*
Inits console
*/
void	console_initialization(t_data *data);

/*
Adds tokens from input, returns 1 if ok
and returns 0 if not
@param data Fully initialized
@param input Any string
*/
int		add_tokens_from_input(t_data *data, char *input);

/*
Adds tokens from input, returns 1 if ok
and returns 0 if not
@param data Fully initialized with tokens
*/
int		add_commands_from_input(t_data *data);

/*
Executes the commands
@param data Fully initialized with tokens and commands
*/
void	ft_pipex(t_data *data);

#endif
