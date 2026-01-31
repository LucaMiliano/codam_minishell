/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpinas <cpinas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 18:18:50 by cpinas            #+#    #+#             */
/*   Updated: 2025/09/25 18:30:03 by cpinas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

int	ft_isalnum(int c)
{
	if (c < 0 || c > 255)
		return (0);
	c = ((unsigned char)c);
	return (ft_isalpha(c) || ft_isdigit(c));
}
// Same here regarding EOF check.
