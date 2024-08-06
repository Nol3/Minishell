#ifndef MINISHELL_H
# define MINISHELL_H

# include "command.h"
# include "token.h"
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

typedef struct s_envp_list
{
	char				*key;
	char				*value;
	struct s_envp_list	*next;
}						t_envp_list;

typedef struct s_data
{
	char				*built_in_cmd[8];
	int					status;
	int					exit;
	char				**envp;
	t_envp_list			*envp_list;
	t_token_list		*token_list;
	t_cmd_list			*cmd_list;
}						t_data;

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
@brief Inits console
*/
void			console_initialization(t_data *data);

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
char			*expanded_token(t_token *token, t_envp_list *list);

/*
-----------------------------
PARSE/COMMANDS
-----------------------------
*/

/*
Adds tokens from input, returns 1 if ok
and returns 0 if not
@param data Fully initialized with tokens
*/
int				add_commands_from_input(t_data *data);

/*
-----------------------------
PIPEX
-----------------------------
*/

/*
Executes the commands
@param data Fully initialized with tokens and commands
*/
void			ft_pipex(t_data *data);

#endif
