/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpinas <cpinas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/27 15:23:51 by cpinas            #+#    #+#             */
/*   Updated: 2026/01/12 02:15:58 by cpinas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

t_redir	*redir_new(t_redir_type type, char *target, int expandable)
{
	t_redir	*redir;

	redir = malloc(sizeof(t_redir));
	if (!redir)
		return (NULL);
	redir->type = type;
	redir->target = ft_strdup(target);
	if (!redir->target)
	{
		free(redir);
		return (NULL);
	}
	redir->expandable = expandable;
	redir->fd = -1;
	redir->next = NULL;
	return (redir);
}

static void	open_and_dup(char *target, int flags, int std_fd)
{
	int	fd;

	fd = open(target, flags, 0644);
	if (fd < 0)
	{
		perror(target);
		exit(1);
	}
	dup2(fd, std_fd);
	close(fd);
}

static void	apply_heredoc(t_redir *redir)
{
	if (redir->fd >= 0)
	{
		dup2(redir->fd, STDIN_FILENO);
		close(redir->fd);
	}
}

void	apply_redirections(t_redir *redir)
{
	while (redir)
	{
		if (redir->type == R_IN)
			open_and_dup(redir->target, O_RDONLY, STDIN_FILENO);
		else if (redir->type == R_OUT)
			open_and_dup(redir->target,
				O_CREAT | O_WRONLY | O_TRUNC, STDOUT_FILENO);
		else if (redir->type == R_APPEND)
			open_and_dup(redir->target,
				O_CREAT | O_WRONLY | O_APPEND, STDOUT_FILENO);
		else if (redir->type == R_HEREDOC)
			apply_heredoc(redir);
		redir = redir->next;
	}
}
