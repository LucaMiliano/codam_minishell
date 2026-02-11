/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpieck <lpieck@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 13:37:58 by cpinas            #+#    #+#             */
/*   Updated: 2026/02/10 17:47:26 by lpieck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <unistd.h>

static int	handle_input(char *line)
{
	if (!line)
	{
		write(1, "exit\n", 5);
		return (0);
	}
	if (*line)
		add_history(line);
	if (builtin_history(line))
		return (2);
	return (1);
}

int	builtin_history(char *line)
{
	if (!ft_strncmp(line, "history -c", 10))
	{
		clear_history();
		write(1, "history cleared\n", 17);
		return (1);
	}
	return (0);
}

int	prompt(t_shell *shell)
{
	t_prompt		p;
	t_prompt_ctx	ctx;
	char			*line;
	t_cmd			*cmds;

	ft_bzero(&p, sizeof(t_prompt));
	ctx.is_tty = isatty(STDIN_FILENO);
	ctx.saved_stdin = dup(STDIN_FILENO);
	shell->saved_stdin = ctx.saved_stdin;
	shell->cur_prompt = &p;
	shell->cur_is_tty = ctx.is_tty;
	shell->cur_line = NULL;
	shell->cur_cmds = NULL;
	/* Line added underneath */
	setup_signals_prompt();
	if (build_prompt1(shell, &p, ctx.is_tty) == 0)
		return (0);
	line = get_prompt_line(&p, ctx.is_tty);
	if (!line)
	{
		prompt_exit(&p, ctx.is_tty, ctx.saved_stdin, 0);
		shell->saved_stdin = -1;
		shell->cur_prompt = NULL;
		return (0);
	}
	if (handle_line(line, &p, ctx.is_tty) != 1)
	{
		prompt_exit(&p, ctx.is_tty, ctx.saved_stdin, 1);
		shell->saved_stdin = -1;
		shell->cur_prompt = NULL;
		return (1);
	}
	cmds = create_cmds(line, &p, ctx.is_tty);
	if (!cmds)
	{
		prompt_exit(&p, ctx.is_tty, ctx.saved_stdin, 1);
		shell->saved_stdin = -1;
		shell->cur_prompt = NULL;
		free(line);
		return (1);
	}
	shell->cur_line = line;
	shell->cur_cmds = cmds;
	ctx.p = &p;
	ctx.line = line;
	return (execute_and_cleanup(shell, cmds, &ctx));
}

int	build_prompt1(t_shell *shell, t_prompt *p, int is_tty)
{
	if (!is_tty)
		return (1);
	p->cwd = get_current_directory();
	p->user = get_username(shell);
	p->host = get_hostname();
	color_prompt(p);
	return (1);
}

int	handle_line(char *line, t_prompt *p, int is_tty)
{
	int	ret;

	ret = handle_input(line);
	if (ret == 1)
		return (1);
	free(line);
	if (is_tty)
		free2_prompt(p);
	if (ret == 0)
		return (0);
	return (-1);
}
