/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcarden <alcarden@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 16:31:02 by alcarden          #+#    #+#             */
/*   Updated: 2024/08/21 18:23:40 by alcarden         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	ctr_c(int sig)
{
	(void)sig;
	if (g_pack == 0)
	{
		rl_on_new_line();
		rl_redisplay();
		rl_replace_line("", 0);
		write(1, "\n", 1);
		rl_on_new_line();
		rl_redisplay();
		rl_replace_line("", 0);
	}
	else if (g_pack == 1)
	{
		write(1, "\n", 1);
		rl_replace_line("", 1);
		rl_on_new_line();
	}
}

static void	ctr_backslash(int sig)
{
	(void)sig;
	write(1, "Quit (core dumped)\n", 19);
	signal(SIGQUIT, SIG_DFL);
	raise(SIGQUIT);
}

void	ft_signals(void)
{
	signal(SIGINT, ctr_c);
	signal(SIGTSTP, SIG_IGN);
	signal(SIGQUIT, ctr_backslash);
}
