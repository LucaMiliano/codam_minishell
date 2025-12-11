/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpinas <cpinas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 19:36:55 by cpinas            #+#    #+#             */
/*   Updated: 2025/12/10 20:52:10 by cpinas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

static char *token_name(enum e_toktype type)
{
	if (type == TOK_WORD)        return "WORD";
	if (type == TOK_PIPE)        return "PIPE";
	if (type == TOK_REDIR_IN)    return "REDIR_IN";
	if (type == TOK_REDIR_OUT)   return "REDIR_OUT";
	if (type == TOK_APPEND)      return "APPEND";
	if (type == TOK_HEREDOC)     return "HEREDOC";
	return "UNKNOWN";
}

void	print_tokens(t_tokens *lst)
{
	printf("\n--- TOKENS ---\n");
	while (lst)
	{
		printf("Type: %-10s | Value: \"%s\"\n",
			token_name(lst->type), lst->value);
		lst = lst->next;
	}
	printf("--------------\n\n");
}
void print_tokens2(t_tokens *tokens)
{
	int i = 0;
	while (tokens)
	{
		printf("[%d] type=%d, value='%s'\n", i, tokens->type, tokens->value);
		tokens = tokens->next;
		i++;
	}
}


void	free_tokens(t_tokens *lst)
{
	t_tokens *tmp;

	while (lst)
	{
		tmp = lst->next;
		free(lst->value);
		free(lst);
		lst = tmp;
	}
}
