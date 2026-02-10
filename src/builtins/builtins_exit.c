/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpinas <cpinas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/28 19:59:37 by cpinas            #+#    #+#             */
/*   Updated: 2026/01/25 19:09:52 by cpinas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <unistd.h>
#include <readline/history.h>

static int	is_number(const char *str)
{
	if (!str || !*str)
		return (0);
	if (*str == '+' || *str == '-')
		str++;
	while (*str)
	{
		if (!isdigit((unsigned char)*str))
			return (0);
		str++;
	}
	return (1);
}

static void	cleanup_and_exit(t_shell *shell, int status)
{
	if (shell)
	{
		if (shell->cur_cmds)
			free_cmd_pipeline((t_cmd *)shell->cur_cmds);
		if (shell->cur_line)
			free(shell->cur_line);
		if (shell->cur_is_tty && shell->cur_prompt)
			free_prompt((t_prompt *)shell->cur_prompt);
		if (shell->saved_stdio_in >= 0)
			close(shell->saved_stdio_in);
		if (shell->saved_stdio_out >= 0)
			close(shell->saved_stdio_out);
		if (shell->saved_stdin >= 0)
			close(shell->saved_stdin);
		if (shell->env)
			free_env(shell->env);
	}
	clear_history();
	exit(status);
}

int	builtin_exit(t_shell *shell, char **argv)
{
	long	status;

	if (isatty(STDIN_FILENO))
		write(STDOUT_FILENO, "exit\n", 5);
	if (!argv[1])
		cleanup_and_exit(shell, g_last_status);
	if (!is_number(argv[1]))
	{
		write(STDERR_FILENO, "minishell: exit: ", 18);
		write(STDERR_FILENO, argv[1], ft_strlen(argv[1]));
		write(STDERR_FILENO, ": numeric argument required\n", 29);
		cleanup_and_exit(shell, 2);
	}
	if (argv[2])
	{
		write(STDERR_FILENO, "minishell: exit: too many arguments\n", 37);
		g_last_status = 1;
		return (1);
	}
	status = ft_atol(argv[1]);
	cleanup_and_exit(shell, (int)status);
	return (0);
}
