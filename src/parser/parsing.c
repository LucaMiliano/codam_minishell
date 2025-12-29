/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpinas <cpinas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 15:25:48 by lpieck            #+#    #+#             */
/*   Updated: 2025/12/22 00:39:00 by cpinas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
	- tokens defined in tokenization.c should be parsed into command pipeline here
	- Validate syntax here (e.g., pipe at ends, consecutive pipes, missing filename)
*/
// Step 2: handle new command (if necessary)
// Step 3: handle redirections
// Step 4: handle WORD tokens (argv)
// Step 5: handle PIPE tokens (split commands)

#include "minishell.h"
/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
////			refactor ideas not complete yet but close			/////
/////////////////////////////////////////////////////////////////////////
// t_cmd	*parse(t_tokens *tokens)
// {
// 	t_cmd	*head;
// 	t_cmd	*current;

// 	if (!check_pipe_syntax(tokens))
// 		return (NULL);
// 	head = NULL;
// 	current = NULL;
// 	while (tokens)
// 	{
// 		if (!current)
// 			current = parse_start_cmd(&head);
// 		if (!current)
// 			return (NULL);
// 		if (!parse_token(&tokens, &current, &head))
// 			return (NULL);
// 	}
// 	return (head);
// }

// int	parse_token(t_tokens **tokens, t_cmd **current, t_cmd **head)
// {
// 	if ((*tokens)->type == TOK_WORD)
// 		return (parse_word(tokens, *current));
// 	if ((*tokens)->type == TOK_PIPE)
// 		return (parse_pipe(tokens, current));
// 	if (is_redir((*tokens)->type))
// 		return (parse_redir(tokens, *current, head));
// 	*tokens = (*tokens)->next;
// 	return (1);
// }

// int	parse_word(t_tokens **tokens, t_cmd *cmd)
// {
// 	cmd->argv = argv_add(cmd->argv, (*tokens)->value);
// 	if (!cmd->argv)
// 		return (0);
// 	*tokens = (*tokens)->next;
// 	return (1);
// }

// int	parse_pipe(t_tokens **tokens, t_cmd **current)
// {
// 	t_cmd	*next;

// 	next = cmd_new();
// 	if (!next)
// 		return (0);
// 	(*current)->next = next;
// 	*current = next;
// 	*tokens = (*tokens)->next;
// 	return (1);
// }

// int	parse_redir(t_tokens **tokens, t_cmd *cmd, t_cmd **head)
// {
// 	if ((*tokens)->type == TOK_HEREDOC)
// 		return (parse_heredoc(tokens, cmd, head));
// 	return (parse_file_redir(tokens, cmd, head));
// }

// int	parse_file_redir(t_tokens **tokens, t_cmd *cmd, t_cmd **head)
// {
// 	t_tokens	*file;
// 	t_redir		*redir;

// 	file = (*tokens)->next;
// 	if (!file || file->type != TOK_WORD)
// 		return (redir_syntax_error(head));
// 	redir = redir_new(redir_type((*tokens)->type),
// 			file->value, file->expandable);
// 	if (!redir)
// 		return (redir_alloc_error(head));
// 	cmd_add_redir(cmd, redir);
// 	*tokens = file->next;
// 	return (1);
// }
// int	parse_heredoc(t_tokens **tokens, t_cmd *cmd, t_cmd **head)
// {
// 	t_tokens	*delim;
// 	t_redir		*redir;

// 	delim = (*tokens)->next;
// 	if (!delim || delim->type != TOK_WORD)
// 		return (heredoc_syntax_error(head));
// 	redir = redir_new(R_HEREDOC, delim->value, delim->expandable);
// 	if (!redir)
// 		return (heredoc_alloc_error(head));
// 	cmd_add_redir(cmd, redir);
// 	*tokens = skip_heredoc_body(delim);
// 	return (1);
// }
// t_tokens	*skip_heredoc_body(t_tokens *delim)
// {
// 	t_tokens	*cur;

// 	cur = delim->next;
// 	while (cur)
// 	{
// 		if (cur->type == TOK_WORD
// 			&& ft_strcmp(cur->value, delim->value) == 0)
// 			return (cur->next);
// 		cur = cur->next;
// 	}
// 	return (NULL);
// }
/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
////			refactor ideas not complete above ^					/////
/////////////////////////////////////////////////////////////////////////

t_cmd *parse(t_tokens *tokens)
{
	if (!check_pipe_syntax(tokens))
		return (NULL);

	t_cmd *head = NULL;
	t_cmd *current = NULL;

	while (tokens)
	{
		if (!current)
		{
			current = cmd_new();
			if (!current)
				return (NULL);
			if (!head)
				head = current;
		}

		if (tokens->type == TOK_WORD)
		{
			current->argv = argv_add(current->argv, tokens->value);
			if (!current->argv)
			{
				free_cmd_pipeline(head);
				return (NULL);
			}
		}
		else if (tokens->type == TOK_PIPE)
		{
			t_cmd *next_cmd = cmd_new();
			if (!next_cmd)
			{
				free_cmd_pipeline(head);
				return (NULL);
			}
			current->next = next_cmd;
			current = next_cmd;
		}
		else if (tokens->type == TOK_REDIR_IN || tokens->type == TOK_REDIR_OUT || tokens->type == TOK_APPEND)
		{
			t_tokens *file_token = tokens->next;
			if (!file_token || file_token->type != TOK_WORD)
			{
				write(2, "minishell: syntax error near redirection\n", 41);
				free_cmd_pipeline(head);
				return NULL;
			}

			t_redir_type rtype;
			if (tokens->type == TOK_REDIR_IN) rtype = R_IN;
			else if (tokens->type == TOK_REDIR_OUT) rtype = R_OUT;
			else rtype = R_APPEND;

			t_redir *redir = redir_new(rtype, file_token->value, file_token->expandable);
			if (!redir)
			{
				free_cmd_pipeline(head);
				return (NULL);
			}

			cmd_add_redir(current, redir);
			tokens = file_token; // skip filename
		}
		else if (tokens->type == TOK_HEREDOC)
		{
			t_tokens *delimiter_token = tokens->next;
			if (!delimiter_token || delimiter_token->type != TOK_WORD)
			{
				write(2, "minishell: syntax error near heredoc\n", 37);
				free_cmd_pipeline(head);
				return (NULL);
			}

			// create redir for HEREDOC with the delimiter
			t_redir *redir = redir_new(R_HEREDOC, delimiter_token->value, delimiter_token->expandable);
			if (!redir)
			{
				free_cmd_pipeline(head);
				return (NULL);
			}
			cmd_add_redir(current, redir);

			// skip delimiter token
			tokens = delimiter_token;

			// skip all tokens until we reach a token equal to the delimiter
			t_tokens *heredoc_content = tokens->next;
			while (heredoc_content)
			{
				if (heredoc_content->type == TOK_WORD &&
					ft_strncmp(heredoc_content->value, delimiter_token->value,
						ft_strlen(delimiter_token->value)) == 0)
				{
					tokens = heredoc_content; // stop at closing delimiter
					break;
				}
				heredoc_content = heredoc_content->next;
			}
		}

		tokens = tokens->next;
	}

	return (head);
}
