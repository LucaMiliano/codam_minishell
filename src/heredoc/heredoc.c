/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpieck <lpieck@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/27 15:25:40 by cpinas            #+#    #+#             */
/*   Updated: 2026/02/06 16:54:08 by lpieck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/readline.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>
#include <termios.h>

// static char *expand_variables(t_shell *shell, const char *line)
// {
// 	char *res = ft_strdup(""); // start with empty string
// 	const char *p = line;

// 	while (*p)
// 	{
// 		if (*p == '$' && ft_isalpha(*(p + 1)))
// 		{
// 			p++;
// 			int start = p - line;
// 			while (ft_isalnum(*p) || *p == '_')
// 				p++;
// 			char *var = ft_substr(line, start, p - line);
// 			char *val = find_in_env(shell, var);
// 			free(var);
// 			char *tmp = res;
// 			if (val != NULL)
// 				res = ft_strjoin(res, val);
// 			else
// 				res = ft_strdup(res);
// 			free(tmp);
// 		}
// 		else
// 		{
// 			char tmp[2] = {*p, 0};
// 			char *old = res;
// 			res = ft_strjoin(res, tmp);
// 			free(old);
// 			p++;
// 		}
// 	}
// 	return (res);
// }

// static int	handle_heredoc(t_shell *shell, t_redir *redir)
// {
// 	char	*line;

// 	while (1)
// 	{
// 		line = readline("> ");
// 		// small edit 102
// 		if (!line)
// 		{
// 			//try everything instead of return 1; error please
// 			if (g_last_status) //maybe fix 3 sentences //
// 				return (1);
// 			break ;
// 		}
// 		if (ft_strncmp(line, redir->target,
// 				ft_strlen(redir->target) + 1) == 0)
// 		{
// 			free(line);
// 			break ;
// 		}
// 		if (redir->expandable)
// 		{
// 			char *expanded = expand_variables(shell, line);
// 			free(line);
// 			line = expanded;
// 		}
// 		write(redir->fd, line, ft_strlen(line));
// 		write(redir->fd, "\n", 1);
// 		free(line);
// 	}
// 	return (0);
// }

// int	prepare_heredocs(t_shell *shell, t_cmd *cmds)
// {
// 	t_cmd	*cmd;
// 	t_redir	*redir;
// 	int		pipefd[2];
// 	pid_t	pid;
// 	int		status;

// 	cmd = cmds;
// 	while (cmd)
// 	{
// 		redir = cmd->redirs;
// 		while (redir)
// 		{
// 			if (redir->type == R_HEREDOC)
// 			{
// 				if (pipe(pipefd) == -1)
// 					return (1);

// 				pid = fork();
// 				if (pid == -1)
// 					return (1);

// 				if (pid == 0)
// 				{
// 					/* CHILD: read heredoc, write to pipe */
// 					setup_signals_heredoc();
// 					close(pipefd[0]);
// 					redir->fd = pipefd[1];
// 					if (handle_heredoc(shell, redir) != 0)
// 						exit(130);// exit(1);
// 					close(pipefd[1]);
// 					exit(0);
// 				}
// 				else
// 				{
// 					/* PARENT: keep read end */
// 					close(pipefd[1]);
// 					redir->fd = pipefd[0];
// 					waitpid(pid, &status, 0);
// 					setup_signals();
// 					if (WIFEXITED(status) && WEXITSTATUS(status) == 130)
// 					{
// 						g_last_status = 130;
// 						return (1); // abort command, prompt loop will redraw ONCE
// 					}

// 					// waitpid(pid, &status, 0);
// 					// setup_signals();

