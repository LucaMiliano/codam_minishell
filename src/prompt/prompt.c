/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpinas <cpinas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 13:37:58 by cpinas            #+#    #+#             */
/*   Updated: 2025/12/30 10:46:38 by cpinas           ###   ########.fr       */
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

	builtin_history(line);
	return (1); // continue loop
}

// int execute_builtins(char *line)
// {
// 	builtin_history(line);
// 	return (0);
// }

int builtin_history(char *line)
{
	if (!ft_strncmp(line, "history -c", 11))
	{
		clear_history();
		write(1, "history cleared\n", 10);
		return (1);
	}
	return (0);
}
// void prompt(void)
// {
// 	char *line;
// 	t_tokens *tokens;
// 	t_prompt p;
// 	t_cmd *cmds;

// 	if (!isatty(STDIN_FILENO))
// 		return ;
// 	while (1)
// 	{
// 		p.cwd = get_current_directory(); // start de struct
// 		p.user = get_username();
// 		p.host = get_hostname();
// 		color_prompt(&p); // kleur invullen (kan ook helemaal in struct)
// 		line = readline(p.prompt_str); // Prompt stdout

// 		if (!handle_input(line))
// 		{
// 			free_prompt(&p);
// 			free(line);
// 			break; // CTRL-D exit
// 		}
// 		// Tokenization & debug
// 		tokens = tokenize(line);
// 		print_tokens_debug(tokens);	// debug
// 		print_tokens(tokens);	// debug
// 		// t_tokens *tokens = tokenize(line);
// 		cmds = parse(tokens);
// 		print_pipeline(cmds); // debug
// 		// Free resources for this loop iteration
// 		free_prompt(&p);
// 		free_tokens(tokens);
// 		free(line);
// 	}
// }


// char	*prompt(void)
// {
// 	char *line;
// 	t_tokens *tokens;
// 	t_prompt p;
// 	t_cmd *cmds;

// 	if (!isatty(STDIN_FILENO))
// 		return;

// 	while (1)
// 	{
// 		// Build prompt
// 		p.cwd = get_current_directory();
// 		p.user = get_username();
// 		p.host = get_hostname();
// 		color_prompt(&p);
// 		line = readline(p.prompt_str);

// 		if (!handle_input(line))
// 		{
// 			free_prompt(&p);
// 			free(line);
// 			break;
// 		}

// 		// Tokenize and debug
// 		tokens = tokenize(line);
// 		print_tokens_debug(tokens);
// 		print_tokens(tokens);

// 		// Parse tokens into commands
// 		cmds = parse(tokens);
// 		if (!cmds)
// 		{
// 			write(2, "Parser returned NULL\n", 21);
// 			free_tokens(tokens);
// 			free_prompt(&p);
// 			free(line);
// 			continue; // skip this iteration safely
// 		}
// 		// Print pipeline debug
// 		print_pipeline(cmds);

// 		// Free lexer tokens (pipeline owns its strings now)
// 		free_tokens(tokens);

// 		// TODO: here is where execution will happen in the future
// 		// After execution, free the pipeline
// 		free_cmd_pipeline(cmds);

// 		// Free prompt and input line
// 		free_prompt(&p);
// 		free(line);
// 	}
// }

// char *prompt(char **envp)
// {
// 	char *line;
// 	t_tokens *tokens;
// 	t_prompt p;
// 	t_cmd *cmds;

// 	if (!isatty(STDIN_FILENO))
// 		return NULL;

// 	while (1)
// 	{
// 		// Build prompt
// 		p.cwd = get_current_directory();
// 		p.user = get_username(envp);
// 		p.host = get_hostname();
// 		color_prompt(&p);
// 		line = readline(p.prompt_str);

// 		if (!handle_input(line))
// 		{
// 			free_prompt(&p);
// 			free(line);
// 			break;
// 		}

// 		// Tokenize
// 		tokens = tokenize(line);
// 		print_tokens_debug(tokens);  // optional debug
// 		print_tokens(tokens);        // optional debug

