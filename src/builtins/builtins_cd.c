/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_cd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpinas <cpinas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/28 15:31:38 by cpinas            #+#    #+#             */
/*   Updated: 2026/01/04 19:28:14 by cpinas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

static char	*get_target_or_error(char **argv, char *oldpwd)
{
	char	*target;

	target = resolve_target(argv);
	if (!target)
	{
		write(2, "cd: HOME or OLDPWD not set\n", 27);
		free(oldpwd);
	}
	return (target);
}

static int	change_directory(char *target, char *oldpwd)
{
	if (chdir(target) != 0)
	{
		perror("cd");
		free(oldpwd);
		return (1);
	}
	return (0);
}

static void	update_pwd_env(char *oldpwd)
{
	char	*cwd;

	update_env("OLDPWD", oldpwd);
	cwd = getcwd(NULL, 0);
	if (cwd)
	{
		update_env("PWD", cwd);
		free(cwd);
	}
}

int	builtin_cd(char **argv)
{
	char	*oldpwd;
	char	*target;

	if (!argv || !argv[0])
		return (1);
	oldpwd = get_oldpwd_or_error();
	if (!oldpwd)
		return (1);
	target = get_target_or_error(argv, oldpwd);
	if (!target)
		return (1);
	if (change_directory(target, oldpwd) != 0)
		return (1);
	update_pwd_env(oldpwd);
	free(oldpwd);
	return (0);
}
