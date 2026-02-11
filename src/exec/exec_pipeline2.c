/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpinas <cpinas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 19:32:50 by cpinas            #+#    #+#             */
/*   Updated: 2026/02/11 19:45:15 by cpinas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>

void	save_and_redirect1(t_shell *shell, t_cmd *cmd,\
		int *saved_in, int *saved_out)
{
	save_stdio1(saved_in, saved_out);
	shell->saved_stdio_in = *saved_in;
	shell->saved_stdio_out = *saved_out;
	if (cmd->redirs)
		apply_redirections(cmd->redirs);
}

void	restore_and_reset1(t_shell *shell, int saved_in, int saved_out)
{
	restore_stdio1(saved_in, saved_out);
	shell->saved_stdio_in = -1;
	shell->saved_stdio_out = -1;
}

int	handle_parent_builtin(t_shell *shell, t_cmd *cmd)
{
	int	saved_in;
	int	saved_out;

	if (!cmd || cmd->next)
		return (0);
	if (!cmd->argv || !cmd->argv[0])
	{
		save_and_redirect1(shell, cmd, &saved_in, &saved_out);
		restore_stdio1(saved_in, saved_out);
		return (1);
	}
	if (ft_strncmp(cmd->argv[0], "cd", 3) == 0
		|| ft_strncmp(cmd->argv[0], "exit", 5) == 0
		|| ft_strncmp(cmd->argv[0], "export", 7) == 0
		|| ft_strncmp(cmd->argv[0], "unset", 6) == 0
		|| ft_strncmp(cmd->argv[0], "echo", 5) == 0)
	{
		save_and_redirect1(shell, cmd, &saved_in, &saved_out);
		g_last_status = exec_builtin(cmd, shell);
		restore_and_reset1(shell, saved_in, saved_out);
		return (1);
	}
	return (0);
}

void	close_heredoc_fds(t_cmd *cmds)
{
	t_cmd	*cmd;
	t_redir	*redir;

	cmd = cmds;
	while (cmd)
	{
		redir = cmd->redirs;
		while (redir)
		{
			if (redir->type == R_HEREDOC && redir->fd >= 0)
			{
				close(redir->fd);
				redir->fd = -1;
			}
			redir = redir->next;
		}
		cmd = cmd->next;
	}
}

void	pipe_loop(t_shell *shell, t_cmd *cmd, int prev_fd)
{
	int		pipefd[2];
	pid_t	pid;

	while (cmd)
	{
		setup_pipe(cmd, pipefd);
		pid = fork();
		if (pid == 0)
			handle_child(shell, cmd, prev_fd, pipefd[1]);
		if (pipefd[1] != STDOUT_FILENO)
			close(pipefd[1]);
		if (prev_fd != STDIN_FILENO)
			close(prev_fd);
		prev_fd = pipefd[0];
		cmd = cmd->next;
	}
	if (prev_fd != STDIN_FILENO)
		close(prev_fd);
}
