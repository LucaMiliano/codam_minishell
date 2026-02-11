/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpinas <cpinas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 13:37:58 by cpinas            #+#    #+#             */
/*   Updated: 2026/02/11 20:42:50 by cpinas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <unistd.h>

int	handle_input(char *line)
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

static int	prompt_init(t_shell *shell, t_prompt *p, t_prompt_ctx *ctx)
{
	ft_bzero(p, sizeof(t_prompt));
	ctx->is_tty = isatty(STDIN_FILENO);
	ctx->saved_stdin = dup(STDIN_FILENO);
	if (ctx->saved_stdin < 0)
		return (1);
	shell->saved_stdin = ctx->saved_stdin;
	shell->cur_prompt = p;
	shell->cur_is_tty = ctx->is_tty;
	shell->cur_line = NULL;
	shell->cur_cmds = NULL;
	setup_signals_prompt();
	return (0);
}

static int	get_and_validate_line(t_shell *shell,
				t_prompt *p, t_prompt_ctx *ctx, char **line)
{
	*line = get_prompt_line(p, ctx->is_tty);
	if (!*line)
	{
		prompt_exit(p, ctx->is_tty, ctx->saved_stdin, 0);
		shell->saved_stdin = -1;
		shell->cur_prompt = NULL;
		return (0);
	}
	if (handle_line(*line, p, ctx->is_tty) != 1)
	{
		prompt_exit(p, ctx->is_tty, ctx->saved_stdin, 1);
		shell->saved_stdin = -1;
		shell->cur_prompt = NULL;
		return (1);
	}
	return (2);
}

static t_cmd	*parse_line(t_shell *shell,
					t_prompt *p, t_prompt_ctx *ctx, char *line)
{
	t_cmd	*cmds;

	cmds = create_cmds(line, p, ctx->is_tty);
	if (!cmds)
	{
		prompt_exit(p, ctx->is_tty, ctx->saved_stdin, 1);
		shell->saved_stdin = -1;
		shell->cur_prompt = NULL;
		free(line);
		return (NULL);
	}
	return (cmds);
}

int	prompt(t_shell *shell)
{
	t_prompt		p;
	t_prompt_ctx	ctx;
	char			*line;
	t_cmd			*cmds;
	int				status;

	if (prompt_init(shell, &p, &ctx))
		return (1);
	if (build_prompt1(shell, &p, ctx.is_tty) == 0)
		return (prompt_exit(&p, ctx.is_tty, ctx.saved_stdin, 0));
	status = get_and_validate_line(shell, &p, &ctx, &line);
	if (status != 2)
		return (status);
	cmds = parse_line(shell, &p, &ctx, line);
	if (!cmds)
		return (1);
	shell->cur_line = line;
	shell->cur_cmds = cmds;
	ctx.p = &p;
	ctx.line = line;
	return (execute_and_cleanup(shell, cmds, &ctx));
}
