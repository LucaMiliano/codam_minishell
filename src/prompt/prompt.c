/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpieck <lpieck@student.codam.nl>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 13:37:58 by cpinas            #+#    #+#             */
/*   Updated: 2026/02/03 15:33:42 by lpieck           ###   ########.fr       */
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
		return (0);
	}
	if (*line)
		add_history(line);

	if (builtin_history(line))
		return(2);
	return(1);
}

int builtin_history(char *line)
{
	if (!ft_strncmp(line, "history -c", 10))
	{
		clear_history();
		write(1, "history cleared\n", 17);
		return (1);
	}
	return (0);
}

// static char * get_input_line(t_shell *shell, t_prompt *p, int is_tty)
// {
// 	char	*line;

// 	if (is_tty)
// 	{
// 		p->cwd = get_current_directory();
// 		p->user = get_username(shell);
// 		p->host = get_hostname();
// 		color_prompt(p);
// 		line = readline(p->prompt_str);
// 	}
// 		else
// 	{
// 		char	buf[4096];
// 		ssize_t	bytes_read = read(STDIN_FILENO, buf, sizeof(buf) - 1);
// 		if (bytes_read <= 0)
// 			return (NULL);
// 		buf[bytes_read] = '\0';
// 		if (bytes_read > 0 && buf[bytes_read - 1] == '\n')
// 			buf[bytes_read - 1] = '\0';
// 		line = ft_strdup(buf);
// 	}
// 	return (line);
// }

// static int	handle_user_input(char *line)
// {
// 	if (!line)
// 		return (0); // exit on EOF or error
// 	if (*line)
// 		add_history(line); // add line to history
// 	if (builtin_history(line))
// 		return (2); // built-in command, skip further execution
// 	return (1); // continue with execution
// }

// static t_cmd	*parse_and_tokenize(char *line)
// {
// 	t_tokens	*tokens;
// 	t_cmd		*cmds;

// 	tokens = tokenize(line); // tokenize input
// 	cmds = parse(tokens);    // parse tokens into commands
// 	free_tokens(tokens);     // free tokens as the pipeline owns them

// 	return (cmds);
// }

// static int	execute_command(t_shell *shell, t_cmd *cmds)
// {
// 	expand_pipeline(cmds, shell);
// 	if (prepare_heredocs(shell, cmds) != 0)
// 	{
// 		free_cmd_pipeline(cmds);
// 		return (0); // error in heredoc preparation
// 	}
// 	execute_pipeline(shell, cmds);
// 	free_cmd_pipeline(cmds); // cleanup after execution
// 	return (1); // success
// }

// static void	cleanup(t_prompt *p, char *line, int is_tty)
// {
// 	if (is_tty)
// 		free_prompt(p);
// 	free(line);
// }

// char	*prompt(t_shell *shell)
// {
// 	char		*line;
// 	t_cmd		*cmds;
// 	t_prompt	p;
// 	int			is_tty;
// 	int			ret;

// 	is_tty = isatty(STDIN_FILENO);
// 	while (1)
// 	{
// 		line = get_input_line(shell, &p, is_tty);
// 		if (!line || !(ret = handle_user_input(line)))
// 		{
// 			cleanup(&p, line, is_tty);
// 			break;
// 		}
// 		cmds = parse_and_tokenize(line);
// 		if (!cmds)
// 		{
// 			cleanup(&p, line, is_tty);
// 			continue; // skip iteration if parsing failed
// 		}
// 		if (!execute_command(shell, cmds))
// 		{
// 			cleanup(&p, line, is_tty);
// 			continue; // continue to next iteration on error
// 		}
// 		cleanup(&p, line, is_tty); // clean up at the end of loop
// 	}
// 	return (NULL);
// }

