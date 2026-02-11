/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpinas <cpinas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 20:29:16 by cpinas            #+#    #+#             */
/*   Updated: 2026/02/11 20:29:35 by cpinas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <unistd.h>

int	build_prompt1(t_shell *shell, t_prompt *p, int is_tty)
{
	if (!is_tty)
		return (1);
	p->cwd = get_current_directory();
	p->user = get_username(shell);
	p->host = get_hostname();
	color_prompt(p);
	return (1);
}

int	handle_line(char *line, t_prompt *p, int is_tty)
{
	int	ret;

	ret = handle_input(line);
	if (ret == 1)
		return (1);
	free(line);
	if (is_tty)
		free2_prompt(p);
	if (ret == 0)
		return (0);
	return (-1);
}
