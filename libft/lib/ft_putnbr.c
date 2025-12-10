/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpinas <cpinas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 03:34:44 by cpinas            #+#    #+#             */
/*   Updated: 2025/09/25 18:28:52 by cpinas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

int	ft_putnbr(int n)
{
	long	num;
	int		count;

	num = n;
	count = 0;
	if (num < 0)
	{
		count += ft_putchar('-');
		num = -num;
	}
	if (num >= 10)
		count += ft_putnbr(num / 10);
	count += ft_putchar((num % 10) + '0');
	return (count);
}
