/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpieck <lpieck@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 21:48:51 by cpinas            #+#    #+#             */
/*   Updated: 2026/02/11 14:43:22 by lpieck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/readline.h>
#include <signal.h>
#include <unistd.h>

static void	sigint_heredoc(int sig)
{
	(void)sig;
	g_last_status = 130;
	write(1, "\n", 1);
	close(STDIN_FILENO);
}

void	setup_signals_heredoc(void)
{
	signal(SIGINT, sigint_heredoc);
	signal(SIGQUIT, SIG_IGN);
}

// void	sigint_handler_heredoc(int sig)
// {
// 	(void)sig;
// 	g_last_status = 130;
// 	write(1, "\n", 1);
// 	rl_replace_line("", 0);
// 	rl_on_new_line();
// 	rl_redisplay();
// }
