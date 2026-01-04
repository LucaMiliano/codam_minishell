/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_cd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpinas <cpinas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/28 15:31:38 by cpinas            #+#    #+#             */
/*   Updated: 2025/12/30 19:24:30 by cpinas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>


static char *get_oldpwd(void)
{
	char *cwd = getcwd(NULL, 0);
	if (!cwd)
		return NULL;
	char *oldpwd = ft_strdup(cwd);
	free(cwd);
	return oldpwd;
}

static char *resolve_target(char **argv)
{
	if (!argv[1] || ft_strncmp(argv[1], "~", 2) == 0)
		return find_in_env("HOME");
	if (ft_strncmp(argv[1], "-", 2) == 0)
		return find_in_env("OLDPWD");
	return argv[1];
}

int builtin_cd(char **argv)
{
	char *oldpwd;
	char *target;
	char *cwd;

	if (!argv || !argv[0])
		return (1);
	oldpwd = get_oldpwd();
	if (!oldpwd)
	{
		perror("cd");
		return (1);
	}
	target = resolve_target(argv);
	if (!target)
	{
		write(2, "cd: HOME or OLDPWD not set\n", 27);
		free(oldpwd);
		return (1);
	}
	if (chdir(target) != 0)
	{
		perror("cd");
		free(oldpwd);
		return (1);
	}
	update_env("OLDPWD", oldpwd);
	free(oldpwd);

	cwd = getcwd(NULL, 0);
	if (cwd)
	{
		update_env("PWD", cwd);
		free(cwd);
	}

	return (0);
}



