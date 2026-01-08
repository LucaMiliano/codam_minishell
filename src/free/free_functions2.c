/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpieck <lpieck@student.codam.nl>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 22:32:31 by cpinas            #+#    #+#             */
/*   Updated: 2026/01/08 15:13:17 by lpieck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_argv(char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
	{
		free(argv[i]);
		i++;
	}
	free(argv);
}

static void	free_redirs(t_redir *r)
{
	t_redir	*next_r;

	while (r)
	{
		next_r = r->next;
		if (r->target)
			free(r->target);
		free(r);
		r = next_r;
	}
}

void	free_cmd_pipeline(t_cmd *cmd)
{
	t_cmd	*next_cmd;

	while (cmd)
	{
		next_cmd = cmd->next;
		if (cmd->argv_expandable)
			free(cmd->argv_expandable);
		if (cmd->argv)
			free_argv(cmd->argv);
		free_redirs(cmd->redirs);
		free(cmd);
		cmd = next_cmd;
	}
}
