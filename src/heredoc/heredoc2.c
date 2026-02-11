/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpieck <lpieck@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 17:36:06 by lpieck            #+#    #+#             */
/*   Updated: 2026/02/11 17:36:19 by lpieck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/readline.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>
#include <termios.h>

static char	*append_variable(t_shell *shell, char *res,
	const char **p, const char *line)
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
	if (!var)
	{
		free(res);
		return (NULL);
	}
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
		if (!res)
			return (NULL);
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
			if (g_last_status == 130)
				return (1);
			break ;
		}
		if (ft_strncmp(line, redir->target,
				ft_strlen(redir->target) + 1) == 0)
		{
			free(line);
			break ;
		}
		if (redir->expandable)
		{
			expanded = expand_variables(shell, line);
			free(line);
			if (!expanded)
				return (1);
			line = expanded;
		}
		write(redir->fd, line, ft_strlen(line));
		write(redir->fd, "\n", 1);
		free(line);
	}
	return (0);
}
