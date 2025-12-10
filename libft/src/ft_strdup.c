/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpinas <cpinas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 22:43:37 by cpinas            #+#    #+#             */
/*   Updated: 2025/09/25 18:33:04 by cpinas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_strdup(char *s)
{
	char	*ptr;
	size_t	i;

	i = (ft_strlen(s));
	i = i + 1;
	ptr = malloc(i);
	if (!ptr)
		return (NULL);
	ft_memcpy(ptr, s, i);
	return (ptr);
}
