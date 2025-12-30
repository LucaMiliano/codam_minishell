/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpinas <cpinas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 17:13:15 by cpinas            #+#    #+#             */
/*   Updated: 2025/12/30 10:48:31 by cpinas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

/*
** Return value of variable name starting at s[0]
** consumed = how many chars we ate from original string
*/
static char *get_var_value(const char *s, int *consumed)
{
	char	*name;
	char	*value;
	int		len;

	// Special case: $?
	if (s[0] == '?')
	{
		*consumed = 1;
		return (ft_itoa(g_shell.last_status));
	}
	len = 0;
	while (s[len] && (ft_isalnum(s[len]) || s[len] == '_'))
		len++;
	if (len == 0)
	{
		*consumed = 0;
		return (ft_strdup("$"));
	}
	name = ft_substr(s, 0, len);
	if (!name)
		return (NULL);

	value = find_in_env(name);
	free(name);
	*consumed = len;
	if (!value)
		return (ft_strdup(""));
	return (ft_strdup(value));
}

/*
** Expand one word ($VAR, $?)
*/
char *expand_word(char *word)
{
	int		i;
	int		consumed;
	char	*result;
	char	*tmp;
	char	*value;

	i = 0;
	result = ft_strdup("");
	if (!result)
		return (NULL);

	while (word[i])
	{
		if (word[i] == '$')
		{
			value = get_var_value(&word[i + 1], &consumed);
			if (!value)
				return (free(result), NULL);

			tmp = ft_strjoin(result, value);
			free(result);
			free(value);
			result = tmp;

			if (!result)
				return (NULL);
			i += consumed + 1;
		}
		else
		{
			tmp = ft_strjoin_char(result, word[i]); //not ft_strjoin_char
			free(result);
			result = tmp;

			if (!result)
				return (NULL);
			i++;
		}
	}
	return (result);
}

/*
** Expand argv and redirections for entire pipeline
*/
// void	expand_pipeline(t_cmd *cmds)
// {
// 	int		i;
// 	char	*expanded;
// 	t_redir	*r;

// 	while (cmds)
// 	{
// 		i = 0;
// 		while (cmds->argv && cmds->argv[i])
// 		{
// 			expanded = expand_word(cmds->argv[i]);
// 			if (expanded)
// 			{
// 				free(cmds->argv[i]);
// 				cmds->argv[i] = expanded;
// 			}
// 			i++;
// 		}

// 		r = cmds->redirs;
// 		while (r)
// 		{
// 			if (r->expandable)
// 			{
// 				expanded = expand_word(r->target);
// 				if (expanded)
// 				{
// 					free(r->target);
// 					r->target = expanded;
// 				}
// 			}
// 			r = r->next;
// 		}
// 		cmds = cmds->next;
// 	}
// }

void	expand_pipeline(t_cmd *cmds)
{
	int		i;
	char	*expanded;
	t_redir	*r;

	while (cmds)
	{
		i = 0;
		while (cmds->argv && cmds->argv[i])
		{
			if (cmds->argv_expandable[i])
			{
				expanded = expand_word(cmds->argv[i]);
				if (expanded)
				{
					free(cmds->argv[i]);
					cmds->argv[i] = expanded;
				}
			}
			i++;
		}

		r = cmds->redirs;
		while (r)
		{
			if (r->expandable)
			{
				expanded = expand_word(r->target);
				if (expanded)
				{
					free(r->target);
					r->target = expanded;
				}
			}
			r = r->next;
		}
		cmds = cmds->next;
	}
}

