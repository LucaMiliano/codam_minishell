/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpinas <cpinas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/27 15:20:49 by cpinas            #+#    #+#             */
/*   Updated: 2026/02/11 20:41:19 by cpinas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>

static void	child_process(t_shell *shell, t_cmd *cmd, int in_fd, int out_fd)
{
	setup_signals_child();
	if (in_fd != STDIN_FILENO)
	{
		dup2(in_fd, STDIN_FILENO);
		close(in_fd);
	}
	if (out_fd != STDOUT_FILENO)
	{
		dup2(out_fd, STDOUT_FILENO);
		close(out_fd);
	}
	if (cmd->redirs)
		apply_redirections(cmd->redirs);
	exec_cmd(shell, cmd, STDIN_FILENO, STDOUT_FILENO);
	perror("exec_cmd");
	exit(1);
}

void	setup_pipe(t_cmd *cmd, int pipefd[2])
{
	if (cmd->next)
	{
		if (pipe(pipefd) == -1)
		{
			perror("pipe");
			exit(1);
		}
	}
	else
	{
		pipefd[0] = STDIN_FILENO;
		pipefd[1] = STDOUT_FILENO;
	}
}

static void	wait_for_children(void)
{
	int	status;

	while (wait(&status) > 0)
	{
		if (WIFEXITED(status))
			g_last_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			g_last_status = 128 + WTERMSIG(status);
	}
}

void	handle_child(t_shell *shell, t_cmd *cmd, int prev_fd, int write_fd)
{
	if (cmd->next && write_fd != STDOUT_FILENO)
		close(write_fd);
	child_process(shell, cmd, prev_fd, write_fd);
}

void	execute_pipeline(t_shell *shell, t_cmd *cmds)
{
	if (handle_parent_builtin(shell, cmds))
		return ;
	pipe_loop(shell, cmds, STDIN_FILENO);
	close_heredoc_fds(cmds);
	wait_for_children();
}
