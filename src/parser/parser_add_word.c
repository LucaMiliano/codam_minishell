/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_add_word.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpieck <lpieck@student.codam.nl>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 03:16:12 by cpinas            #+#    #+#             */
/*   Updated: 2026/01/07 12:52:48 by lpieck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <string.h>

static int	argv_count(t_cmd *cmd)
{
	int	count;

	count = 0;
	while (cmd->argv && cmd->argv[count])
		count++;
	return (count);
}

static t_cmd	*argv_extend(t_cmd *cmd, int current_count, char *word, int expandable)
{
	char	**new_argv;
	int		*new_exp;
	int		i;

	new_argv = malloc(sizeof(char *) * (current_count + 2));
	if (!new_argv)
		return (NULL);
	new_exp = malloc(sizeof(int) * (current_count + 1));
	if (!new_exp)
		return (free(new_argv), NULL);
	i = 0;
	while (i < current_count)
	{
		new_argv[i] = cmd->argv[i];
		new_exp[i] = cmd->argv_expandable[i];
		i++;
	}
	new_argv[i] = ft_strdup(word);
	if (!new_argv[i])
		return (free(new_argv), free(new_exp), NULL);
	new_argv[i + 1] = NULL;
	new_exp[i] = expandable;
	free(cmd->argv);
	free(cmd->argv_expandable);
	cmd->argv = new_argv;
	cmd->argv_expandable = new_exp;
	return (cmd);
}

t_cmd	*argv_add(t_cmd *cmd, char *word, int expandable)
{
	int	current_count;

	current_count = argv_count(cmd);
	return (argv_extend(cmd, current_count, word, expandable));
}
