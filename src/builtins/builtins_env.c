/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpinas <cpinas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/28 15:24:04 by cpinas            #+#    #+#             */
/*   Updated: 2026/01/25 17:07:50 by cpinas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>

int	builtin_env(t_shell *shell)
{
	int		i;
	char	**env;

	env = shell->env;
	i = 0;
	if (!env)
		return (0);
	while (env[i])
	{
		write(STDOUT_FILENO, env[i], ft_strlen(env[i]));
		write(STDOUT_FILENO, "\n", 1);
		i++;
	}
	return (0);
}
