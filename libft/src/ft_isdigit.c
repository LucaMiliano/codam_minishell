/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpinas <cpinas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 17:58:05 by cpinas            #+#    #+#             */
/*   Updated: 2025/09/25 18:30:58 by cpinas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

int	ft_isdigit(int c)
{
	if (c < 0 || c > 255)
		return (0);
	c = (unsigned char)c;
	return (c >= '0' && c <= '9');
}
// Same statement as ft_isalpha still aplies probably for the other "simple"
// functions as well...
