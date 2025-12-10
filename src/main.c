/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpinas <cpinas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 12:39:07 by cpinas            #+#    #+#             */
/*   Updated: 2025/12/09 23:09:29 by cpinas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

// int add_history PARAMS(const char *);

int main(void)
{
	// char	*line; verwijdert want de line is nu dynamisch anders segfault

	setup_signals();
	// line = NULL; Zonder line ook niet setten op nul
	prompt();
	return (0);
}
