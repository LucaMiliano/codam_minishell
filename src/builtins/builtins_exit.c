/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpinas <cpinas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/28 19:59:37 by cpinas            #+#    #+#             */
/*   Updated: 2025/12/28 20:02:15 by cpinas           ###   ########.fr       */
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
}

int builtin_exit(char **argv)
{
	long status = 0;

	// Print "exit" if interactive shell
	if (isatty(STDIN_FILENO))
		write(STDOUT_FILENO, "exit\n", 5);

	if (argv[1])
	{
		if (!is_number(argv[1]))
		{
			fprintf(stderr, "minishell: exit: %s: numeric argument required\n", argv[1]);
			exit(255);
		}
		status = atol(argv[1]);
		if (argv[2])
		{
			fprintf(stderr, "minishell: exit: too many arguments\n");
			return (1); // do not exit
		}
	}

	exit((int)status);
}
