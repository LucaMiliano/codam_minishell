/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpinas <cpinas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 14:11:50 by lpieck            #+#    #+#             */
/*   Updated: 2026/01/04 19:36:57 by cpinas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/history.h>

int	exec_builtin(t_cmd *cmd)
{
	if (!cmd || !cmd->argv || !cmd->argv[0])
		return (1);
	if (ft_strncmp(cmd->argv[0], "echo", ft_strlen("echo") + 1) == 0)
		return (builtin_echo(cmd->argv));
	if (ft_strncmp(cmd->argv[0], "pwd", ft_strlen("pwd") + 1) == 0)
		return (builtin_pwd());
	if (ft_strncmp(cmd->argv[0], "env", ft_strlen("env") + 1) == 0)
		return (builtin_env());
	if (ft_strncmp(cmd->argv[0], "cd", ft_strlen("cd") + 1) == 0)
		return (builtin_cd(cmd->argv));
	if (ft_strncmp(cmd->argv[0], "exit", ft_strlen("exit") + 1) == 0)
		return (builtin_exit(cmd->argv));
	if (ft_strncmp(cmd->argv[0], "export", ft_strlen("export") + 1) == 0)
		return (builtin_export(cmd->argv));
	if (ft_strncmp(cmd->argv[0], "unset", ft_strlen("unset") + 1) == 0)
		return (builtin_unset(cmd->argv));
	return (0);
}
