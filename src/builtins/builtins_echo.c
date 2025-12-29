/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_echo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpinas <cpinas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/28 14:51:13 by cpinas            #+#    #+#             */
/*   Updated: 2025/12/28 19:51:28 by cpinas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>

static int is_n_option(char *arg)
{
	int i;

	if (!arg || arg[0] != '-')
		return 0;
	i = 1;
	while (arg[i] == 'n')
		i++;
	return (arg[i] == '\0');
}

int builtin_echo(char **argv)
{
	int i;
	int newline;

	i = 1;
	newline = 1;

	// Handle one or more -n options
	while (argv[i] && is_n_option(argv[i]))
	{
		newline = 0;
		i++;
	}
	// Print remaining arguments
	while (argv[i])
	{
		write(STDOUT_FILENO, argv[i], ft_strlen(argv[i]));
		if (argv[i + 1])
			write(STDOUT_FILENO, " ", 1);
		i++;
	}
	if (newline)
		write(STDOUT_FILENO, "\n", 1);

	return (0);
}


