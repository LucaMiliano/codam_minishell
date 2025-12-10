/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpinas <cpinas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 01:28:48 by cpinas            #+#    #+#             */
/*   Updated: 2025/09/25 18:33:15 by cpinas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

static char	*alloc_check(char const *s1, char const *s2, int *len1, int *len2)
{
	if (!s1 || !s2)
		return (NULL);
	*len1 = ft_strlen(s1);
	*len2 = ft_strlen(s2);
	return (malloc(*len1 + *len2 + 1));
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*result;
	int		i;
	int		j;
	int		len1;
	int		len2;

	i = 0;
	j = 0;
	result = alloc_check(s1, s2, &len1, &len2);
	if (!result)
		return (NULL);
	while (i < len1)
	{
		result[i] = s1[i];
		i++;
	}
	while (j < len2)
	{
		result[i] = s2[j];
		i++;
		j++;
	}
	result[i] = '\0';
	return (result);
}
