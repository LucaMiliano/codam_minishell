/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpinas <cpinas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 13:52:29 by lpieck            #+#    #+#             */
/*   Updated: 2025/12/29 17:00:21 by cpinas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_space(char c)
{
	// (unsigned)c; unused variable
	if ((c > 6 && c < 12) || c == 32) // () around the expression to resolve error (-Wall -Werror Wextra)
		return (1);
	return (0);
}

int	is_operator(char c)
{
	// (unsigned)c; unused variable
	if (c == '<' || c == '>' || c == '|')
		return (1);
	return (0);
}

int operator_len(char *s)
{
	if ((s[0] == '<' && s[1] == '<') || (s[0] == '>' && s[1] == '>'))
		return 2;
	return 1;
}

// int	operator_type(char *op)
// {
// 	if (!ft_strcmp(op, "|"))
// 		return (TOK_PIPE);
// 	if (!ft_strcmp(op, "<"))
// 		return (TOK_REDIR_IN);
// 	if (!ft_strcmp(op, ">"))
// 		return (TOK_REDIR_OUT);
// 	if (!ft_strcmp(op, "<<"))
// 		return (TOK_HEREDOC);
// 	if (!ft_strcmp(op, ">>"))
// 		return (TOK_APPEND);
// 	return (TOK_WORD);
// } Replaced with ft_strncmp want die checkt n aantal zelfs zonder '\0'

int operator_type(char *op)
{
	if (ft_strncmp(op, "|", 2) == 0)
		return TOK_PIPE;
	if (ft_strncmp(op, "<", 2) == 0)
		return TOK_REDIR_IN;
	if (ft_strncmp(op, ">", 2) == 0)
		return TOK_REDIR_OUT;
	if (ft_strncmp(op, "<<", 3) == 0)
		return TOK_HEREDOC;
	if (ft_strncmp(op, ">>", 3) == 0)
		return TOK_APPEND;
	return TOK_WORD;
}



