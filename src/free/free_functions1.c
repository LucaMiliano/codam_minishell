/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpieck <lpieck@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 01:40:20 by cpinas            #+#    #+#             */
/*   Updated: 2026/02/11 14:31:47 by lpieck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tokens(t_tokens *lst)
{
	t_tokens	*tmp;

	while (lst)
	{
		tmp = lst->next;
		free(lst->value);
		free(lst);
		lst = tmp;
	}
}

void	free_split(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

void	free_env(char **env) // unused right now;
{
	if (env)
	{
		for (int i = 0; env[i] != NULL; i++)
			free(env[i]);  // Free each string in the array
		free(env);  // Free the array itself
	}
}

// part of promt refactor
// int prompt_exit(t_prompt *p, int is_tty, int saved_stdin, int ret)
// {
// 	dup2(saved_stdin, STDIN_FILENO);
// 	close(saved_stdin);
// 	if (is_tty)
// 		free_prompt(p);
// 	return (ret);
// }
int prompt_exit(t_prompt *p, int is_tty, int saved_stdin, int ret)
{
	if (saved_stdin >= 0)
	{
		dup2(saved_stdin, STDIN_FILENO);
		close(saved_stdin);
	}
	if (is_tty)
		free2_prompt(p);
	return (ret);
}
