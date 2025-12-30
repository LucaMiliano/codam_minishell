/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpinas <cpinas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/27 15:20:49 by cpinas            #+#    #+#             */
/*   Updated: 2025/12/30 12:19:28 by cpinas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>

/*
** Executes a pipeline of commands with proper pipe chaining and redirections.
** cmds: head of t_cmd linked list
** envp: environment variables for execve
*/

// static void child_process(t_cmd *cmd, int in_fd, int out_fd, char **envp)
// {

// 	// If there is a previous pipe result, use it as stdin
// 	if (in_fd != STDIN_FILENO)
// 	{
// 		dup2(in_fd, STDIN_FILENO);
// 		close(in_fd);
// 	}

// 	// If this command should write to a pipe, set stdout
// 	if (out_fd != STDOUT_FILENO)
// 	{
// 		dup2(out_fd, STDOUT_FILENO);
// 		close(out_fd);
// 	}

// 	// Apply any redirections (<, >, >>, <</heredoc)
// 	if (cmd->redirs)
// 		apply_redirections(cmd->redirs);

// 	// Execute the command
// 	exec_cmd(cmd, STDIN_FILENO, STDOUT_FILENO, envp);

// 	// If exec_cmd returns, it failed
// 	perror("exec_cmd failed");
// 	exit(1);
// }

static void child_process(t_cmd *cmd, int in_fd, int out_fd)
{
	setup_signals_child();
	/* stdin from previous pipe */
	if (in_fd != STDIN_FILENO)
	{
		dup2(in_fd, STDIN_FILENO);
		close(in_fd);
	}

	/* stdout to next pipe */
	if (out_fd != STDOUT_FILENO)
	{
		dup2(out_fd, STDOUT_FILENO);
		close(out_fd);
	}

	/* Apply redirections (< > >> <<) */
	if (cmd->redirs)
		apply_redirections(cmd->redirs);

	/* Execute command (never returns on success) */
	exec_cmd(cmd, STDIN_FILENO, STDOUT_FILENO);

	/* If we reach here, exec failed */
	perror("exec_cmd");
	exit(1);
}


// void execute_pipeline(t_cmd *cmds, char **envp)
// {
// 	t_cmd *cmd = cmds;
// 	int prev_fd = STDIN_FILENO;
// 	int pipefd[2];
// 	pid_t pid;

// 	// SINGLE command, NO pipes, parent-only builtin
// 	if (cmds && !cmds->next)
// 	{
// 		if (ft_strncmp(cmds->argv[0], "cd", ft_strlen("cd") + 1) == 0 ||
// 			ft_strncmp(cmds->argv[0], "exit", ft_strlen("exit") + 1) == 0)
// 		{
// 			if (cmds->redirs)
// 				apply_redirections(cmds->redirs);
// 			exec_builtin(cmds, envp);
// 			return ;
// 		}
// 	}
// 	while (cmd)
// 	{
// 		// If there is a next command, create a pipe
// 		if (cmd->next)
// 		{
// 			if (pipe(pipefd) == -1)
// 			{
// 				perror("pipe");
// 				exit(1);
// 			}
// 		}
// 		else
// 		{
// 			pipefd[0] = STDIN_FILENO;
// 			pipefd[1] = STDOUT_FILENO;
// 		}

// 		pid = fork();
// 		if (pid < 0)
// 		{
// 			perror("fork");
// 			exit(1);
// 		}
// 		else if (pid == 0)
// 		{
// 			// Child: feed prev_fd into stdin, pipefd[1] into stdout
// 			child_process(cmd, prev_fd, pipefd[1], envp);
// 		}

// 		// Parent closes write end
// 		if (pipefd[1] != STDOUT_FILENO)
// 			close(pipefd[1]);

// 		// Parent closes previous read end (not needed anymore)
// 		if (prev_fd != STDIN_FILENO)
// 			close(prev_fd);

// 		// Next command reads from this pipe
// 		prev_fd = pipefd[0];

// 		cmd = cmd->next;
// 	}

// 	// Parent waits for all children
// 	while (wait(NULL) > 0)
// 		;
// }

void execute_pipeline(t_cmd *cmds)
{
	t_cmd	*cmd;
	int		prev_fd;
	int		pipefd[2];
	pid_t	pid;

	cmd = cmds;
	prev_fd = STDIN_FILENO;

	/* Parent-only builtins (single command, no pipes) */
	if (cmds && !cmds->next)
	{
		if (ft_strncmp(cmds->argv[0], "cd", ft_strlen("cd") + 1) == 0
			|| ft_strncmp(cmds->argv[0], "exit", ft_strlen("exit") + 1) == 0
			|| ft_strncmp(cmds->argv[0], "export", ft_strlen("export") + 1) == 0
			|| ft_strncmp(cmds->argv[0], "unset", ft_strlen("unset") + 1) == 0)
		{
			if (cmds->redirs)
				apply_redirections(cmds->redirs);
			g_shell.last_status = exec_builtin(cmds);
			return ;
		}
	}
	while (cmd)
	{
		if (cmd->next)
		{
			if (pipe(pipefd) == -1)
			{
				perror("pipe");
				return;
			}
		}
		else
		{
			pipefd[0] = STDIN_FILENO;
			pipefd[1] = STDOUT_FILENO;
		}
		pid = fork();
		if (pid == -1)
		{
			perror("fork");
			return;
		}
		if (pid == 0)
		{
			/* Child */
			child_process(cmd, prev_fd, pipefd[1]);
		}
		/* Parent */
		if (pipefd[1] != STDOUT_FILENO)
			close(pipefd[1]);
		if (prev_fd != STDIN_FILENO)
			close(prev_fd);
		prev_fd = pipefd[0];
		cmd = cmd->next;
	}
	// while (wait(NULL) > 0)
	// 	;

		int status;
	while (wait(&status) > 0)
	{
    	if (WIFEXITED(status))
        	g_shell.last_status = WEXITSTATUS(status);
    	else if (WIFSIGNALED(status))
        	g_shell.last_status = 128 + WTERMSIG(status);
	}
}
