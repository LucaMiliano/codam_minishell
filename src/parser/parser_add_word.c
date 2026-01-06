/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_add_word.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpieck <lpieck@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 03:16:12 by cpinas            #+#    #+#             */
/*   Updated: 2026/01/06 16:54:11 by lpieck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <string.h>

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
