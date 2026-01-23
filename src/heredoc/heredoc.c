/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpieck <lpieck@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/27 15:25:40 by cpinas            #+#    #+#             */
/*   Updated: 2026/01/23 16:04:33 by lpieck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/readline.h>
#include <sys/wait.h>
#include <unistd.h>

static int	handle_heredoc(t_redir *redir)
{
	char	*line;
	char	*expanded;

	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (ft_strncmp(line, redir->target,
				ft_strlen(redir->target) + 1) == 0)
		{
			free(line);
			break ;
		}
		if (redir->expandable)
		{
			expanded = expand_variables(line);
			free(line);
			line = expanded;
		}
		write(redir->fd, line, ft_strlen(line));
		write(redir->fd, "\n", 1);
		free(line);
	}
	return (0);
}

static void	heredoc_child_process(int *pipefd, t_redir *redir)
{
	setup_signals_heredoc();
	close(pipefd[0]);
	redir->fd = pipefd[1];
	if (handle_heredoc(redir) != 0)
		exit(1);
	close(pipefd[1]);
	exit(0);
}

static int	heredoc_parent_process(pid_t pid, int *pipefd, t_redir *redir)
{
	int		status;

	close(pipefd[1]);
	redir->fd = pipefd[0];
	waitpid(pid, &status, 0);
	setup_signals();
	if (WIFSIGNALED(status))
	{
		g_shell.last_status = 128 + WTERMSIG(status);
		return (1);
	}
	if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
	{
		g_shell.last_status = WEXITSTATUS(status);
		return (1);
	}
	return (0);
}

static int	handle_redir_heredoc(t_redir *redir)
{
	int		pipefd[2];
	pid_t	pid;

	if (pipe(pipefd) == -1)
		return (1);
	pid = fork();
	if (pid == -1)
		return (1);
	if (pid == 0)
		heredoc_child_process(pipefd, redir);
	return (heredoc_parent_process(pid, pipefd, redir));
}

int	prepare_heredocs(t_cmd *cmds)
{
	t_cmd	*cmd;
	t_redir	*redir;

	cmd = cmds;
	while (cmd)
	{
		redir = cmd->redirs;
		while (redir)
		{
			if (redir->type == R_HEREDOC)
			{
				if (handle_redir_heredoc(redir) != 0)
					return (1);
			}
			redir = redir->next;
		}
		cmd = cmd->next;
	}
	return (0);
}