// 		// Parse
// 		cmds = parse(tokens);
// 		free_tokens(tokens);
// 		if (!cmds)
// 		{
// 			write(2, "Parser returned NULL\n", 21);
// 			free_prompt(&p);
// 			free(line);
// 			continue;
// 		}

// 		// Prepare heredocs
// 		if (prepare_heredocs(cmds) != 0)
// 		{
// 			free_cmd_pipeline(cmds);
// 			free_prompt(&p);
// 			free(line);
// 			continue;
// 		}

// 		// Execute pipeline
// 		execute_pipeline(cmds, envp);

// 		// Free the pipeline after execution
// 		free_cmd_pipeline(cmds);

// 		free_prompt(&p);
// 		free(line);
// 	}

// 	return (NULL);
// }

char *prompt()
{
	char		*line;
	t_tokens	*tokens;
	t_prompt	p;
	t_cmd		*cmds;

	if (!isatty(STDIN_FILENO))
		return NULL;

	while (1)
	{
		// Build prompt
		p.cwd = get_current_directory();
		p.user = get_username();  // old function that needs envp
		p.host = get_hostname();
		color_prompt(&p);             // builds p.prompt_str

		line = readline(p.prompt_str);
		if (!line) // Ctrl-D / EOF
		{
			free_prompt(&p);
			break;
		}

		if (!handle_input(line)) // optional: empty or invalid input
		{
			free_prompt(&p);
			free(line);
			break;
		}

		// Tokenize input
		tokens = tokenize(line);
		// print_tokens_debug(tokens); // optional debug commented out for clarity
		// print_tokens(tokens);       // optional debug

		// Parse tokens into commands
		cmds = parse(tokens);
		free_tokens(tokens); // pipeline now owns the strings

		expand_pipeline(cmds);

		if (!cmds)
		{
			write(2, "Parser returned NULL\n", 21);
			free_prompt(&p);
			free(line);
			continue; // safely skip to next iteration
		}

		// print_pipeline(cmds); // optional debug commanted out

		// Prepare heredocs
		if (prepare_heredocs(cmds) != 0)
		{
			free_cmd_pipeline(cmds);
			free_prompt(&p);
			free(line);
			continue;
		}

		// Execute pipeline
		execute_pipeline(cmds);

		// Free pipeline after execution
		free_cmd_pipeline(cmds);

		// Free prompt and input line
		free_prompt(&p);
		free(line);
	}

	return (NULL);
}


// char *prompt(void)
// {
// 	char        *line;
// 	t_tokens    *tokens;
// 	t_prompt    p;
// 	t_cmd       *cmds;
// 	extern char **environ; // standard global env

// 	if (!isatty(STDIN_FILENO))
// 		return NULL;

// 	while (1)
// 	{
// 		// Build prompt
// 		p.cwd = get_current_directory();
// 		p.user = get_username();
// 		p.host = get_hostname();
// 		color_prompt(&p);
// 		line = readline(p.prompt_str);

// 		if (!handle_input(line)) // Ctrl-D or invalid input
// 		{
// 			free_prompt(&p);
// 			free(line);
// 			break;
// 		}

// 		// Tokenize input
// 		tokens = tokenize(line);
// 		print_tokens_debug(tokens);
// 		print_tokens(tokens);

// 		// Parse tokens into commands
// 		cmds = parse(tokens);
// 		if (!cmds)
// 		{
// 			write(2, "Parser returned NULL\n", 21);
// 			free_tokens(tokens);
// 			free_prompt(&p);
// 			free(line);
// 			continue;
// 		}
// 		print_pipeline(cmds);

// 		// Free tokens (pipeline owns strings now)
// 		free_tokens(tokens);

// 		// Prepare heredocs
// 		if (prepare_heredocs(cmds) != 0)
// 		{
// 			free_cmd_pipeline(cmds);
// 			free_prompt(&p);
// 			free(line);
// 			continue;
// 		}

// 		// Execute the pipeline
// 		execute_pipeline(cmds, environ);

// 		// Free pipeline after execution
// 		free_cmd_pipeline(cmds);

// 		// Free prompt and input line
// 		free_prompt(&p);
// 		free(line);
// 	}
// 	return NULL;
// }
