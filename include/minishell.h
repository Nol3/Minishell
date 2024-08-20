#ifndef MINISHELL_H
# define MINISHELL_H

# include "defines.h"
# include "command.h"
# include "token.h"
# include "command.h"
# include "../libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# include <sys/ioctl.h>

typedef struct s_data
{
	char				*built_in_cmd[8];
	int					status;
	int					exit;
	char				**envp;
	t_envp_list			*envp_list;
	t_token_list		*token_list;
	t_cmd_list			*cmd_list;
	t_cmd				*current_cmd;
}						t_data;

extern int g_pack;

void			parse_variables(char *line);
/*
-----------------------------
UTILS
-----------------------------
*/

/*
Prints "Error\n" then prints str with another \n if str isn't empty
@param str
@return 0
*/
int				print_error(const char *str);

/*
Returns an initialized t_data if everything went ok,
returns NULL if not.
@param envp
@return int
*/
t_data			*get_initialized_data(char **envp);

/*
Liberates all data from the struct
*/
void			free_data(t_data *data);

/*
Compares 2 strings
@return 1 if equal, 0 if not
*/
int				strs_are_equal(char *str1, char *str2);

/*
@brief Inits console
*/
void			console_initialization(t_data *data);


/*
Updates the data->envp from the data->envp_list
*/
int				update_envp(t_data *data);

/*
-----------------------------
PARSE/TOKENS
-----------------------------
*/

//add_tokens_from_input.c

/*
It iterates through all the input string to add tokens
Returns 1 if ok
and returns 0 if not
@param data Fully initialized
@param input Any string
*/
int				add_tokens_from_input(t_data *data, char *input);

/*
-----------------------------
PARSE/LEXER
-----------------------------
*/

//validators_utils.c

/*
Given a token type, checks if it's a redirection or not
@return 1 if a redirection, 0 if not
*/
int				is_redir(int type);

/*
Gets the next or previous token that is not a white space
@param next 1 if next token, 0 if previous token
*/
t_token			*skip_spaces(t_token *token, int next);

//valid_token_list.c

/*
It iterates through all the token list to see if there are
any syntax errors.
@return 1 if syntax is ok, 0 if not
*/
int				valid_token_list(t_token_list *list);

/*
-----------------------------
PARSE/EXPANDER
-----------------------------
*/

/*
@param token with type ENV
@return value of the variable if it exists, empty string
if it doesn't
*/
char			*expanded_token(t_token *token, t_data *data);

/*
-----------------------------
PARSE/COMMANDS
-----------------------------
*/

//add_commands_from_input.c

/*
Adds tokens from input, returns 1 if ok
and returns 0 if not
@param data Fully initialized with tokens
*/
int				add_commands_from_input(t_data *data);

//get_arg.c

/*
Returns a word from a combination of tokens from the token list.
Used for get_args and get_redir_list.
@param token double pointer so pointer can be modified
@param data to expand the variables
*/
char			*get_arg(t_token **token, t_data *data);

//get_lists.c

/*
Fills the args + the redirection list
@param token double pointer so pointer can be modified
@param data to expand the variables
*/
void			get_lists(t_token **token, t_data *data, char **args,
					t_redir_list *redir_list);

/*
-----------------------------
PARSE/REDIRECTIONS
-----------------------------
*/

/*
Handles all redirections of the command list of data
@param data with a complete list of commands
@return 1 if ok, 0 if not
*/
int				handle_redirections(t_data *data);

/*
-----------------------------
PIPEX
-----------------------------
*/

/*
Executes the commands
@param data Fully initialized with tokens and commands
*/

void			print_data(t_data *data);
int				ft_pipex(t_data *data);
int				ft_exec_builtin(t_data *data);
int				ft_exec_cmd(t_data *data, int cmd_count);
int				ft_fork(t_data *data, int cmd_count);
int				ft_child_process(t_data *data);
void			ft_redir_fd_std(int fd, int std, int fd2);
//int			ft_is_builtin(t_data *data, char *str);
//int			ft_built_in(t_data *data, t_cmd *node);

//list_utils funciones:
char			**get_paths(char *envp[]);
char			*abs_bin_path(char *cmd, char **envp);
char			*ft_valid_cmd(char *cmd);
void			ft_free_matrix(char **envp);


//Meter las "char	*built_in_cmd[8];" en relación las funciones
//además de las funciones adicionales de cd, explorar como debería ir env
//built-in functions
//cd functions
int				cd(t_data *data);
//echo
int 			echo(t_data *data);
//env
void			ft_env(t_data *data);
int				env(t_data *data);
//exit
int				ft_exit(t_data *data);
//export
int				ft_export(t_data *data);
//pwd
int				ft_pwd(t_data *data);
//unset
int				ft_unset(t_data *data);

//signals
void			ft_signals(void);

#endif
