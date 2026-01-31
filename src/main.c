/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpinas <cpinas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 15:03:37 by lpieck            #+#    #+#             */
/*   Updated: 2026/01/29 14:39:24 by cpinas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <stdio.h> //debug

// int add_history PARAMS(const char *);

int g_last_status; // definition


// actually duplicating enviorment //
static char	**dup_envp(char **envp)
{
	int		i;
	char	**copy;

	i = 0;
	while (envp[i])
		i++;

	copy = malloc(sizeof(char *) * (i + 1));
	if (!copy)
		return (NULL);

	i = 0;
	while (envp[i])
	{
		copy[i] = ft_strdup(envp[i]);
		i++;
	}
	copy[i] = NULL;

	return (copy);
}

int main(int ac, char **av, char **envp)
{
	t_shell shell;
	(void)ac;
	(void)av;

	// shell->env = dup_envp(envp);
    // g_last_status = 0; step 1;
	shell.env = dup_envp(envp);
	g_last_status = 0;

	setup_signals();	// install SIGINT/SIGQUIT
	//  needs understanding code :disable_echoctl();  // makes sure we don't have gosting prompt behavior(not strictly wrong more clean)
	while (1)
	{
		if (prompt(&shell) == 0)			// run the shell loop, passing envp if needed for expansions later
			break ;
		// if (g_last_status == 130)
		// 	break ;
	// }
	if (g_last_status != 0)
	{
		shell.last_status = g_last_status;
		g_last_status = 0;
	}
	}
	// promt() -> promt(&shell); and free_env(shell.env) added/changed step 1
	free_env(shell.env); //***temorary shotdown to check segfault****
	return (0);
}

// #include <termios.h>

// static void	disable_echoctl(void)
// {
// 	struct termios	term;

// 	if (tcgetattr(STDIN_FILENO, &term) == -1)
// 		return ;
// 	term.c_lflag &= ~ECHOCTL;
// 	tcsetattr(STDIN_FILENO, TCSANOW, &term);
// }
// something like this for echoctl disable but really bs, if you ask me, we only need 90%
