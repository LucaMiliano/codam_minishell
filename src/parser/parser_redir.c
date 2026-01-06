/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpieck <lpieck@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 02:51:45 by cpinas            #+#    #+#             */
/*   Updated: 2026/01/06 17:09:12 by lpieck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <string.h>

// t_redir	*redir_new(t_redir_type type, char *target, int expandable);

void	cmd_add_redir(t_cmd *cmd, t_redir *redir)
{
	t_redir	*tmp;

	if (!cmd->redirs)
		cmd->redirs = redir;
	else
	{
		tmp = cmd->redirs;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = redir;
	}
}

// t_redir	*redir_new(t_redir_type type, char *target, int expandable)
// {
// 	t_redir *redir = malloc(sizeof(t_redir));
// 	if (!redir)
// 		return NULL;
// 	redir->type = type;
// 	redir->target = target; // pointer to token->value (we can strdup if needed)
// 	redir->expandable = expandable;
// 	redir->next = NULL;
// 	return redir;
// }

// t_redir	*redir_new(t_redir_type type, char *target, int expandable)
// {
// 	t_redir *redir = malloc(sizeof(t_redir));
// 	if (!redir)
// 		return NULL;

// 	redir->type = type;
// 	redir->target = strdup(target); // copy string
// 	if (!redir->target)
// 	{
// 		free(redir);
// 		return NULL;
// 	}
// 	redir->expandable = expandable;
// 	redir->next = NULL;
// 	return redir;
// }
