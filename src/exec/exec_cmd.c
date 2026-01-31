/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpinas <cpinas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/27 15:21:54 by cpinas            #+#    #+#             */
/*   Updated: 2026/01/25 19:02:19 by cpinas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

static void	try_exec_paths(t_shell *shell, char **paths, t_cmd *cmd)
{
	char	*full;
	int		i;

	i = 0;
	while (paths[i])
	{
		full = join_path(paths[i], cmd->argv[0]);
		if (full)
			execve(full, cmd->argv, shell->env);
		free(full);
		i++;
	}
}

void	exec_from_path(t_shell *shell, t_cmd *cmd)
{
	char	**paths;
	char	*path_env;

	path_env = find_in_env(shell, "PATH");
	if (!path_env)
	{
		write(2, "minishell: PATH not set\n", 24);
		exit(127);
	}
	paths = ft_split(path_env, ':');
	if (!paths)
		exit(1);
	try_exec_paths(shell, paths, cmd);
	free_split(paths);
	write(2, cmd->argv[0], ft_strlen(cmd->argv[0]));
	write(2, ": command not found\n", 21);
	exit(127);
}

void	exec_cmd(t_shell *shell, t_cmd *cmd, int in_fd, int out_fd)
{
	(void)in_fd;
	(void)out_fd;
	if (!cmd || !cmd->argv || !cmd->argv[0])
		exit(1);
	if (is_builtin(cmd->argv[0]))
	{
		exec_builtin(cmd, shell);
		exit(0);
	}
	if (ft_strchr(cmd->argv[0], '/'))
		exec_absolute_or_relative(shell, cmd);
	exec_from_path(shell, cmd);
}
