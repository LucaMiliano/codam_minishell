/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpieck <lpieck@student.codam.nl>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 16:00:58 by lpieck            #+#    #+#             */
/*   Updated: 2026/01/27 11:23:36 by lpieck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*append_variable(char *res, const char **p, const char *line)
{
	char	*var;
	char	*val;
	char	*old;
	int		start;

	(*p)++;
	start = *p - line;
	while (ft_isalnum(**p) || **p == '_')
		(*p)++;
	var = ft_substr(line, start, *p - line - start);
	val = find_in_env(var);
	old = res;
	if (val != NULL)
		res = ft_strjoin(res, val);
	else
		res = ft_strdup(res);
	free(old);
	free(var);
	return (res);
}

char	*expand_variables(const char *line)
{
	char		*res;
	const char	*p;

	res = ft_strdup("");
	if (!res)
		return (NULL);
	p = line;
	while (*p)
	{
		if (*p == '$' && ft_isalpha(*(p + 1)))
			res = append_variable(res, &p, line);
		else
		{
			res = append_char(res, *p);
			p++;
		}
	}
	return (res);
}
