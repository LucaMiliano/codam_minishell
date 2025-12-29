/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpinas <cpinas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 03:52:23 by cpinas            #+#    #+#             */
/*   Updated: 2025/12/21 03:53:38 by cpinas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

void print_redirs(t_redir *redir)
{
	while (redir)
	{
		const char *type_str;

		if (redir->type == R_IN) type_str = "<";
		else if (redir->type == R_OUT) type_str = ">";
		else if (redir->type == R_APPEND) type_str = ">>";
		else if (redir->type == R_HEREDOC) type_str = "<<";
		else type_str = "?";

		printf("  Redir: %s -> '%s' (expandable=%d)\n", type_str, redir->target, redir->expandable);
		redir = redir->next;
	}
}

void print_cmd(t_cmd *cmd, int index)
{
	int i = 0;
	printf("--- Command %d ---\n", index);

	if (!cmd)
	{
		printf("NULL command\n");
		return;
	}

	if (cmd->argv)
	{
		while (cmd->argv[i])
		{
			printf(" argv[%d] = '%s'\n", i, cmd->argv[i]);
			i++;
		}
	}

	print_redirs(cmd->redirs);
	printf("-----------------\n");
}

void print_pipeline(t_cmd *head)
{
	int index = 0;
	t_cmd *current = head;

	while (current)
	{
		print_cmd(current, index);
		current = current->next;
		index++;
	}
}
