/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpinas <cpinas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 14:45:24 by cpinas            #+#    #+#             */
/*   Updated: 2026/01/25 17:42:31 by cpinas           ###   ########.fr       */
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

static void	export_one(t_shell *shell, char *arg)
{
	char	*eq;
	char	*key;

	if (!is_valid_identifier(arg))
	{
		ft_putstr_fd("minishell: export: `", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		return ;
	}
	eq = ft_strchr(arg, '=');
	if (!eq)
	{
		if (!find_in_env(shell, arg))
			add_env_var(shell, arg, NULL);
		return ;
	}
	key = ft_substr(arg, 0, eq - arg);
	if (find_in_env(shell, key))
		update_env(shell, key, eq + 1);
	else
		add_env_var(shell, key, eq + 1);
	free(key);
}

static void	print_export(t_shell *shell)
{
	int	i;

	i = 0;
	while (shell->env && shell->env[i])
	{
		write(1, shell->env[i], ft_strlen(shell->env[i]));
		write(1, "\n", 1);
		i++;
	}
}

int	builtin_export(t_shell *shell, char **argv)
{
	int	i;

	if (!argv[1])
	{
		print_export(shell);
		return (0);
	}
	i = 1;
	while (argv[i])
	{
		export_one(shell, argv[i]);
		i++;
	}
	return (0);
}
