/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_variable.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpinas <cpinas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 15:31:10 by lpieck            #+#    #+#             */
/*   Updated: 2026/01/04 20:01:59 by cpinas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_env(char *key, char *value)
{
	int		i;
	size_t	key_len;
	char	*new_var;

	if (!key || !value || !g_shell.env)
		return ;
	key_len = ft_strlen(key);
	new_var = malloc(key_len + 1 + ft_strlen(value) + 1);
	if (!new_var)
		return ;
	ft_strlcpy(new_var, key, key_len + 1);
	ft_strlcat(new_var, "=", key_len + 2);
	ft_strlcat(new_var, value, key_len + 2 + ft_strlen(value));
	i = -1;
	while (g_shell.env[i++])
	{
		if (ft_strncmp(g_shell.env[i], key, key_len) == 0
			&& g_shell.env[i][key_len] == '=')
		{
			free(g_shell.env[i]);
			g_shell.env[i] = new_var;
			return ;
		}
	}
	free(new_var);
}

char	*find_in_env(const char *name)
{
	int		i;
	size_t	len;
	char	**env;

	if (!name)
		return (NULL);
	env = g_shell.env;
	if (!env)
		return (NULL);
	len = ft_strlen(name);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], name, len) == 0
			&& env[i][len] == '=')
		{
			return (env[i] + len + 1);
		}
		i++;
	}
	return (NULL);
}

char	*join_path(char *dir, char *cmd)
{
	size_t	len;
	char	*res;

	len = ft_strlen(dir) + ft_strlen(cmd) + 2;
	res = malloc(len);
	if (!res)
		return (NULL);
	ft_strlcpy(res, dir, len);
	ft_strlcat(res, "/", len);
	ft_strlcat(res, cmd, len);
	return (res);
}

void	add_env_var(char *key, char *value)
{
	int		i;
	char	**new_env;
	char	*new_var;

	i = 0;
	while (g_shell.env && g_shell.env[i])
		i++;
	new_env = malloc(sizeof(char *) * (i + 2));
	if (!new_env)
		return ;
	i = 0;
	while (g_shell.env && g_shell.env[i])
	{
		new_env[i] = g_shell.env[i];
		i++;
	}
	if (value)
		new_var = ft_strjoin_multiple(key, "=", value, NULL);
	else
		new_var = ft_strdup(key);
	new_env[i++] = new_var;
	new_env[i] = NULL;
	free(g_shell.env);
	g_shell.env = new_env;
}

void	remove_env_var(char *key)
{
	int	i;
	int	j;
	int	key_len;

	if (!key || !g_shell.env)
		return ;
	key_len = ft_strlen(key);
	i = 0;
	while (g_shell.env[i])
	{
		if (ft_strncmp(g_shell.env[i], key, key_len) == 0
			&& g_shell.env[i][key_len] == '=')
		{
			free(g_shell.env[i]);
			j = i;
			while (g_shell.env[j + 1])
			{
				g_shell.env[j] = g_shell.env[j + 1];
				j++;
			}
			g_shell.env[j] = NULL;
			return ;
		}
		i++;
	}
}
