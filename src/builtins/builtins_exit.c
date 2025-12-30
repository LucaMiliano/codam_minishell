/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpinas <cpinas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/28 19:59:37 by cpinas            #+#    #+#             */
/*   Updated: 2025/12/30 11:51:49 by cpinas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

static int is_number(const char *str)
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
}// no longer active if revision works maybe?

// int builtin_exit(char **argv)
// {
// 	long status = 0;

// 	// Print "exit" if interactive shell
// 	if (isatty(STDIN_FILENO))
// 		write(STDOUT_FILENO, "exit\n", 5);

// 	if (argv[1])
// 	{
// 		if (!is_number(argv[1]))
// 		{
// 			fprintf(stderr, "minishell: exit: %s: numeric argument required\n", argv[1]);
// 			exit(255);
// 		}
// 		status = atol(argv[1]);
// 		if (argv[2])
// 		{
// 			fprintf(stderr, "minishell: exit: too many arguments\n");
// 			return (1); // do not exit
// 		}
// 	}

// 	exit((int)status);
// }


int builtin_exit(char **argv)
{
	long status;

	// Print "exit" if interactive shell
	if (isatty(STDIN_FILENO))
		write(STDOUT_FILENO, "exit\n", 5);

	if (!argv[1])
	{
		/* No arguments: exit normally */
		exit(g_shell.last_status);
	}

	/* Argument provided */
	if (!is_number(argv[1]))
	{
		fprintf(stderr, "minishell: exit: %s: numeric argument required\n", argv[1]);
		g_shell.last_status = 1; // store non-zero status
		return (1); // do NOT exit shell
	}

	/* Too many arguments */
	if (argv[2])
	{
		fprintf(stderr, "minishell: exit: too many arguments\n");
		g_shell.last_status = 1;
		return (1);
	}

	status = ft_atol(argv[1]);
	/* Exit with given numeric status */
	exit((int)status);
}
