/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpinas <cpinas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 14:19:09 by lpieck            #+#    #+#             */
/*   Updated: 2025/12/11 00:58:32 by cpinas           ###   ########.fr       */
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
	// int			skip; // -> unused variable?
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
		return ; // toegevoegd voor echt foute input (makkelijker voor parsen)
	len = operator_len(str + *i);
	operator = ft_substr(str, *i, len);
	if (!operator)
		return ;
	type = operator_type(operator);
	add_token(list, operator, type, 0, 1); // arguments toegevoegd
	*i += len;
}

void	handle_word(char *str, int *i, t_tokens **list)
{
	char *word;

	word = extract_word(str, i);
	if  (!word)
		return ;
	add_token(list, word, TOK_WORD, 0, 1); // zelfde als in handle_operator
}

char	*extract_word(char *str, int *i)
{
	int		start = *i;
	int		j = *i;
	char	quote;
	int		quoted = 0;
	int		expand = 1;

	start = *i;
	j = *i;
	while (str[j] && !is_space(str[j]) && !is_operator(str[j]))
	{
		if (str[j] == '"' || str[j] == '\'')
		{
			quote = str[j];
			if (quote == '"')
				quoted = 2;
			else if (quote == '\'')
			{
				quoted = 1;
				expand = 0; // enkele quote geen expansion
			}

			j++; // skip opening quote
			while (str[j] && str[j] != quote)
				j++;

			if (!str[j])
			{
				write(2, "minishell: syntax error: unclosed quote\n", 40);
				*i = j;
				return (NULL);
			}
			j++; // skip closing quote
		}
		else
			j++;
	}
	*i = j;
	// haal onveranderde tekst eruit
	char *raw = ft_substr(str, start, j - start);
	if (!raw)
		return (NULL);

	// verwijder quotes -> new function
	char *clean = remove_quotes(raw);
	free(raw);
	return (clean);
}

t_tokens	*add_token(t_tokens **tokens, char *val, int type, int quoted, int expandable) // voor het struct en toekomstige parsing
{
	t_tokens *new;
	t_tokens *tmp;

	new = malloc(sizeof(t_tokens));
	if (!new)
		return (NULL);
	new->value = val;
	new->type = type;
	new->quoted = quoted;
	new->expandable = expandable;
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
	return (new);
} // een return toegevoegd zodat de data rechtstreeks kan worden aangepast;
