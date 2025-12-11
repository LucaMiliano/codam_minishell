/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpinas <cpinas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 20:49:43 by cpinas            #+#    #+#             */
/*   Updated: 2025/12/10 22:23:41 by cpinas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <unistd.h>

// Directory (path)
char	*get_current_directory(void)
{
	char	*cwd;
	char	*home;
	char	*result;

	cwd = malloc(1024);
	if (!cwd)
		return (NULL);
	if (!getcwd(cwd, 1024))
	{
		free(cwd);
		return (NULL);
	}
	home = getenv("HOME");
	if (home && !ft_strncmp(cwd, home, ft_strlen(home)))
	{
		result = malloc(ft_strlen(cwd) - ft_strlen(home) + 2);
		if (!result)
			return (free(cwd), NULL);
		result[0] = '~';
		ft_strlcpy(result + 1, cwd + ft_strlen(home),
			ft_strlen(cwd) - ft_strlen(home) + 1);
		free(cwd);
		return (result);
	}
	return (cwd);
}

// Username
char	*get_username(void)
{
	char	*env;

	env = getenv("USER");
	if (env)
		return (ft_strdup(env));
	return (ft_strdup("user"));
}

// Hostname
char	*get_hostname(void)
{
	char	buf[256];

	if (getenv("HOSTNAME"))
		return (ft_strdup(getenv("HOSTNAME")));
	if (gethostname(buf, sizeof(buf)) != 0)
		return (ft_strdup("host"));
	return (ft_strdup(buf));
}

// Build_promt
char	*build_prompt(t_prompt *p)
{
	char	*tmp;
	char	*tmp2;
	char	*out;

	tmp = ft_strjoin(p->user, "@");
	tmp2 = ft_strjoin(tmp, p->host);
	free(tmp);
	tmp = ft_strjoin(tmp2, ":");
	free(tmp2);
	tmp2 = ft_strjoin(tmp, p->cwd);
	free(tmp);
	out = ft_strjoin(tmp2, "$ ");
	free(tmp2);

	return (out);
}

void	free_prompt(t_prompt *p)
{
	if (p->cwd) free(p->cwd);
	if (p->user) free(p->user);
	if (p->host) free(p->host);
	if (p->prompt_str) free(p->prompt_str);
}
