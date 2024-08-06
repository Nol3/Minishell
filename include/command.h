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

#endif
