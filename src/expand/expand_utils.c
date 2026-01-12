/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpinas <cpinas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 00:26:46 by cpinas            #+#    #+#             */
/*   Updated: 2026/01/12 00:37:52 by cpinas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

static char	*handle_special_var(const char *s, int *consumed)
{
	if (s[0] == '?')
	{
		*consumed = 1;
		return (ft_itoa(g_shell.last_status));
	}
	return (NULL);
}

static char	*extract_var_name(const char *s, int *len)
{
	*len = 0;
	while (s[*len] && (ft_isalnum(s[*len]) || s[*len] == '_'))
		(*len)++;
	if (*len == 0)
		return (NULL);
	return (ft_substr(s, 0, *len));
}

char	*get_var_value(const char *s, int *consumed)
{
	char	*name;
	char	*value;
	int		len;

	value = handle_special_var(s, consumed);
	if (value)
		return (value);
	name = extract_var_name(s, &len);
	if (!name)
	{
		*consumed = 0;
		return (ft_strdup("$"));
	}
	value = find_in_env(name);
	free(name);
	*consumed = len;
	if (!value)
		return (ft_strdup(""));
	return (ft_strdup(value));
}

char	*append_char(char *result, char c)
{
	char	*tmp;

	tmp = ft_strjoin_char(result, c);
	free(result);
	return (tmp);
}

char	*append_expanded_var(char *result, char *word, int *i)
{
	char	*value;
	char	*tmp;
	int		consumed;

	value = get_var_value(&word[*i + 1], &consumed);
	if (!value)
		return (free(result), NULL);
	tmp = ft_strjoin(result, value);
	free(result);
	free(value);
	if (!tmp)
		return (NULL);
	*i += consumed + 1;
	return (tmp);
}
