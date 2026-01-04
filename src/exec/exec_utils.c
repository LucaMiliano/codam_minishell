/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpinas <cpinas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/27 15:41:00 by cpinas            #+#    #+#             */
/*   Updated: 2026/01/04 21:01:13 by cpinas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

void	exec_absolute_or_relative(t_cmd *cmd)
{
	execve(cmd->argv[0], cmd->argv, g_shell.env);
	perror(cmd->argv[0]);
	exit(126);
}

int	is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	if (ft_strncmp(cmd, "cd", ft_strlen("cd") + 1) == 0)
		return (1);
	if (ft_strncmp(cmd, "echo", ft_strlen("echo") + 1) == 0)
		return (1);
	if (ft_strncmp(cmd, "pwd", ft_strlen("pwd") + 1) == 0)
		return (1);
	if (ft_strncmp(cmd, "env", ft_strlen("env") + 1) == 0)
		return (1);
	if (ft_strncmp(cmd, "exit", ft_strlen("exit") + 1) == 0)
		return (1);
	if (ft_strncmp(cmd, "export", ft_strlen("export") + 1) == 0)
		return (1);
	if (ft_strncmp(cmd, "unset", ft_strlen("unset") + 1) == 0)
		return (1);
	return (0);
}
