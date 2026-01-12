/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpinas <cpinas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/27 15:25:40 by cpinas            #+#    #+#             */
/*   Updated: 2026/01/12 03:08:51 by cpinas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/readline.h>
#include <sys/wait.h>
#include <unistd.h>


static char *expand_variables(const char *line)
{
	char *res = ft_strdup(""); // start with empty string
	const char *p = line;

	while (*p)
	{
		if (*p == '$' && ft_isalpha(*(p + 1)))
		{
			p++;
			int start = p - line;
			while (ft_isalnum(*p) || *p == '_')
				p++;
			char *var = ft_substr(line, start, p - line);
			char *val = find_in_env(var);
			free(var);
			char *tmp = res;
			if (val != NULL)
				res = ft_strjoin(res, val);
			else
				res = ft_strdup(res);
			free(tmp);
		}
		else
		{
			char tmp[2] = {*p, 0};
			char *old = res;
			res = ft_strjoin(res, tmp);
			free(old);
			p++;
		}
	}
	return (res);
}

// static char *append_char(char *res, char c)
// {
// 	char tmp[2] = {c, 0};
// 	char *old = res;
// 	res = ft_strjoin(res, tmp);
// 	free(old);
// 	return res;
// }

// static char *append_var_value(char *res, const char *line, int start, int end)
// {
// 	char *var = ft_substr(line, start, end - start);
// 	char *val = find_in_env(var);
// 	free(var);
// 	char *old = res;
// 	if (val)
// 		res = ft_strjoin(res, val);
// 	else
// 		res = ft_strdup(res);
// 	free(old);
// 	return res;
// }

// static char *expand_variables(const char *line)
// {
// 	char *res = ft_strdup("");
// 	const char *p = line;

// 	while (*p)
// 	{
// 		if (*p == '$' && ft_isalpha(*(p + 1)))
// 		{
// 			p++;
// 			int start = p - line;
// 			while (ft_isalnum(*p) || *p == '_')
// 				p++;
// 			res = append_var_value(res, line, start, p - line);
// 		}
// 		else
// 		{
// 			res = append_char(res, *p);
// 			p++;
// 		}
// 		if (!res)
// 			return NULL;
// 	}
// 	return res;
// }

static int	handle_heredoc(t_redir *redir)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line)
			break;
		if (ft_strncmp(line, redir->target,
				ft_strlen(redir->target) + 1) == 0)
		{
			free(line);
			break;
		}
		if (redir->expandable)
		{
			char *expanded = expand_variables(line);
			free(line);
			line = expanded;
		}
		write(redir->fd, line, ft_strlen(line));
		write(redir->fd, "\n", 1);
		free(line);
	}
	return (0);
}

int	prepare_heredocs(t_cmd *cmds)
{
	t_cmd	*cmd;
	t_redir	*redir;
	int		pipefd[2];
	pid_t	pid;
	int		status;

	cmd = cmds;
	while (cmd)
	{
		redir = cmd->redirs;
		while (redir)
		{
			if (redir->type == R_HEREDOC)
			{
				if (pipe(pipefd) == -1)
					return (1);

				pid = fork();
				if (pid == -1)
					return (1);

				if (pid == 0)
				{
					/* CHILD: read heredoc, write to pipe */
					setup_signals_heredoc();
					close(pipefd[0]);
					redir->fd = pipefd[1];
					if (handle_heredoc(redir) != 0)
						exit(1);
					close(pipefd[1]);
					exit(0);
				}
				else
				{
					/* PARENT: keep read end */
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
				}
			}
			redir = redir->next;
		}
		cmd = cmd->next;
	}
	return (0);
}

