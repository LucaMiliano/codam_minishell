/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpinas <cpinas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 15:25:48 by lpieck            #+#    #+#             */
/*   Updated: 2026/02/05 13:58:01 by cpinas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_redir(enum e_toktype tok_type)
{
	return (tok_type == TOK_REDIR_IN || tok_type == TOK_REDIR_OUT
		|| tok_type == TOK_APPEND || tok_type == TOK_HEREDOC);
}

int	redir_alloc_error(t_cmd **head)
{
	free_cmd_pipeline(*head);
	return (0);
}

int	heredoc_syntax_error(t_cmd **head)
{
	write(2, "minishell: syntax error near heredoc\n", 37);
	free_cmd_pipeline(*head);
	return (0);
}

int	heredoc_alloc_error(t_cmd **head)
{
	free_cmd_pipeline(*head);
	return (0);
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
