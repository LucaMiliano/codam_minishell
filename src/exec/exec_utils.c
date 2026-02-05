/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpinas <cpinas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/27 15:41:00 by cpinas            #+#    #+#             */
/*   Updated: 2026/02/05 15:18:30 by cpinas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

void	exec_absolute_or_relative(t_shell *shell, t_cmd *cmd)
{
	execve(cmd->argv[0], cmd->argv, shell->env);
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

void	save_stdio1(int *saved_stdin, int *saved_stdout)
{
	*saved_stdin = dup(STDIN_FILENO);
	*saved_stdout = dup(STDOUT_FILENO);
}

void	restore_stdio1(int saved_stdin, int saved_stdout)
{
	dup2(saved_stdin, STDIN_FILENO);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdin);
	close(saved_stdout);
}
