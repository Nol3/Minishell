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

// FILE DESCRIPTORS UTILS DEFINES
# define STDIN 0
# define STDOUT 1
# define STDERR 2
# define UNDEF_FD -2

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

int g_pack;

void	parse_variables(char *line);

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

//pipex funciones:
int 		ft_cmdlist_size(t_cmd *cmd_list);
int			ft_pipex(t_data data);
int			ft_exec_cmd(t_data *data, t_cmd *node, int cmd_number);
int			ft_fork(t_data *data, t_cmd *node, int cmd_number);
int			ft_child_process(t_data *data, t_cmd *node);
static void	child_process_redir(t_cmd *node);
void		ft_redir_fd_std(int fd, int std, int fd2);
//int		ft_is_builtin(t_data *data, char *str);
//int		ft_built_in(t_data *data, t_cmd *node);

//list_utils funciones:
char		**get_paths(char *envp[]);
char		*abs_bin_path(char *cmd, char **envp);
char		*ft_valid_cmd(char *cmd);

#endif
