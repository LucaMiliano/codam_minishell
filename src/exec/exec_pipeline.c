/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpinas <cpinas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/27 15:20:49 by cpinas            #+#    #+#             */
/*   Updated: 2026/01/04 21:30:35 by cpinas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>

static void	child_process(t_cmd *cmd, int in_fd, int out_fd)
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
	exec_cmd(cmd, STDIN_FILENO, STDOUT_FILENO);
	perror("exec_cmd");
	exit(1);
}

static int	handle_parent_builtin(t_cmd *cmd)
{
	if (cmd && !cmd->next
		&& (ft_strncmp(cmd->argv[0], "cd", 3) == 0
			|| ft_strncmp(cmd->argv[0], "exit", 5) == 0
			|| ft_strncmp(cmd->argv[0], "export", 7) == 0
			|| ft_strncmp(cmd->argv[0], "unset", 6) == 0))
	{
		if (cmd->redirs)
			apply_redirections(cmd->redirs);
		g_shell.last_status = exec_builtin(cmd);
		return (1);
	}
	return (0);
}

static void	setup_pipe(t_cmd *cmd, int pipefd[2])
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
			g_shell.last_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			g_shell.last_status = 128 + WTERMSIG(status);
	}
}

void	execute_pipeline(t_cmd *cmds)
{
	t_cmd	*cmd;
	int		prev_fd;
	int		pipefd[2];
	pid_t	pid;

	if (handle_parent_builtin(cmds))
		return ;
	cmd = cmds;
	prev_fd = STDIN_FILENO;
	while (cmd)
	{
		setup_pipe(cmd, pipefd);
		pid = fork();
		if (pid == 0)
			child_process(cmd, prev_fd, pipefd[1]);
		if (pipefd[1] != STDOUT_FILENO)
			close(pipefd[1]);
		if (prev_fd != STDIN_FILENO)
			close(prev_fd);
		prev_fd = pipefd[0];
		cmd = cmd->next;
	}
	wait_for_children();
}
