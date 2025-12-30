/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpinas <cpinas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 20:49:56 by cpinas            #+#    #+#             */
/*   Updated: 2025/12/30 17:43:15 by cpinas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/readline.h>
#include <signal.h>
#include <unistd.h>

void	sigint_handler(int sig)
{
	(void)sig;

	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	setup_signals(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}
void setup_signals_child(void)
{
	signal(SIGINT, SIG_DFL);  // default behavior for child
	signal(SIGQUIT, SIG_DFL); // default behavior for child
}
// /*
// ** ======================
// ** CHILD PROCESS (EXEC)
// ** ======================
// ** Ctrl-C  → kill process
// ** Ctrl-\  → quit process
// */

// void setup_signals_child(void)
// {
// 	signal(SIGINT, SIG_DFL);
// 	signal(SIGQUIT, SIG_DFL);
// }

// /*
// ** ======================
// ** HEREDOC MODE
// ** ======================
// ** Ctrl-C  → abort heredoc
// */

// static void sigint_heredoc(int signo)
// {
// 	(void)signo;
// 	write(1, "\n", 1);
// 	exit(1);
// }

// void setup_signals_heredoc(void)
// {
// 	signal(SIGINT, sigint_heredoc);
// 	signal(SIGQUIT, SIG_IGN);
// }

static void	sigint_heredoc(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	exit(130);
}

void	setup_signals_heredoc(void)
{
	signal(SIGINT, sigint_heredoc);
	signal(SIGQUIT, SIG_IGN);
}

void	sigint_handler_heredoc(int sig) //new
{
	(void)sig;
	g_shell.last_status = 130;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}
