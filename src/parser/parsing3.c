/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpinas <cpinas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 13:57:04 by cpinas            #+#    #+#             */
/*   Updated: 2026/02/05 13:57:36 by cpinas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parse_heredoc(t_tokens **tokens, t_cmd *cmd, t_cmd **head)
{
	t_tokens	*delim;
	t_redir		*redir;

	delim = (*tokens)->next;
	if (!delim || delim->type != TOK_WORD)
		return (heredoc_syntax_error(head));
	redir = redir_new(R_HEREDOC, delim->value, delim->expandable);
	if (!redir)
		return (heredoc_alloc_error(head));
	cmd_add_redir(cmd, redir);
	*tokens = skip_heredoc_body(delim);
	return (1);
}

int	parse_redir(t_tokens **tokens, t_cmd *cmd, t_cmd **head)
{
	if ((*tokens)->type == TOK_HEREDOC)
		return (parse_heredoc(tokens, cmd, head));
	return (parse_file_redir(tokens, cmd, head));
}

int	parse_token(t_tokens **tokens, t_cmd **current, t_cmd **head)
{
	if ((*tokens)->type == TOK_WORD)
		return (parse_word(tokens, *current));
	if ((*tokens)->type == TOK_PIPE)
		return (parse_pipe(tokens, current));
	if (is_redir((*tokens)->type))
		return (parse_redir(tokens, *current, head));
	*tokens = (*tokens)->next;
	return (1);
}

t_cmd	*parse(t_tokens *tokens)
{
	t_cmd	*head;
	t_cmd	*current;

	if (!check_pipe_syntax(tokens))
		return (NULL);
	head = NULL;
	current = NULL;
	while (tokens)
	{
		if (!current)
		{
			current = cmd_new();
			if (!current)
				return (NULL);
			if (!head)
				head = current;
		}
		if (!parse_token(&tokens, &current, &head))
			return (NULL);
	}
	return (head);
}
