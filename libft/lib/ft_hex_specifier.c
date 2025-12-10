/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hex_specifier.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpinas <cpinas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 03:52:58 by cpinas            #+#    #+#             */
/*   Updated: 2025/09/25 18:28:12 by cpinas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

char	*ft_hex_specifier(char *c, char format)
{
	int		j;
	char	*b;

	j = -1;
	if (format == 'X')
	{
		while (c[++j])
			c[j] = ft_toupperr((unsigned char)c[j]);
		return (c);
	}
	if (format == 'p')
	{
		j = ft_strlenn(c);
		b = malloc(j + 3);
		if (!b)
			return (NULL);
		b[0] = '0';
		b[1] = 'x';
		ft_strncpyy(b + 2, c, j);
		b[j + 2] = '\0';
		return (b);
	}
	return (c);
}
