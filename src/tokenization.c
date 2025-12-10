/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpieck <lpieck@student.codam.nl>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 14:19:09 by lpieck            #+#    #+#             */
/*   Updated: 2025/12/10 15:27:03 by lpieck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
TODO:
- create tokens: WORD, OPTION, NUM, SQUOTE, DQUOTE, PIPE, REDIR_IN, REDIR_OUT, APPEND, HEREDOC.
- return error on unclosed quotes
- Make tokens by creating a linked list > for every token found, store that piece of string and assign a value to it (defining the type)

Type definitions:
1 = WORD
2 = OPTION
3 = NUM
4 = SQUOTE
5 = DQUOTE
6 = PIPE
7 = REDIR_IN
8 = REDIR_OUT
9 = APPEND
10 = HEREDOC
*/

#include "minishell.h"

t_tokens	*tokenize(char *prompt)
{
	int			i;
	int			skip;
	t_tokens	*tokens;

	i = 0;
	tokens = NULL;
	if (!prompt)
		return (NULL);
	while (prompt[i])
	{
		while (is_space(prompt[i]))
			i++;
		if (is_operator(prompt[i]))
			handle_operator(prompt, &i, &tokens);
		else
			handle_word(prompt, &i, &tokens);
	}
	return (tokens);
}

void	handle_operator(char *str, int *i, t_tokens **list)
{
	int		len;
	char	*operator;
	int		type;
	
	len = operator_len(str + *i);
	operator = ft_substr(str, *i, len);
	if (!operator)
		return ;
	type = operator_type(operator);
	add_token(list, operator, type);
	*i += len;	
}

void	handle_word(char *str, int *i, t_tokens **list)
{
	char *word;

	word = extract_word(str, i);
	if  (!word)
		return ;
	add_token(list, word, TOK_WORD);
}

char *extract_word(char *str, int *i)
{
	int		start;
	int		j;
	char	quote;

	start = *i;
	j = *i;
	while (str[j] && !is_space(str[j]) && !is_operator(str[j]))
	{
		if (str[j] == 34 || str[j] == 39) // checks if currecnt char are quotes
		{
			quote = str[j++]; // sla op in c en ga door
			while (str[j] && str[j] != quote)
				j++;
			if (str[j] = quote)
				j++;
			else
				error_handling(); // TODO error wnr unclosed quote
		}
		else
			j++;
	}
	*i = j;
	return (ft_substr(str, start, j - start));
}

void	add_token(t_tokens **tokens, char *val, int type)
{
	t_tokens *new;
	t_tokens *tmp;
	
	new = malloc(sizeof(t_tokens));
	if (!new)
		return ;
	new->value = val;
	new->type = type;
	new->next = NULL;
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