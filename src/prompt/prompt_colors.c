/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_colors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpinas <cpinas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 21:07:52 by cpinas            #+#    #+#             */
/*   Updated: 2026/02/10 17:58:04 by cpinas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	color_prompt(t_prompt *p)
{
	char	*tmp;

	tmp = ft_strjoin_multiple(
			GREEN, p->user, RESET, "@",
			CYAN, p->host, RESET, " ",
			YELLOW, p->cwd, RESET, " ",
			RED, "$ ", RESET,
			NULL
			);
	p->prompt_str = tmp;
}

static char	*join_and_free(char *result, const char *str)
{
	char	*tmp;

	tmp = result;
	result = ft_strjoin(tmp, str);
	free(tmp);
	return (result);
}

char	*ft_strjoin_multiple(const char *first, ...)
{
	va_list		args;
	const char	*str;
	char		*result;

	if (!first)
		return (NULL);
	result = ft_strdup(first);
	if (!result)
		return (NULL);
	va_start(args, first);
	str = va_arg(args, const char *);
	while (str)
	{
		result = join_and_free(result, str);
		if (!result)
		{
			va_end(args);
			return (NULL);
		}
		str = va_arg(args, const char *);
	}
	va_end(args);
	return (result);
}
