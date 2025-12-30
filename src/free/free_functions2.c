/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpinas <cpinas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 22:32:31 by cpinas            #+#    #+#             */
/*   Updated: 2025/12/30 10:38:15 by cpinas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_cmd_pipeline(t_cmd *cmd)
{
	while (cmd)
	{
		t_cmd *next_cmd = cmd->next;
		// Free argv
		if (cmd->argv_expandable)
			free(cmd->argv_expandable);

		if (cmd->argv)
		{
			for (int i = 0; cmd->argv[i]; i++)
				free(cmd->argv[i]);
			free(cmd->argv);
		}
		// Free redirections
		t_redir *r = cmd->redirs;
		while (r)
		{
			t_redir *next_r = r->next;
			if (r->target)
				free(r->target);
			free(r);
			r = next_r;
		}
		free(cmd);
		cmd = next_cmd;
	}
}