int prompt(t_shell *shell)
{
	char		*line;
	t_tokens	*tokens;
	t_prompt	p;
	t_cmd		*cmds;
	int			is_tty;
	int			ret;
	int			saved_stdin;

	is_tty = isatty(STDIN_FILENO);
	saved_stdin = dup(STDIN_FILENO);
	
	// Build prompt
	if (is_tty)
	{
		p.cwd = get_current_directory();
		p.user = get_username(shell);
		p.host = get_hostname();
		color_prompt(&p);
	}

	if (is_tty)
		line = readline(p.prompt_str);
	else 
	{
		char buf[4096];
		ssize_t bytes_read = read(STDIN_FILENO, buf, sizeof(buf) - 1);
		if (bytes_read <= 0)
			return (0);
		buf[bytes_read] = '\0';
		if (buf[bytes_read - 1] == '\n')
			buf[bytes_read - 1] = '\0';
		line = ft_strdup(buf);
	}

	if (!line)
	{
		if (is_tty)
			free2_prompt(&p);  //new toegevoegd op falen.
		return (0);
	}
	ret = handle_input(line);
	if (ret == 0)
	{
		free(line);
		if (is_tty)
			free2_prompt(&p);  //new toegevoegd op falen.
		return (0);
	}
	if (ret == 2)
	{
		free(line);
		if (is_tty)
			free2_prompt(&p);  //new toegevoegd op falen.
		return (1);
	}

	tokens = tokenize(line);
	cmds = parse(tokens);
	free_tokens(tokens);

	if (!cmds)
	{
		free(line);
		if (is_tty)
			free2_prompt(&p);  //new toegevoegd op falen.
		return (1);
	}

	expand_pipeline(cmds, shell);

	if (prepare_heredocs(shell, cmds) != 0)
	{
		free_cmd_pipeline(cmds);
		free(line);
		if (is_tty)
			free2_prompt(&p);  //new toegevoegd op falen.
		return (1);
	}

	execute_pipeline(shell, cmds);
	free_cmd_pipeline(cmds);
	free(line);

	dup2(saved_stdin, STDIN_FILENO);
	close(saved_stdin);
	if (is_tty)
		free_prompt(&p);

	return (1);
}


// char *prompt(t_shell *shell) // updated: *prompt() -> *prompt(t_shell *shell) //
// {
// 	char		*line;
// 	t_tokens	*tokens;
// 	t_prompt	p;
// 	t_cmd		*cmds;
// 	int			is_tty;

// 	is_tty = isatty(STDIN_FILENO);

// 	while (1)
// 	{
// 		// Build prompt only if TTY
// 		if (is_tty)
// 		{
// 			p.cwd = get_current_directory();
// 			p.user = get_username(shell);
// 			p.host = get_hostname();
// 			color_prompt(&p);
// 			line = readline(p.prompt_str);
// 		}
// 		else
// 		{
// 			char buf[4096];
// 			ssize_t bytes_read = read(STDIN_FILENO, buf, sizeof(buf) -1);
// 			if (bytes_read <= 0)
// 			{
// 				if(is_tty)
// 					free_prompt(&p);
// 				break ;
// 			}
// 			buf[bytes_read] = '\0';
// 			if (bytes_read > 0 && buf[bytes_read - 1] == '\n')
// 			buf[bytes_read - 1] = '\0';

// 			line = ft_strdup(buf);
// 		}

// 		if (!line)
// 		{
// 			if (is_tty)
// 				free_prompt(&p);
// 			break;
// 		}

// 		int ret = handle_input(line);
// 		if (ret == 0)
// 		{
// 			if (is_tty)
// 				free_prompt(&p);
// 			free(line);
// 			break;
// 		}
// 		if (ret == 2)
// 		{
// 			if (is_tty)
// 				free_prompt(&p);
// 			free(line);
// 			continue;
// 		}

// 		// Tokenize input
// 		tokens = tokenize(line);
// 		// print_tokens_debug(tokens); // optional debug commented out for clarity
// 		// print_tokens(tokens);       // optional debug

// 		// Parse tokens into commands
// 		cmds = parse(tokens);
// 		free_tokens(tokens); // pipeline now owns the strings


// 		if (!cmds)
// 		{
// 			// write(2, "Parser returned NULL\n", 21);
// 			if (is_tty)
// 			free_prompt(&p);
// 			free(line);
// 			continue; // safely skip to next iteration
// 		}

// 		expand_pipeline(cmds, shell);
// 		// print_pipeline(cmds); // optional debug commanted out

// 		// Prepare heredocs
// 		if (prepare_heredocs(shell, cmds) != 0) // might need shell later for now leave
// 		{
// 			free_cmd_pipeline(cmds);
// 			if (is_tty)
// 				free_prompt(&p);
// 			free(line);
// 			continue;
// 		}

// 		// Execute pipeline
// 		execute_pipeline(shell, cmds);

// 		// Free pipeline after execution
// 		free_cmd_pipeline(cmds);

// 		// Free prompt and input line
// 		if (is_tty)
// 			free_prompt(&p);
// 		free(line);
// 	}

// 	return (NULL);
// }



