/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpinas <cpinas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 18:28:59 by cpinas            #+#    #+#             */
/*   Updated: 2025/09/25 18:30:51 by cpinas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

int	ft_isascii(int c)
{
	if (c < 0 || c > 255)
		return (0);
	c = (unsigned char)c;
	return (c >= 0 && c <= 127);
}
// couldn't find isascii in the gnu, the manpage didn't state any checks other
// than the objective (unsigned char) which is already in effect (0 < c > 127)
// the typecasting and range check is just a precaution #safety first!
// in all seriousness I think since it's in the same grouping and the ohters all
// need these checks, it just seems logical to me.
