/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpinas <cpinas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/27 15:25:40 by cpinas            #+#    #+#             */
/*   Updated: 2025/12/27 17:58:42 by cpinas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/readline.h>

/*
** HEREDOC EXPANSION RULES:
** - If delimiter was quoted:
**      -> NO expansion
** - If delimiter was unquoted:
**      -> Expand $VAR
** - Expansion happens per line
** - Expansion result is written to heredoc pipe
*/
static int handle_heredoc(t_redir *redir)
{
	int pipefd[2];
	char *line;

	if (pipe(pipefd) == -1)
		return -1;

	while (1)
	{
		line = readline("> ");
		if (!line) // EOF or Ctrl-D
			break;

		// FUTURE: heredoc expansion hook
		if (redir->expandable)
		{
			// line = expand_variables(line, env); // placeholder
		}

		if (ft_strncmp(line, redir->target, ft_strlen(redir->target) + 1) == 0)
		{
			free(line);
			break;
		}

		write(pipefd[1], line, ft_strlen(line));
		write(pipefd[1], "\n", 1);
		free(line);
	}

	close(pipefd[1]);
	redir->fd = pipefd[0]; // child will read from this
	return 0;
}


int prepare_heredocs(t_cmd *cmds)
{
	t_cmd *cmd;
	t_redir *redir;

	cmd = cmds;
	while (cmd)
	{
		redir = cmd->redirs;
		while (redir)
		{
			if (redir->type == R_HEREDOC)
			{
				if (handle_heredoc(redir) != 0)
					return -1;
			}
			redir = redir->next;
		}
		cmd = cmd->next;
	}
	return 0;
}


