/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpinas <cpinas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 02:38:16 by cpinas            #+#    #+#             */
/*   Updated: 2025/09/25 18:33:57 by cpinas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

static void	ft_edge(const char *s1, const char *set, size_t *start, size_t *end)
{
	*start = 0;
	*end = ft_strlen(s1);
	while (s1[*start] && ft_strchr(set, s1[*start]))
		(*start)++;
	while (*end > *start && ft_strchr(set, s1[*end - 1]))
		(*end)--;
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;
	size_t	len;
	char	*res;

	if (!s1 || !set)
		return (NULL);
	ft_edge(s1, set, &start, &end);
	len = end - start;
	res = (char *)malloc(len + 1);
	if (!res)
		return (NULL);
	ft_strlcpy(res, s1 + start, len + 1);
	return (res);
}
