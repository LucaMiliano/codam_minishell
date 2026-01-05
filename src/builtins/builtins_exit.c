/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpieck <lpieck@student.codam.nl>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/28 19:59:37 by cpinas            #+#    #+#             */
/*   Updated: 2026/01/05 14:11:01 by lpieck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

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

int	builtin_exit(char **argv)
{
	long	status;

	if (isatty(STDIN_FILENO))
		// write(STDOUT_FILENO, "exit\n", 5);
	if (!argv[1])
	{
		exit(g_shell.last_status);
	}
	if (!is_number(argv[1]))
	{
		write(STDERR_FILENO, "minishell: exit: ", 18);
		write(STDERR_FILENO, argv[1], ft_strlen(argv[1]));
		write(STDERR_FILENO, ": numeric argument required\n", 29);
		g_shell.last_status = 1;
		return (1);
	}
	if (argv[2])
	{
		write(STDERR_FILENO, "minishell: exit: too many arguments\n", 37);
		g_shell.last_status = 1;
		return (1);
	}
	status = ft_atol(argv[1]);
	exit((int)status);
}
