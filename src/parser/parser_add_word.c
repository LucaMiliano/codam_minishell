/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_add_word.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpinas <cpinas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 03:16:12 by cpinas            #+#    #+#             */
/*   Updated: 2026/02/11 20:24:12 by cpinas           ###   ########.fr       */
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

static int	alloc_argv_arrays(char ***new_argv, int **new_exp, int size)
{
	*new_argv = malloc(sizeof(char *) * (size + 1));
	if (!*new_argv)
		return (0);
	*new_exp = malloc(sizeof(int) * size);
	if (!*new_exp)
	{
		free(*new_argv);
		return (0);
	}
	return (1);
}

static void	copy_existing_args(t_cmd *cmd, char **new_argv,
								int *new_exp, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		new_argv[i] = cmd->argv[i];
		new_exp[i] = cmd->argv_expandable[i];
		i++;
	}
}

static t_cmd	*argv_extend(t_cmd *cmd, int cur_count,
							char *word, int exp)
{
	char	**new_argv;
	int		*new_exp;

	if (!alloc_argv_arrays(&new_argv, &new_exp, cur_count + 1))
		return (NULL);
	copy_existing_args(cmd, new_argv, new_exp, cur_count);
	new_argv[cur_count] = ft_strdup(word);
	if (!new_argv[cur_count])
	{
		free(new_argv);
		free(new_exp);
		return (NULL);
	}
	new_argv[cur_count + 1] = NULL;
	new_exp[cur_count] = exp;
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