// 					// if (WIFSIGNALED(status))
// 					// {
	// 					// 	g_last_status = 128 + WTERMSIG(status);
	// 					// 	return (1);
	// 					// }
	// 					if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
	// 					{
		// 						g_last_status = WEXITSTATUS(status);
		// 						return (1);
	// 					}
	// 				}
	// 			}
	// 			redir = redir->next;
	// 		}
	// 		cmd = cmd->next;
	// 	}
	// 	return (0);
	// }
	static char	*append_variable(t_shell *shell, char *res, const char **p, const char *line)
	{
		char	*var;
		char	*val;
		char	*old;
		int		start;

		(*p)++;
		start = *p - line;
		while (ft_isalnum(**p) || **p == '_')
			(*p)++;
		var = ft_substr(line, start, *p - line - start);
		val = find_in_env(shell, var);
		old = res;
		if (val != NULL)
			res = ft_strjoin(res, val);
		else
			res = ft_strdup(res);
		free(old);
		free(var);
		return (res);
	}

	static char	*expand_variables(t_shell *shell, const char *line)
	{
		char		*res;
		const char	*p;

		res = ft_strdup("");
		if (!res)
			return (NULL);
		p = line;
		while (*p)
		{
			if (*p == '$' && ft_isalpha(*(p + 1)))
				res = append_variable(shell, res, &p, line);
			else
			{
				res = append_char(res, *p);
				p++;
			}
		}
		return (res);
	}

static int	handle_heredoc(t_shell *shell, t_redir *redir)
{
	char	*line;
	char	*expanded;

	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			printf("[DEBUG] EOF non working version detected\n"); //debug
			break ;
		}
		if (ft_strncmp(line, redir->target,
				ft_strlen(redir->target) + 1) == 0)
		{
			free(line);
			break ;
		}
		// if (ft_strlen(line) == ft_strlen(redir->target)
   		// 	&& ft_strncmp(line, redir->target, ft_strlen(redir->target)) == 0)
		// {
		// 	free(line);
		// 	break;
		// }
		if (redir->expandable)
		{
			expanded = expand_variables(shell, line);
			free(line);
			line = expanded;
		}
		write(redir->fd, line, ft_strlen(line));
		write(redir->fd, "\n", 1);
		free(line);
	}
	return (0);
}

static void	heredoc_child_process(t_shell *shell, int *pipefd, t_redir *redir)
{
	printf("[HEREDOC CHILD] pid=%d pgrp=%d\n",
	   getpid(), getpgrp()); // two lines above temp debug
	setup_signals_heredoc();
	close(pipefd[0]);
	redir->fd = pipefd[1];
	if (handle_heredoc(shell, redir) != 0)
		exit(1);
	close(pipefd[1]);
	exit(0);
}

static int	heredoc_parent_process(pid_t pid, int *pipefd, t_redir *redir)
{
	int		status;

	close(pipefd[1]);
	redir->fd = pipefd[0];
	printf("[PARENT] pid=%d pgrp=%d\n",
		getpid(), getpgrp()); // two sentences above debug
	signal(SIGINT, SIG_IGN);
	waitpid(pid, &status, 0);
	// tcsetpgrp(STDIN_FILENO, getpgrp());

	setup_signals();
	if (WIFSIGNALED(status))
	{
		g_last_status = 128 + WTERMSIG(status);
		return (1);
	}
	if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
	{
		g_last_status = WEXITSTATUS(status);
		return (1);
	}
	return (0);
}

// static int heredoc_parent_process(pid_t pid, int *pipefd, t_redir *redir)
// {
// 	int status;

// 	close(pipefd[1]);
// 	redir->fd = pipefd[0];

// 	signal(SIGINT, SIG_IGN);
// 	signal(SIGQUIT, SIG_IGN);
// 	signal(SIGTSTP, SIG_IGN);

// 	printf("[PARENT] pid=%d pgrp=%d\n",
// 	getpid(), getpgrp()); // two sentences above debug

// 	waitpid(pid, &status, 0);

// 	tcsetpgrp(STDIN_FILENO, getpid());
// 	setup_signals();

// 	if (WIFSIGNALED(status))
// 	{
// 		g_last_status = 128 + WTERMSIG(status);
// 		return (1);
// 	}
// 	if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
// 	{
// 		g_last_status = WEXITSTATUS(status);
// 		return (1);
// 	}
// 	return (0);
// }


// static int	handle_redir_heredoc(t_shell *shell, t_redir *redir)
// {
// 	int		pipefd[2];
// 	pid_t	pid;

// 	if (pipe(pipefd) == -1)
// 		return (1);
// 	pid = fork();
// 	if (pid == -1)
// 		return (1);
// 	if (pid == 0)
// 		heredoc_child_process(shell, pipefd, redir);
// 	return (heredoc_parent_process(pid, pipefd, redir));
// }


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
        return (1);
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
