/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpinas <cpinas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 21:27:04 by cpinas            #+#    #+#             */
/*   Updated: 2025/09/25 18:33:52 by cpinas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t			s_len;
	unsigned char	x;

	x = (unsigned char) c;
	s_len = ft_strlen(s);
	if (x == '\0')
		return ((char *)&s[s_len]);
	while (s_len-- > 0)
	{
		if ((unsigned char) s[s_len] == x)
			return ((char *)&(s[s_len]));
	}
	return (NULL);
}
