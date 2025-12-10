/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpinas <cpinas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 23:17:18 by cpinas            #+#    #+#             */
/*   Updated: 2025/09/25 18:32:00 by cpinas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t				i;
	unsigned char		*ptrs;

	ptrs = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		if (ptrs[i] == (unsigned char)c)
			return ((void *)&ptrs[i]);
		i++;
	}
	return (NULL);
}
