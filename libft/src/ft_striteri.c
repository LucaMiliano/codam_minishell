/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpinas <cpinas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 14:29:50 by cpinas            #+#    #+#             */
/*   Updated: 2025/09/25 18:33:10 by cpinas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

// Applies the function ’f’ to each character of the
// string passed as argument, passing its index as
// the first argument. Each character is passed by
// address to ’f’ so it can be modified if necessary.

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	i;

	if (!s || !f)
		return ;
	i = 0;
	while (s[i])
	{
		(f)(i, &s[i]);
		i++;
	}
}
