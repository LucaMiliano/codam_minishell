/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_variable.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpieck <lpieck@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 15:31:10 by lpieck            #+#    #+#             */
/*   Updated: 2026/02/11 17:09:38 by lpieck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*create_new_var(char *key, char *value)
{
	char	*new_var;
	size_t	key_len;

	key_len = ft_strlen(key);
	new_var = malloc(key_len + 1 + ft_strlen(value) + 1);
	if (!new_var)
		return (NULL);
	ft_strlcpy(new_var, key, key_len + 1);
	ft_strlcat(new_var, "=", key_len + 2);
	ft_strlcat(new_var, value, key_len + 2 + ft_strlen(value));
	return (new_var);
}

void	update_env(t_shell *shell, char *key, char *value)
{
	int		i;
	size_t	key_len;
	char	*new_var;

	if (!key || !value || !shell->env)
		return ;
	key_len = ft_strlen(key);
	new_var = create_new_var(key, value);
	if (!new_var)
		return ;
	i = 0;
	while (shell->env[i])
	{
		if (ft_strncmp(shell->env[i], key, key_len) == 0
			&& shell->env[i][key_len] == '=')
		{
			free(shell->env[i]);
			shell->env[i] = new_var;
			return ;
		}
		i++;
	}
	free(new_var);
}

char	*find_in_env(t_shell *shell, const char *name)
{
	int		i;
	size_t	len;
	char	**env;

	if (!name)
		return (NULL);
	if (!shell || !shell->env)
	{
		write(2, "error find_in_env\n", 19);
		return (NULL);
	}
	env = shell->env;
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

void	add_env_var(t_shell *shell, char *key, char *value)
{
	int		i;
	char	**new_env;
	char	*new_var;

	i = 0;
	while (shell->env && shell->env[i])
		i++;
	new_env = malloc(sizeof(char *) * (i + 2));
	if (!new_env)
		return ;
	i = 0;
	while (shell->env && shell->env[i])
	{
		new_env[i] = shell->env[i];
		i++;
	}
	if (value)
		new_var = ft_strjoin_multiple(key, "=", value, NULL);
	else
		new_var = ft_strdup(key);
	new_env[i++] = new_var;
	new_env[i] = NULL;
	free(shell->env);
	shell->env = new_env;
}

void	remove_env_var(t_shell *shell, char *key)
{
	int	i;
	int	j;
	int	key_len;

	if (!key || !shell->env)
		return ;
	key_len = ft_strlen(key);
	i = 0;
	while (shell->env[i])
	{
		if (ft_strncmp(shell->env[i], key, key_len) == 0
			&& shell->env[i][key_len] == '=')
		{
			free(shell->env[i]);
			j = i;
			while (shell->env[j + 1])
			{
				shell->env[j] = shell->env[j + 1];
				j++;
			}
			shell->env[j] = NULL;
			return ;
		}
		i++;
	}
}
