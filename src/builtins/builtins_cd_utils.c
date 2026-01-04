/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_cd_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpinas <cpinas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 19:26:08 by cpinas            #+#    #+#             */
/*   Updated: 2026/01/04 19:31:57 by cpinas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

char	*get_oldpwd(void)
{
	char	*cwd;
	char	*oldpwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (NULL);
	oldpwd = ft_strdup(cwd);
	free(cwd);
	return (oldpwd);
}

char	*resolve_target(char **argv)
{
	if (!argv[1] || ft_strncmp(argv[1], "~", 2) == 0)
		return (find_in_env("HOME"));
	if (ft_strncmp(argv[1], "-", 2) == 0)
		return (find_in_env("OLDPWD"));
	return (argv[1]);
}

char	*get_oldpwd_or_error(void)
{
	char	*oldpwd;

	oldpwd = get_oldpwd();
	if (!oldpwd)
		perror("cd");
	return (oldpwd);
}
