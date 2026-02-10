/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpieck <lpieck@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 13:37:58 by cpinas            #+#    #+#             */
/*   Updated: 2026/02/10 14:28:03 by lpieck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <unistd.h>

int	has_unclosed_quotes(char *str)
{
    int		i;
    char	quote;

    i = 0;
    while (str[i])
    {
        if (str[i] == '"' || str[i] == '\'')
        {
            quote = str[i];
            i++;
            while (str[i] && str[i] != quote)
                i++;
            if (!str[i])
                return (1);  // Found unclosed quote
            i++;
        }
        else
            i++;
    }
    return (0);
}

char	*read_from_stdin(void)
{
	char	buf[4096];
	ssize_t	bytes_read;

	bytes_read = read(STDIN_FILENO, buf, 4095);
	if (bytes_read <= 0)
		return (NULL);
	buf[bytes_read] = '\0';
	if (buf[bytes_read - 1] == '\n')
		buf[bytes_read - 1] = '\0';
	return (ft_strdup(buf));
}

char	*get_prompt_line(t_prompt *p, int is_tty)
{
	char	*line;
	char	*continuation;
    char	*temp;

	if (is_tty)
	{
		line = readline(p->prompt_str);
		if (!line)
			return (NULL);
		while (has_unclosed_quotes(line))
        {
            continuation = readline("> ");
            if (!continuation)
            {
                free(line);
                return (NULL);
            }
            temp = line;
            line = ft_strjoin(line, "\n");
            free(temp);
            if (!line)
                return (NULL);
            temp = line;
            line = ft_strjoin(line, continuation);
            free(temp);
            free(continuation);
            if (!line)
                return (NULL);
        }
		return (line);
	}

	return (read_from_stdin());
}

t_cmd	*create_cmds(char *line, t_prompt *p, int is_tty)
{
	t_tokens	*tokens;
	t_cmd		*cmds;

	tokens = tokenize(line);
	cmds = parse(tokens);
	free_tokens(tokens);
	if (!cmds && is_tty)
		free2_prompt(p);
	return (cmds);
}

int	execute_and_cleanup(
	t_shell *shell,
	t_cmd *cmds,
	t_prompt_ctx *ctx)
{
	if (prepare_heredocs(shell, cmds) != 0)
	{
		shell->cur_cmds = NULL;
		shell->cur_line = NULL;
		shell->cur_prompt = NULL;
		shell->saved_stdin = -1;
		free_cmd_pipeline(cmds);
		free(ctx->line);
		if (ctx->is_tty)
			free2_prompt(ctx->p);
		return (restore_and_return(ctx->saved_stdin, 1));
	}
	expand_pipeline(cmds, shell);
	setup_signals_exec();
	execute_pipeline(shell, cmds);
	shell->cur_cmds = NULL;
	shell->cur_line = NULL;
	shell->cur_prompt = NULL;
	shell->saved_stdin = -1;
	free_cmd_pipeline(cmds);
	free(ctx->line);
	if (ctx->is_tty)
		free_prompt(ctx->p);
	return (restore_and_return(ctx->saved_stdin, 1));
}

int	restore_and_return(int saved_stdin, int ret)
{
	dup2(saved_stdin, STDIN_FILENO);
	close(saved_stdin);
	rl_reset_terminal(NULL);
	return (ret);
}
