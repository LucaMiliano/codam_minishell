/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpinas <cpinas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 20:49:43 by cpinas            #+#    #+#             */
/*   Updated: 2026/02/05 09:44:54 by cpinas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

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
	home = getenv ("HOME");
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

char	*get_username(t_shell *shell)
{
	char	*val;

	val = find_in_env(shell, "USER");
	if (val != NULL)
		return (ft_strdup(val));
	return (ft_strdup("user"));
}

char	*get_hostname(void)
{
	int		fd;
	int		n;
	char	buf[256];

	fd = open("/etc/hostname", O_RDONLY);
	if (fd < 0)
		return (ft_strdup("host"));
	n = read(fd, buf, 255);
	close(fd);
	if (n <= 0)
		return (ft_strdup("host"));
	buf[n] = '\0';
	if (buf[n - 1] == '\n')
		buf[n - 1] = '\0';
	return (ft_strdup(buf));
}

char	*build_prompt(t_prompt *p)
{
	char	*tmp;
	char	*tmp2;
	char	*out;

	if (!p->user || !p->host || !p->cwd)
		return (NULL);
	tmp = ft_strjoin(p->user, "@");
	if (!tmp)
		return (NULL);
	tmp2 = ft_strjoin(tmp, p->host);
	free(tmp);
	if (!tmp2)
		return (NULL);
	tmp = ft_strjoin(tmp2, ":");
	free(tmp2);
	if (!tmp)
		return (NULL);
	tmp2 = ft_strjoin(tmp, p->cwd);
	free(tmp);
	if (!tmp2)
		return (NULL);
	out = ft_strjoin(tmp2, "$ ");
	free(tmp2);
	return (out);
}

void	free_prompt(t_prompt *p)
{
	if (p->cwd)
		free(p->cwd);
	if (p->user)
		free(p->user);
	if (p->host)
		free(p->host);
	if (p->prompt_str)
		free(p->prompt_str);
}
