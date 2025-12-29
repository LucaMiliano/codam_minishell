/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpinas <cpinas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/27 15:23:51 by cpinas            #+#    #+#             */
/*   Updated: 2025/12/28 11:52:35 by cpinas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

t_redir *redir_new(t_redir_type type, char *target, int expandable)
{
	t_redir *redir = malloc(sizeof(t_redir));
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
	redir->fd = -1;   // INIT HERE
	redir->next = NULL;
	return (redir);
}

void apply_redirections(t_redir *redir)
{
	int fd;

	while (redir)
	{
		if (redir->type == R_IN)
		{
			fd = open(redir->target, O_RDONLY);
			if (fd < 0)
			{
				perror(redir->target);
				exit(1);
			}
			dup2(fd, STDIN_FILENO);
			close(fd);
		}
		else if (redir->type == R_OUT)
		{
			fd = open(redir->target, O_CREAT | O_WRONLY | O_TRUNC, 0644);
			if (fd < 0)
			{
				perror(redir->target);
				exit(1);
			}
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		else if (redir->type == R_APPEND)
		{
			fd = open(redir->target, O_CREAT | O_WRONLY | O_APPEND, 0644);
			if (fd < 0)
			{
				perror(redir->target);
				exit(1);
			}
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		else if (redir->type == R_HEREDOC)
		{
			if (redir->fd >= 0)
			{
				dup2(redir->fd, STDIN_FILENO);
				close(redir->fd);
			}
		}

		redir = redir->next;
	}
}
