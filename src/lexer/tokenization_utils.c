/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpieck <lpieck@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 13:52:29 by lpieck            #+#    #+#             */
/*   Updated: 2026/01/06 16:26:42 by lpieck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_space(char c)
{
	if ((c > 6 && c < 12) || c == 32)
		return (1);
	return (0);
}

int	is_operator(char c)
{
	if (c == '<' || c == '>' || c == '|')
		return (1);
	return (0);
}

int	operator_len(char *s)
{
	if ((s[0] == '<' && s[1] == '<') || (s[0] == '>' && s[1] == '>'))
		return (2);
	return (1);
}

int	operator_type(char *op)
{
	if (ft_strncmp(op, "|", 2) == 0)
		return (TOK_PIPE);
	if (ft_strncmp(op, "<", 2) == 0)
		return (TOK_REDIR_IN);
	if (ft_strncmp(op, ">", 2) == 0)
		return (TOK_REDIR_OUT);
	if (ft_strncmp(op, "<<", 3) == 0)
		return (TOK_HEREDOC);
	if (ft_strncmp(op, ">>", 3) == 0)
		return (TOK_APPEND);
	return (TOK_WORD);
}

char	*check_for_quotes(char *str, int *quoted, int *i, int *expand)
{
	char	quote;

	quote = str[*i];
	if (quote == '"')
		*quoted = 2;
	else if (quote == '\'')
	{
		*quoted = 1;
		*expand = 0;
	}
	(*i)++;
	while (str[*i] && str[*i] != quote)
		(*i)++;
	if (!str[*i])
	{
		write(2, "minishell: syntax error: unclosed quote\n", 40);
		return (NULL);
	}
	(*i)++;
	return (str);
}
