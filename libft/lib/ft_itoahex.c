/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoahex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpinas <cpinas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 14:27:11 by cpinas            #+#    #+#             */
/*   Updated: 2025/11/04 13:13:36 by cpinas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

char	*ft_itoahex(unsigned long n, char format)
{
	char		*hex_digits;
	char		*res;
	int			i;

	hex_digits = "0123456789abcdef";
	res = malloc(17);
	i = 0;
	if (!res)
		return (NULL);
	if (n == 0)
	{
		res[i++] = ('0');
		res[i] = ('\0');
		return (res);
	}
	while (n > 0)
	{
		res[i++] = hex_digits[n % 16];
		n /= 16;
	}
	res[i] = '\0';
	return (ft_specifier (res, format));
}

char	*ft_specifier(char *res, char format)
{
	char	*tmp;

	ft_strrevv(res);
	if (format == 'X' || format == 'p')
		tmp = ft_hex_specifier(res, format);
	else
		tmp = res;
	if (format == 'p')
	{
		free(res);
		res = tmp;
	}
	else if (format == 'X')
	{
		res = tmp;
	}
	return (res);
}
