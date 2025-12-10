/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpinas <cpinas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 01:57:59 by cpinas            #+#    #+#             */
/*   Updated: 2025/09/25 18:31:08 by cpinas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

size_t	ft_intleng(long n)
{
	size_t	count;

	count = 1;
	if (n < 0)
	{
		n = -1 * n;
		count++;
	}
	while (n > 9)
	{
		n = n / 10;
		count++;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	char			*str;
	size_t			i;
	unsigned int	nb;
	long			num;

	num = n;
	i = ft_intleng(num);
	str = malloc((i + 1) * sizeof(char));
	if (!str)
		return (NULL);
	str[i] = '\0';
	if (num < 0)
	{
		nb = -num;
		str[0] = '-';
	}
	else
		nb = num;
	while (nb > 9)
	{
		str[--i] = (nb % 10) + '0';
		nb /= 10;
	}
	str[--i] = nb + '0';
	return (str);
}
