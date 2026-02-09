/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpieck <lpieck@student.codam.nl>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/27 15:20:49 by cpinas            #+#    #+#             */
/*   Updated: 2026/02/09 17:35:06 by lpieck           ###   ########.fr       */
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

// static int	handle_parent_builtin(t_shell *shell, t_cmd *cmd)
// {
// 	debug_cmd(cmd); //debug
// 	if (cmd && !cmd->next
// 		&& (ft_strncmp(cmd->argv[0], "cd", 3) == 0
// 			|| ft_strncmp(cmd->argv[0], "exit", 5) == 0
// 			|| ft_strncmp(cmd->argv[0], "export", 7) == 0
// 			|| ft_strncmp(cmd->argv[0], "unset", 6) == 0))
// 	{
// 		if (cmd->redirs)
// 			apply_redirections(cmd->redirs);
// 		g_last_status = exec_builtin(cmd, shell);
// 		return (1);
// 	}
// 	return (0);
// }

// static int	handle_parent_builtin(t_shell *shell, t_cmd *cmd)
// {
// 	int saved_in;
// 	int saved_out;

// 	if (!cmd || cmd->next)
// 		return 0;
// 	save_stdio1(&saved_in, &saved_out);
// 	if (cmd->redirs)
// 		apply_redirections(cmd->redirs);

// 	if (!cmd->argv || !cmd->argv[0])
// 	{
// 		restore_stdio1(saved_in, saved_out);
// 		return 1;
// 	}
// 	if (ft_strncmp(cmd->argv[0], "cd", 3) == 0
// 		|| ft_strncmp(cmd->argv[0], "exit", 5) == 0
// 		|| ft_strncmp(cmd->argv[0], "export", 7) == 0
// 		|| ft_strncmp(cmd->argv[0], "unset", 6) == 0
// 		|| ft_strncmp(cmd->argv[0], "echo", 5) == 0) // echo
// 	{
// 		g_last_status = exec_builtin(cmd, shell);
// 		restore_stdio1(saved_in, saved_out);
// 		return 1;
// 	}
// 	restore_stdio1(saved_in, saved_out);
// 	return 0;
// }



static int	handle_parent_builtin(t_shell *shell, t_cmd *cmd)
{
    int	saved_in;
    int	saved_out;

    if (!cmd || cmd->next)
        return (0);
    if (!cmd->argv || !cmd->argv[0])
    {
        save_stdio1(&saved_in, &saved_out);
        if (cmd->redirs)
            apply_redirections(cmd->redirs);
        restore_stdio1(saved_in, saved_out);
        return (1);
    }
    if (ft_strncmp(cmd->argv[0], "cd", 3) == 0
        || ft_strncmp(cmd->argv[0], "exit", 5) == 0
        || ft_strncmp(cmd->argv[0], "export", 7) == 0
        || ft_strncmp(cmd->argv[0], "unset", 6) == 0
        || ft_strncmp(cmd->argv[0], "echo", 5) == 0)
    {
        save_stdio1(&saved_in, &saved_out);
        if (cmd->redirs)
            apply_redirections(cmd->redirs);
        g_last_status = exec_builtin(cmd, shell);
        restore_stdio1(saved_in, saved_out);
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
			g_last_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			g_last_status = 128 + WTERMSIG(status);
	}
}

// void	execute_pipeline(t_shell *shell, t_cmd *cmds)
// {
// 	t_cmd	*cmd;
// 	int		prev_fd;
// 	int		pipefd[2];
// 	pid_t	pid;

// 	// if (prepare_heredocs(shell, cmds) != 0)
// 	// 	return ;

// 	if (handle_parent_builtin(shell, cmds))
// 		return ;
// 	cmd = cmds;
// 	prev_fd = STDIN_FILENO;
// 	while (cmd)
// 	{
// 		setup_pipe(cmd, pipefd);
// 		pid = fork();
// 		if (pid == 0)
// 			child_process(shell, cmd, prev_fd, pipefd[1]);
// 		if (pipefd[1] != STDOUT_FILENO)
// 			close(pipefd[1]);
// 		if (prev_fd != STDIN_FILENO)
// 			close(prev_fd);
// 		prev_fd = pipefd[0];
// 		cmd = cmd->next;
// 	}
// 	wait_for_children();
// }

// ...existing code...

static void	close_heredoc_fds(t_cmd *cmds)
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

void	execute_pipeline(t_shell *shell, t_cmd *cmds)
{
    t_cmd	*cmd;
    int		prev_fd;
    int		pipefd[2];
    pid_t	pid;

    if (handle_parent_builtin(shell, cmds))
        return ;
    cmd = cmds;
    prev_fd = STDIN_FILENO;
    while (cmd)
    {
        setup_pipe(cmd, pipefd);
        pid = fork();
        if (pid == 0)
        {
            if (cmd->next && pipefd[0] != STDIN_FILENO)
                close(pipefd[0]);
            child_process(shell, cmd, prev_fd, pipefd[1]);
        }
        if (pipefd[1] != STDOUT_FILENO)
            close(pipefd[1]);
        if (prev_fd != STDIN_FILENO)
            close(prev_fd);
        prev_fd = pipefd[0];
        cmd = cmd->next;
    }
    if (prev_fd != STDIN_FILENO)
        close(prev_fd);
    close_heredoc_fds(cmds);
    wait_for_children();
}
