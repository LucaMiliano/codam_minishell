/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization_more_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpieck <lpieck@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 00:03:28 by cpinas            #+#    #+#             */
/*   Updated: 2026/01/06 16:52:44 by lpieck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_operator_exclusion(char *str, int *i)
{
	if (str[*i] == '|' && str[*i + 1] == '|')
	{
		write(2, "minishell: syntax error near unexpected token '||'\n", 51);
		*i += 2;
		return (1);
	}
	if (str[*i] == '<' && str[*i + 1] == '<' && str [*i + 2] == '<')
	{
		write (2, "minishell: syntax error near unexpected token '<<<'\n", 51);
		*i += 3;
		return (1);
	}
	if (str[*i] == '>' && str[*i + 1] == '<')
	{
		write(2, "minishell: syntax error near unexpected token `><`\n", 51);
		*i += 2;
		return (1);
	}
	if (str[*i] == '<' && str[*i + 1] == '>')
	{
		write(2, "minishell: syntax error near unexpected token `<>`\n", 51);
		*i += 2;
		return (1);
	}
	return (0);
}

char	*remove_quotes(char *s)
{
	char	*new;
	int		i;
	int		j;
	char	q;

	i = 0;
	j = 0;
	new = malloc(ft_strlen(s) +1);
	if (!new)
		return (NULL);
	while (s[i])
	{
		if (s[i] == '\'' || s[i] == '"')
		{
			q = s[i++];
			while (s[i] && s[i] != q)
				new[j++] = s[i++];
			if (s[i] == q)
				i++;
		}
		else
			new[j++] = s[i++];
	}
	new[j] = '\0';
	return (new);
}

t_tokens	*new_token(char *val, int type, int quoted, int exp)
{
	t_tokens	*new;

	new = malloc(sizeof(t_tokens));
	if (!new)
		return (NULL);
	new->value = val;
	new->type = type;
	new->quoted = quoted;
	new->expandable = exp;
	new->next = NULL;
	return (new);
}

void	token_add_back(t_tokens **tokens, t_tokens *new)
{
	t_tokens	*tmp;

	if (!new)
		return ;
	if (!*tokens)
		*tokens = new;
	else
	{
		tmp = *tokens;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}
