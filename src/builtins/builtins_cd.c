/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_cd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpinas <cpinas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/28 15:31:38 by cpinas            #+#    #+#             */
/*   Updated: 2025/12/28 19:58:33 by cpinas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

// int builtin_cd(char **argv, char **envp)
// {
// 	char cwd[4096];
// 	char *target;
// 	char *oldpwd;

// 	if (!argv || !argv[0])
// 		return (1);
// 	// Save old PWD before changing
// 	if (getcwd(cwd, sizeof(cwd)) == NULL)
// 	{
// 		perror("cd");
// 		return (1);
// 	}
// 	oldpwd = cwd;
// 	// Determine target directory
// 	if (!argv[1] || ft_strncmp(argv[1], "~", 2) == 0)
// 		target = getenv("HOME");
// 	else if (ft_strncmp(argv[1], "-", 2) == 0)
// 		target = getenv("OLDPWD");
// 	else
// 		target = argv[1];
// 	if (!target)
// 	{
// 		write(2, "cd: HOME or OLDPWD not set\n", 27);
// 		free(oldpwd);
// 		return (1);
// 	}
// 	// Attempt to change directory
// 	if (chdir(target) != 0)
// 	{
// 		perror("cd");
// 		free(oldpwd);
// 		return (1);
// 	}
// 	// Update PWD and OLDPWD in envp
// 	if (oldpwd)
// 	{
// 		update_env("OLDPWD", oldpwd, envp);
// 		free(oldpwd);  // safe to free our strdup
// 	}

// 	if (getcwd(cwd, sizeof(cwd)))
// 		update_env("PWD", cwd, envp);

// 	return (0);
// }

// int builtin_cd(char **argv)
// {
// 	char *cwd;
// 	char *target;
// 	char *oldpwd;

// 	if (!argv || !argv[0])
// 		return (1);

// 	// Save old PWD
// 	cwd = getcwd(NULL, 0); // dynamically allocate the path
// 	if (!cwd)
// 	{
// 		perror("cd");
// 		return 1;
// 	}
// 	oldpwd = ft_strdup(cwd); // strdup to safely store oldpwd
// 	free(cwd);

// 	// Determine target directory
// 	if (!argv[1] || ft_strncmp(argv[1], "~", 2) == 0)
// 		target = find_in_env("HOME");
// 	else if (ft_strncmp(argv[1], "-", 2) == 0)
// 		target = find_in_env("OLDPWD");
// 	else
// 		target = argv[1];

// 	if (!target)
// 	{
// 		write(2, "cd: HOME or OLDPWD not set\n", 27);
// 		free(oldpwd);
// 		return (1);
// 	}

// 	// Attempt to change directory
// 	if (chdir(target) != 0)
// 	{
// 		perror("cd");
// 		free(oldpwd);
// 		return (1);
// 	}

// 	// Update OLDPWD and PWD
// 	update_env("OLDPWD", oldpwd);
// 	free(oldpwd);

// 	cwd = getcwd(NULL, 0);
// 	if (cwd)
// 	{
// 		update_env("PWD", cwd);
// 		free(cwd);
// 	}

// 	return (0);
// }

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


// int builtin_cd(char **argv)
// {
// 	char cwd[PATH_MAX];
// 	char *target;
// 	char *oldpwd;

// 	if (!argv || !argv[0])
// 		return 1;

// 	// Save old PWD
// 	if (!getcwd(cwd, sizeof(cwd)))
// 	{
// 		perror("cd");
// 		return 1;
// 	}
// 	oldpwd = ft_strdup(cwd); // strdup to safely store oldpwd

// 	// Determine target directory
// 	if (!argv[1] || ft_strncmp(argv[1], "~", 2) == 0)
// 		target = find_in_env("HOME");
// 	else if (ft_strncmp(argv[1], "-", 2) == 0)
// 		target = find_in_env("OLDPWD");
// 	else
// 		target = argv[1];

// 	if (!target)
// 	{
// 		write(2, "cd: HOME or OLDPWD not set\n", 27);
// 		free(oldpwd);
// 		return 1;
// 	}

// 	// Attempt to change directory
// 	if (chdir(target) != 0)
// 	{
// 		perror("cd");
// 		free(oldpwd);
// 		return 1;
// 	}

// 	// Update OLDPWD and PWD
// 	update_env("OLDPWD", oldpwd);
// 	free(oldpwd);

// 	if (getcwd(cwd, sizeof(cwd)))
// 		update_env("PWD", cwd);

// 	return (0);
// }


// void update_env(char *key, char *value, char **envp)
// {
// 	int i;
// 	size_t key_len;
// 	size_t total_len;
// 	char *new_var;

// 	if (!key || !value || !envp)
// 		return;

// 	key_len = ft_strlen(key);
// 	total_len = key_len + 1 + ft_strlen(value) + 1; // key + '=' + value + '\0'

// 	new_var = malloc(total_len);
// 	if (!new_var)
// 		return;

// 	ft_strlcpy(new_var, key, total_len);			// copy key
// 	ft_strlcat(new_var, "=", total_len);			// append '='
// 	ft_strlcat(new_var, value, total_len);			// append value

// 	i = 0;
// 	while (envp[i])
// 	{
// 		if (ft_strncmp(envp[i], key, key_len) == 0 && envp[i][key_len] == '=')
// 		{
// 			free(envp[i]);
// 			envp[i] = new_var;
// 			return;
// 		}
// 		i++;
// 	}

// 	// Optional: if not found, skip adding
// 	free(new_var);
// }
