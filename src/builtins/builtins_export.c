/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpinas <cpinas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 14:45:24 by cpinas            #+#    #+#             */
/*   Updated: 2025/12/29 14:49:37 by cpinas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_valid_identifier(char *s)
{
	int	i;

	if (!s || !(ft_isalpha(s[0]) || s[0] == '_'))
		return (0);
	i = 1;
	while (s[i] && s[i] != '=')
	{
		if (!ft_isalnum(s[i]) && s[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

static void	export_one(char *arg)
{
	char	*eq;
	char	*key;

	if (!is_valid_identifier(arg))
	{
		ft_putstr_fd("minishell: export: `", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		return;
	}

	eq = ft_strchr(arg, '=');
	if (!eq)
	{
		if (!find_in_env(arg))
			add_env_var(arg, NULL);
		return;
	}

	key = ft_substr(arg, 0, eq - arg);
	if (find_in_env(key))
		update_env(key, eq + 1);
	else
		add_env_var(key, eq + 1);
	free(key);
}

static void	print_export(void)
{
	int	i;

	i = 0;
	while (g_shell.env && g_shell.env[i])
	{
		write(1, g_shell.env[i], ft_strlen(g_shell.env[i]));
		write(1, "\n", 1);
		i++;
	}
}


int	builtin_export(char **argv)
{
	int	i;

	if (!argv[1])
	{
		print_export();
		return (0);
	}
	i = 1;
	while (argv[i])
	{
		export_one(argv[i]);
		i++;
	}
	return (0);
}
