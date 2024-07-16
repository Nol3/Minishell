/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angcampo <angcampo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 11:39:31 by alcarden          #+#    #+#             */
/*   Updated: 2024/07/16 13:00:58 by angcampo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

typedef struct s_env_list
{
	char				*key;
	char				*value;
	struct s_env_list	*next;
}						t_env_list;

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
	t_env_list			*envp_list;
	t_token				*token_list;
	t_cmd				*cmd_list;
}						t_data;

void   parse_variables(char *line);

/*
Initializes data:
returns 1 if everything went ok, 
returns 0 if not.
@param data
@param envp
@return int
*/
int	initialize_data(t_data *data, char **envp);

#endif