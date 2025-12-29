/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_add_word.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpinas <cpinas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 03:16:12 by cpinas            #+#    #+#             */
/*   Updated: 2025/12/22 00:22:07 by cpinas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <string.h>

char	**argv_add(char **argv, char *new_arg)
{
	int i;
	int j;
	char **new_argv;

	i = 0;
	j = 0;
	while (argv && argv[i])
		i++;
	new_argv = malloc(sizeof(char *) *(i + 2));
	if(!new_argv)
		return (NULL);

	while (j < i)
	{
		new_argv[j] = argv[j];
		j++;
	}
	new_argv[i] = ft_strdup(new_arg);
	   if (!new_argv[i])
	{
		free(new_argv);
		return NULL;
	}
	new_argv[i + 1] = NULL;
	free(argv); // free old argv array (but not the string)
	return (new_argv);
}


