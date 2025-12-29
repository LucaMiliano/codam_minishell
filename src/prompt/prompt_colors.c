/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_colors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpinas <cpinas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 21:07:52 by cpinas            #+#    #+#             */
/*   Updated: 2025/12/10 22:27:03 by cpinas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	color_prompt(t_prompt *p)
{
	char *tmp;

	tmp = ft_strjoin_multiple(
		GREEN, p->user, RESET, "@",
		CYAN, p->host, RESET, " ",
		YELLOW, p->cwd, RESET, " ",
		RED, "$ ", RESET,
		NULL
	);
	p->prompt_str = tmp;
} // zo is best goed al voor kleur

char	*ft_strjoin_multiple(const char *first, ...)
{
	va_list args;
	const char *str;
	char *result;
	char *tmp;

	if (!first)
		return NULL;
	result = ft_strdup(first);
	if (!result)
		return NULL;
	va_start(args, first);
	while ((str = va_arg(args, const char *)) != NULL)
	{
		tmp = result;
		result = ft_strjoin(result, str); // use your libft ft_strjoin
		free(tmp);
		if (!result)
		{
			va_end(args);
			return NULL;
		}
	}
	va_end(args);
	return result;
}
