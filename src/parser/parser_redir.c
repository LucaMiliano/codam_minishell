/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpieck <lpieck@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 02:51:45 by cpinas            #+#    #+#             */
/*   Updated: 2026/01/23 15:50:31 by lpieck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <string.h>

// t_redir	*redir_new(t_redir_type type, char *target, int expandable);

int	parse_heredoc(t_tokens **tokens, t_cmd *cmd, t_cmd **head)
{
	t_tokens	*delim;
	t_redir		*redir;

	delim = (*tokens)->next;
	if (!delim || delim->type != TOK_WORD)
	{
		write(2, "minishell: syntax error near heredoc\n", 37);
		return (free_cmd_pipeline(*head), 0);
	}
	redir = redir_new(R_HEREDOC, delim->value, delim->expandable);
	if (!redir)
		return (free_cmd_pipeline(*head), 0);
	cmd_add_redir(cmd, redir);
	*tokens = skip_heredoc_body(delim);
	return (1);
}

void	cmd_add_redir(t_cmd *cmd, t_redir *redir)
{
	t_redir	*tmp;

	if (!cmd->redirs)
		cmd->redirs = redir;
	else
	{
		tmp = cmd->redirs;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = redir;
	}
}

int	is_redir(enum e_toktype tok_type)
{
	return (tok_type == TOK_REDIR_IN || tok_type == TOK_REDIR_OUT
		|| tok_type == TOK_APPEND || tok_type == TOK_HEREDOC);
}

t_redir_type	redir_type(enum e_toktype tok_type)
{
	if (tok_type == TOK_REDIR_IN)
		return (R_IN);
	if (tok_type == TOK_REDIR_OUT)
		return (R_OUT);
	if (tok_type == TOK_APPEND)
		return (R_APPEND);
	return (R_HEREDOC);
}

int	parse_redir(t_tokens **tokens, t_cmd *cmd, t_cmd **head)
{
	if ((*tokens)->type == TOK_HEREDOC)
		return (parse_heredoc(tokens, cmd, head));
	return (parse_file_redir(tokens, cmd, head));
}

// t_redir	*redir_new(t_redir_type type, char *target, int expandable)
// {
// 	t_redir *redir = malloc(sizeof(t_redir));
// 	if (!redir)
// 		return NULL;
// 	redir->type = type;
// 	redir->target = target; // pointer to token->value (we can strdup if needed)
// 	redir->expandable = expandable;
// 	redir->next = NULL;
// 	return redir;
// }

// t_redir	*redir_new(t_redir_type type, char *target, int expandable)
// {
// 	t_redir *redir = malloc(sizeof(t_redir));
// 	if (!redir)
// 		return NULL;

// 	redir->type = type;
// 	redir->target = strdup(target); // copy string
// 	if (!redir->target)
// 	{
// 		free(redir);
// 		return NULL;
// 	}
// 	redir->expandable = expandable;
// 	redir->next = NULL;
// 	return redir;
// }
