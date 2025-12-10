/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpinas <cpinas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 17:57:07 by cpinas            #+#    #+#             */
/*   Updated: 2025/09/25 18:30:30 by cpinas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

int	ft_isalpha(int c)
{
	if (c < 0 || c > 255)
		return (0);
	c = (unsigned char)c;
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}
// only thing it doesn't check for is (the special value) EOF
// which the gnu states however EOF (typically defined as -1)
// is in the stdio.h library which is not allowed.
// Probably correct have to ask someone.
