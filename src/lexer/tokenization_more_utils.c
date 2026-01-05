/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization_more_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpieck <lpieck@student.codam.nl>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 00:03:28 by cpinas            #+#    #+#             */
/*   Updated: 2026/01/05 10:21:17 by lpieck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_operator_exclusion(char *str, int *i)
{
	if (str[*i] == '|' && str[*i + 1] == '|') // '||' deze verwijderen als we bonus gaan doen
	{
		write(2, "minishell: syntax error near unexpected token '||'\n", 51);
		*i += 2;
		return (1);
	}
	if (str[*i] == '<' && str[*i + 1] == '<' && str [*i + 2] == '<') // '<<<'
	{
		write (2, "minishell: syntax error near unexpected token '<<<'\n", 51);
		*i += 3;
		return (1);
	}
	if (str[*i] == '>' && str[*i + 1] == '<') // ><
	{
		write(2, "minishell: syntax error near unexpected token `><`\n", 51);
		*i += 2;
		return (1);
	}
	if (str[*i] == '<' && str[*i + 1] == '>') // <>
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
	int		i = 0;
	int		j = 0;

	new = malloc(ft_strlen(s) +1);
	if (!new)
		return (NULL);
	while (s[i])
	{
		if (s[i] == '\'' || s[i] == '"')
		{
			char q = s[i++];
			while (s[i] && s[i] != q)
				new[j++] = s[i++];
			if (s[i] == q)
				i++;
		}
		else
			new[j++] = s[i++];
	}
	new[j] = '\0';
	return new;
}
