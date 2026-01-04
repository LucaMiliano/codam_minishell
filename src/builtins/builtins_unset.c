/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_unset.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpinas <cpinas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 16:35:52 by cpinas            #+#    #+#             */
/*   Updated: 2026/01/04 18:43:17 by cpinas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_unset(char **argv)
{
	int	i;

	if (!argv)
		return (0);
	i = 1;
	while (argv[i])
	{
		remove_env_var(argv[i]);
		i++;
	}
	return (0);
}
