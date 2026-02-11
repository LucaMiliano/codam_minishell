/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpinas <cpinas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/27 15:25:40 by cpinas            #+#    #+#             */
/*   Updated: 2026/02/11 19:55:26 by cpinas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/readline.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>
#include <termios.h>

static void	heredoc_child_process(t_shell *shell, int *pipefd, t_redir *redir)
{
	if (shell->saved_stdin >= 0)
		close(shell->saved_stdin);
	setup_signals_heredoc();
	close(pipefd[0]);
	redir->fd = pipefd[1];
	if (handle_heredoc(shell, redir) != 0)
	{
		close(pipefd[1]);
		exit(g_last_status);
	}
	close(pipefd[1]);
	exit(0);
}

static int	heredoc_parent_process(pid_t pid, int *pipefd, t_redir *redir)
{
	int	status;

	close(pipefd[1]);
	redir->fd = pipefd[0];
	signal(SIGINT, SIG_IGN);
	waitpid(pid, &status, 0);
	setup_signals_prompt();
	if (WIFSIGNALED(status))
	{
		g_last_status = 128 + WTERMSIG(status);
		close(redir->fd);
		redir->fd = -1;
		return (1);
	}
	if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
	{
		g_last_status = WEXITSTATUS(status);
		close(redir->fd);
		redir->fd = -1;
		return (1);
	}
	return (0);
}

static int	handle_redir_heredoc(t_shell *shell, t_redir *redir)
{
	int				pipefd[2];
	pid_t			pid;
	struct termios	saved_term;
	int				has_term;

	if (pipe(pipefd) == -1)
		return (1);
	has_term = (tcgetattr(STDIN_FILENO, &saved_term) == 0);
	pid = fork();
	if (pid == -1)
	{
		close(pipefd[0]);
		close(pipefd[1]);
		return (1);
	}
	if (pid == 0)
		heredoc_child_process(shell, pipefd, redir);
	if (has_term)
		tcsetattr(STDIN_FILENO, TCSANOW, &saved_term);
	return (heredoc_parent_process(pid, pipefd, redir));
}

int	prepare_heredocs(t_shell *shell, t_cmd *cmds)
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
				if (handle_redir_heredoc(shell, redir) != 0)
					return (1);
			}
			redir = redir->next;
		}
		cmd = cmd->next;
	}
	return (0);
}
