/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_add_word.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpinas <cpinas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 03:16:12 by cpinas            #+#    #+#             */
/*   Updated: 2025/12/30 10:15:01 by cpinas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <string.h>

// char	**argv_add(char **argv, char *new_arg)
// {
// 	int i;
// 	int j;
// 	char **new_argv;

// 	i = 0;
// 	j = 0;
// 	while (argv && argv[i])
// 		i++;
// 	new_argv = malloc(sizeof(char *) *(i + 2));
// 	if(!new_argv)
// 		return (NULL);

// 	while (j < i)
// 	{
// 		new_argv[j] = argv[j];
// 		j++;
// 	}
// 	new_argv[i] = ft_strdup(new_arg);
// 	   if (!new_argv[i])
// 	{
// 		free(new_argv);
// 		return NULL;
// 	}
// 	new_argv[i + 1] = NULL;
// 	free(argv); // free old argv array (but not the string)
// 	return (new_argv);
// }

int	argv_add(t_cmd *cmd, char *word, int expandable)
{
	int		i;
	char	**new_argv;
	int		*new_exp;

	i = 0;
	while (cmd->argv && cmd->argv[i])
		i++;

	new_argv = malloc(sizeof(char *) * (i + 2));
	new_exp = malloc(sizeof(int) * (i + 1));
	if (!new_argv || !new_exp)
		return (0);

	for (int j = 0; j < i; j++)
	{
		new_argv[j] = cmd->argv[j];
		new_exp[j] = cmd->argv_expandable[j];
	}

	new_argv[i] = ft_strdup(word);
	if (!new_argv[i])
		return (0);
	new_argv[i + 1] = NULL;
	new_exp[i] = expandable;

	free(cmd->argv);
	free(cmd->argv_expandable);

	cmd->argv = new_argv;
	cmd->argv_expandable = new_exp;
	return (1);
}
