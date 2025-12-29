/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpinas <cpinas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 03:32:00 by cpinas            #+#    #+#             */
/*   Updated: 2025/12/21 03:49:52 by cpinas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>

int	check_pipe_syntax(t_tokens *tokens) //double pipe command syntax error
{
	if (!tokens)
		return (0);

	// PIPE at start
	if (tokens->type == TOK_PIPE)
	{
		write(2, "minishell: syntax error near unexpected token '|'\n", 52);
		return (0);
	}
	t_tokens *prev = tokens;
	tokens = tokens->next;

	while (tokens)
	{
		if (tokens->type == TOK_PIPE)
		{
			if (!tokens->next || tokens->next->type == TOK_PIPE)
			{
				write(2, "minishell: syntaxterror near unexpected token '|'\n", 52);
				return (0);
			}
		}
		prev = tokens;
		tokens = tokens->next;
	}
	// pipe at end
	if (prev->type == TOK_PIPE)
	{
		write(2, "minishell: syntax error near unexpected token '|'\n", 52);
		return (0);
	}
	return (1);
}
