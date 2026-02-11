/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpieck <lpieck@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 15:03:37 by lpieck            #+#    #+#             */
/*   Updated: 2026/02/11 17:44:36 by lpieck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <readline/history.h>

int g_last_status;

static char	**dup_envp(char **envp)
{
	int		i;
	int		j;
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
		if (!copy[i])
		{
			j = 0;
			while (j < i)
				free(copy[j++]);
			free(copy);
			return (NULL);
		}
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

int main(int ac, char **av, char **envp)
{
	t_shell	shell;

	(void)ac;
	(void)av;
	shell.env = dup_envp(envp);
	shell.saved_stdin = -1;
	shell.saved_stdio_in = -1;
	shell.saved_stdio_out = -1;
	shell.cur_line = NULL;
	shell.cur_cmds = NULL;
	shell.cur_prompt = NULL;
	shell.cur_is_tty = 0;
	g_last_status = 0;
	setup_signals_prompt();
	while (1)
	{
		if (prompt(&shell) == 0)
			break ;
		if (g_last_status != 0)
			shell.last_status = g_last_status;
	}
	if (shell.cur_cmds)
		free_cmd_pipeline((t_cmd *)shell.cur_cmds);
	if (shell.cur_line)
		free(shell.cur_line);
	if (shell.cur_is_tty && shell.cur_prompt)
		free_prompt((t_prompt *)shell.cur_prompt);
	if (shell.saved_stdio_in >= 0)
		close(shell.saved_stdio_in);
	if (shell.saved_stdio_out >= 0)
		close(shell.saved_stdio_out);
	if (shell.saved_stdin >= 0)
		close(shell.saved_stdin);
	free_env(shell.env);
	clear_history();
	return (g_last_status);
}
