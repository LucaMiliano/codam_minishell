/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpinas <cpinas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 15:03:37 by lpieck            #+#    #+#             */
/*   Updated: 2025/12/28 18:53:48 by cpinas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

// int add_history PARAMS(const char *);

t_shell g_shell;

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
	(void)ac;
	(void)av;

	g_shell.env = dup_envp(envp);
    g_shell.last_status = 0;

	setup_signals();	// install SIGINT/SIGQUIT
	prompt();			// run the shell loop, passing envp if needed for expansions later

	return (0);
}

