/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpinas <cpinas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 17:13:15 by cpinas            #+#    #+#             */
/*   Updated: 2026/01/12 00:40:00 by cpinas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

char	*expand_word(char *word)
{
	int		i;
	char	*result;

	i = 0;
	result = ft_strdup("");
	if (!result)
		return (NULL);
	while (word[i])
	{
		if (word[i] == '$')
			result = append_expanded_var(result, word, &i);
		else
		{
			result = append_char(result, word[i]);
			i++;
		}
		if (!result)
			return (NULL);
	}
	return (result);
}

static void	expand_argv(t_cmd *cmd)
{
	int		i;
	char	*expanded;

	i = 0;
	while (cmd->argv && cmd->argv[i])
	{
		if (cmd->argv_expandable[i])
		{
			expanded = expand_word(cmd->argv[i]);
			if (expanded)
			{
				free(cmd->argv[i]);
				cmd->argv[i] = expanded;
			}
		}
		i++;
	}
}

static void	expand_redirs(t_redir *r)
{
	char	*expanded;

	while (r)
	{
		if (r->expandable)
		{
			expanded = expand_word(r->target);
			if (expanded)
			{
				free(r->target);
				r->target = expanded;
			}
		}
		r = r->next;
	}
}

void	expand_pipeline(t_cmd *cmds)
{
	while (cmds)
	{
		expand_argv(cmds);
		expand_redirs(cmds->redirs);
		cmds = cmds->next;
	}
}
