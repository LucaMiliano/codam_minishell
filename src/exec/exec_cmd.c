/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpinas <cpinas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/27 15:21:54 by cpinas            #+#    #+#             */
/*   Updated: 2025/12/29 16:16:32 by cpinas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <errno.h>
#include <limits.h>

#ifndef PATH_MAX
#define PATH_MAX 4096
#endif


static int is_builtin(char *cmd)
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
	// add export/unset/history if desired
	return (0);
}


void exec_cmd(t_cmd *cmd, int in_fd, int out_fd)
{
	char	**paths;
	char	*path_env;
	char	*full;
	int		i;

	(void)in_fd;
	(void)out_fd;

	if (!cmd || !cmd->argv || !cmd->argv[0])
		exit(1);
	/* Child-safe builtins only */
	if (is_builtin(cmd->argv[0]))
	{
		exec_builtin(cmd);
		exit(0);
	}
	/* Absolute or relative path */
	if (ft_strchr(cmd->argv[0], '/'))
	{
		execve(cmd->argv[0], cmd->argv, g_shell.env);
		perror(cmd->argv[0]);
		exit(126);
	}
	/* PATH lookup */
	path_env = find_in_env("PATH");
	if (!path_env)
	{
		write(2, "minishell: PATH not set\n", 24);
		exit(127);
	}
	paths = ft_split(path_env, ':');
	if (!paths)
		exit(1);
	i = 0;
	while (paths[i])
	{
		full = join_path(paths[i], cmd->argv[0]); // explained below
		if (full)
			execve(full, cmd->argv, g_shell.env);
		free(full);
		i++;
	}
	free_split(paths);
	write(2, cmd->argv[0], ft_strlen(cmd->argv[0]));
	write(2, ": command not found\n", 21);
	exit(127);
}


// Illegal right now in exec_cmd !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

// fprintf ❌

// strchr ❌ (must use ft_strchr)

// strtok ❌

// snprintf ❌

// Allowed alternatives

// write / printf

// ft_strchr

// Manual PATH splitting

// Manual string joins !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
