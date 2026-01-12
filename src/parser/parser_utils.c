/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpinas <cpinas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 03:32:00 by cpinas            #+#    #+#             */
/*   Updated: 2026/01/12 01:05:22 by cpinas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>

static int	check_pipe_position_validity(t_tokens *tokens)
{
	t_tokens	*prev;

	prev = tokens;
	tokens = tokens->next;
	while (tokens)
	{
		if (tokens->type == TOK_PIPE)
		{
			if (!tokens->next || tokens->next->type == TOK_PIPE)
			{
				write(2, "minishell:\
					syntax error near unexpected token '|'\n", 50);
				return (0);
			}
		}
		prev = tokens;
		tokens = tokens->next;
	}
	if (prev->type == TOK_PIPE)
	{
		write(2, "minishell: syntax error near unexpected token '|'\n", 50);
		return (0);
	}
	return (1);
}

int	check_pipe_syntax(t_tokens *tokens)
{
	if (!tokens)
		return (0);
	if (tokens->type == TOK_PIPE)
	{
		write(2, "minishell: syntax error near unexpected token '|'\n", 50);
		return (0);
	}
	return (check_pipe_position_validity(tokens));
}
