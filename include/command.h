#ifndef COMMAND_H
# define COMMAND_H

# include "token.h"
# include <limits.h>
# include <stdarg.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

enum e_built_in
{
	B_ECHO = 0,
	B_CD = 1,
	B_PWD = 2,
	B_EXPORT = 3,
	B_UNSET = 4,
	B_ENV = 5,
	B_EXIT = 6,
	NOT_BUILT_IN = 7,
};

typedef struct s_redir
{
	char				*file;
	enum e_token_type	type;
	struct s_redir		*next;
	struct s_redir		*prev;
}	t_redir;

typedef struct s_redir_list
{
	t_redir				*first;
	t_redir				*last;
	int					size;
}	t_redir_list;

typedef struct s_cmd
{
	enum e_built_in		built_in;
	char				**args;
	char				**choosen_path;
	int					fd_in;
	int					fd_out;
	t_redir_list		*redir_list;
	struct s_cmd		*next;
	struct s_cmd		*prev;
}						t_cmd;

typedef struct s_cmd_list
{
	t_cmd				*first;
	t_cmd				*last;
	int					size;
}	t_cmd_list;

typedef struct s_envp_list
{
	char				*key;
	char				*value;
	struct s_envp_list	*next;
}						t_envp_list;

/*
PARSE/COMMANDS
*/

//cmd_list_utils.c

/*
Checks if a command list is empty
@return 1 if empty, 0 if not empty
*/
int				is_cmd_empty(t_cmd_list *list);

/*
Returns an initialized command list
*/
t_cmd_list		*init_cmd_list(t_cmd_list *list);

/*
Returns a new command node
*/
t_cmd			*new_cmd(char **args, t_redir_list *redir_list,
					enum e_built_in built_in);

/*
Adds a command node to the end of the list
*/
void			add_cmd_last(t_cmd_list *list, t_cmd *new);

/*
Frees the whole list
*/
void			free_cmd_list(t_cmd_list *list);

//cmd_utils.c

/*
Frees a double pointer char that is NULL terminated
*/
void			free_strs(char **strs);

//get_arg.c

/*
Returns a word from a combination of tokens from the token list.
Used for get_args and get_redir_list.
@param token double pointer so pointer can be modified
@param envp_list to expand the variables
*/
char			*get_arg(t_token **token, t_envp_list *envp_list);

//get_args.c

/*
Returns the needed args for the construction of the command node
@param token double pointer so pointer can be modifiedtypedef struct s_envp_list
{
	char				*key;
	char				*value;
	struct s_envp_list	*next;
}						t_envp_list;
@param args_size it's the max quantity of single char pointers for args
@param envp_list to expand the variables
*/
char			**get_args(t_token **token, int args_size,
					t_envp_list *envp_list);

//get_built_in.c

/*
@param command the command we want the built_in from
@return a built_in
*/
enum e_built_in	get_built_in(char *command);

//get_redir_list.c

/*
Returns a list of redirections
@param token double pointer so pointer can be modified
@param envp_list to expand the variables
*/
t_redir_list	*get_redir_list(t_token **token, t_envp_list *envp_list);

//redir_list_utils.c

/*
Checks if a redirection list is empty
@return 1 if empty, 0 if not empty
*/
int				is_redir_empty(t_redir_list *list);

/*
Returns an initialized redirection list
*/
t_redir_list	*init_redir_list(t_redir_list *list);

/*
Returns a new redirection node
*/
t_redir			*new_redir(char *file, enum e_token_type type);

/*
Adds a redirection node to the end of the list
*/
void			add_redir_last(t_redir_list *list, t_redir *new);

/*
Frees the whole list
*/
void			free_redir_list(t_redir_list *list);

#endif
