/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpinas <cpinas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 13:37:58 by cpinas            #+#    #+#             */
/*   Updated: 2025/12/10 22:47:34 by cpinas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <unistd.h>

static int	handle_input(char *line)
{
	if (!line)
	{
		write(1, "exit\n", 5);
		return (0); // break stop de loop
	}
	if (*line)
		add_history(line);
	if (!ft_strncmp(line, "history -c", 11))
	{
		clear_history();
		write(1, "history cleared\n", 16);
	}
	return 1; // continue loop
}

void prompt(void)
{
	char *line;
	t_tokens *tokens;
	t_prompt p;

	while (1)
	{
		p.cwd = get_current_directory(); // start de struct
		p.user = get_username();
		p.host = get_hostname();
		color_prompt(&p); // kleur invullen (kan ook helemaal in struct)
		line = readline(p.prompt_str); // Prompt stdout

		if (!handle_input(line))
		{
			free_prompt(&p);
			free(line);
			break; // CTRL-D exit
		}
		// Tokenization & debug
		tokens = tokenize(line);
		print_tokens2(tokens);
		print_tokens(tokens);
		// Free resources for this loop iteration
		free_prompt(&p);
		free_tokens(tokens);
		free(line);
	}
}
