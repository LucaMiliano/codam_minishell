/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpinas <cpinas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 14:26:00 by cpinas            #+#    #+#             */
/*   Updated: 2025/11/12 22:54:03 by cpinas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isvalid_base_char(char c, int base)
{
	if (base <= 10)
		return (c >= '0' && c < '0' + base);
	return ((c >= '0' && c <= '9')
		|| (c >= 'A' && c < 'A' + base - 10)
		|| (c >= 'a' && c < 'a' + base - 10));
}

static int	ft_char_to_val(char c)
{
	if (c >= '0' && c <= '9')
		return (c - '0');
	if (c >= 'A' && c <= 'F')
		return (c - 'A' + 10);
	if (c >= 'a' && c <= 'f')
		return (c - 'a' + 10);
	return (0);
}

int	ft_atoi_base(const char *str, int base)
{
	int	result;
	int	sign;

	if (!str || base < 2 || base > 16)
		return (0);
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	sign = 1;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	result = 0;
	while (ft_isvalid_base_char(*str, base))
		result = result * base + ft_char_to_val(*str++);
	return (result * sign);
}
