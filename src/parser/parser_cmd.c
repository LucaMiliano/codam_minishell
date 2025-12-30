/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpinas <cpinas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 02:48:36 by cpinas            #+#    #+#             */
/*   Updated: 2025/12/30 10:14:01 by cpinas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <string.h>

t_cmd	*cmd_new(void)
{
	t_cmd *cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->argv = NULL;
	cmd->argv_expandable = NULL; //new added to keep metadata
	cmd->redirs = NULL;
	cmd->next = NULL;
	return (cmd);
}


// int	add_word_to_argv(t_cmd *cmd, char *word)
// {
// 	int count = 0;
// 	char **new_argv;

// 	// Count existing argv elements
// 	if (cmd->argv)
// 	{
// 		while (cmd->argv[count])
// 			count++;
// 	}

// 	// Allocate new array (count + 2: +1 for new word, +1 for NULL)
// 	new_argv = malloc(sizeof(char *) * (count + 2));
// 	if (!new_argv)
// 		return 0;

// 	for (int i = 0; i < count; i++)
// 		new_argv[i] = cmd->argv[i];

// 	new_argv[count] = word;  // add the new word
// 	new_argv[count + 1] = NULL;

// 	free(cmd->argv);          // free old pointer (not the strings)
// 	cmd->argv = new_argv;

// 	return 1;
// }
