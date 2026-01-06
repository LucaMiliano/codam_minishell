/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpieck <lpieck@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 14:19:09 by lpieck            #+#    #+#             */
/*   Updated: 2026/01/06 16:52:29 by lpieck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tokens	*tokenize(char *prompt)
{
	int			i;
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

	if (handle_operator_exclusion(str, i))
		return ;
	len = operator_len(str + *i);
	operator = ft_substr(str, *i, len);
	if (!operator)
		return ;
	type = operator_type(operator);
	token_add_back(list, new_token(operator, type, 0, 0));
	*i += len;
}

void	handle_word(char *str, int *i, t_tokens **list)
{
	char	*word;
	int		quoted;
	int		expand;

	quoted = 0;
	expand = 1;
	word = extract_word(str, i, &quoted, &expand);
	if (!word)
		return ;
	token_add_back(list, new_token(word, TOK_WORD, quoted, expand));
}

char	*extract_word(char *str, int *i, int *quoted, int *expand)
{
	int		start;
	char	*raw;
	char	*clean;

	start = *i;
	while (str[*i] && !is_space(str[*i]) && !is_operator(str[*i]))
	{
		if (str[*i] == '"' || str[*i] == '\'')
		{
			if (!check_for_quotes(str, quoted, i, expand))
				return (NULL);
		}
		else
			(*i)++;
	}
	raw = ft_substr(str, start, *i - start);
	if (!raw)
		return (NULL);
	clean = remove_quotes(raw);
	free(raw);
	return (clean);
}
