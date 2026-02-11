/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_variable2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpinas <cpinas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 19:20:37 by cpinas            #+#    #+#             */
/*   Updated: 2026/02/11 19:21:28 by cpinas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
