/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpinas <cpinas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 13:56:30 by cpinas            #+#    #+#             */
/*   Updated: 2026/02/05 13:56:54 by cpinas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parse_word(t_tokens **tokens, t_cmd *cmd)
{
	cmd = argv_add(cmd, (*tokens)->value, (*tokens)->expandable);
	if (!cmd->argv)
		return (0);
	*tokens = (*tokens)->next;
	return (1);
}

int	parse_pipe(t_tokens **tokens, t_cmd **current)
{
	t_cmd	*next;

	next = cmd_new();
	if (!next)
		return (0);
	(*current)->next = next;
	*current = next;
	*tokens = (*tokens)->next;
	return (1);
}

int	parse_file_redir(t_tokens **tokens, t_cmd *cmd, t_cmd **head)
{
	t_tokens	*file;
	t_redir		*redir;

	file = (*tokens)->next;
	if (!file || file->type != TOK_WORD)
	{
		write(2, "minishell: syntax error near redirection\n", 41);
		free_cmd_pipeline(cmd);
		return (0);
	}
	redir = redir_new(redir_type((*tokens)->type),
			file->value, file->expandable);
	if (!redir)
		return (redir_alloc_error(head));
	cmd_add_redir(cmd, redir);
	*tokens = file->next;
	return (1);
}

t_tokens	*skip_heredoc_body(t_tokens *delim)
{
	t_tokens	*cur;

	cur = delim->next;
	while (cur)
	{
		if (cur->type == TOK_WORD
			&& ft_strncmp(cur->value, delim->value,
				ft_strlen(delim->value)) == 0)
			return (cur->next);
		cur = cur->next;
	}
	return (NULL);
}
