/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_pwd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpinas <cpinas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/28 15:15:53 by cpinas            #+#    #+#             */
/*   Updated: 2025/12/29 14:20:43 by cpinas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>
#include <stdlib.h>

// int builtin_pwd(void)
// {
// 	char *cwd = getcwd(NULL, 0);
// 	if (!cwd)
// 	{
// 		write(2, "pwd: error retrieving current directory\n", 40);
// 		return (1);
// 	}

// 	write(STDOUT_FILENO, cwd, ft_strlen(cwd));
// 	write(STDOUT_FILENO, "\n", 1);
// 	free(cwd);
// 	return (1);
// }

int	builtin_pwd(void)
{
char *cwd = getcwd(NULL, 0);
if (!cwd)
{
	write(2, "pwd: error retrieving current directory\n", 40);
	return 1;
}
write(STDOUT_FILENO, cwd, ft_strlen(cwd));
write(STDOUT_FILENO, "\n", 1);

update_env("PWD", cwd);  // keep g_shell.env in sync
free(cwd);
return (0);
}
