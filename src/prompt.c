/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpinas <cpinas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 13:37:58 by cpinas            #+#    #+#             */
/*   Updated: 2025/12/09 23:55:30 by cpinas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <signal.h> //header for signals

// de kleine functies in deze folder kunnen tzt in utils.c of iets dergelijks
// heb ze voor nu bij elkaar gelaten zodat we precies kunnen zien wat, wat does.
// maar kan het altijd nog opdelen
int	ft_streq(const char *s1, const char *s2)
{
	return (ft_strncmp(s1, s2, ft_strlen(s1) + 1) == 0);
}
// this might need to be replaced later on.
// It's simple signal handler and prompting the signals
void	setup_signals(void)
{
	signal(SIGINT, sigint_handler);		// Ctrl-C: interrupt and refresh prompt
	signal(SIGQUIT, SIG_IGN);			// Ctrl-\ : ignored
}
// specifically for prompt at this point, Don't know if more utility is usefull lateron
// handles cntrl-c (sigint) while in prompt.
// prints newline, clears the current input line, shows fresh prompt
void	sigint_handler(int sig)
{
	(void)sig;
	write(1, "\n",1);
	rl_replace_line("",0);
	rl_on_new_line();
	rl_redisplay();
}

void	prompt(void)
{
	// stuk tussen **** toegevoegd voor, de juiste username handling (zie helperfuncties)
	char	*line = NULL;
	char	*cwd;
	char	*username;
	char	*hostname;

	while (1) // while(1) betekent net als op examens gewoon blijven runnen tot sint jutimis
	{
			// Get dynamic values
		cwd = get_current_directory(); // Get current working directory
		username = get_username();     // Get the username
		hostname = get_hostname();     // Get the hostname

		// Construct and display the prompt
		char *prompt_str = malloc(strlen(username) + strlen(hostname) + strlen(cwd) + 20);
		if (!prompt_str) {
			perror("malloc");
			exit(EXIT_FAILURE);
		}

		// Construct the prompt: user@hostname:current_directory$
		sprintf(prompt_str, "%s@%s:%s$ ", username, hostname, cwd); // unsafe function ook illigaal voor minishell, maar wel snel en duidelijk voor nu. kan vervangen andere functies tzt.
		line = readline(prompt_str);
		// line = readline("prompt> "); // geen prompt meer readline positie hierboven neemt over
		// Clean up
		free(cwd);
		free(hostname);
		free(prompt_str);
		// **** tot hier ongeveer voor de nieuwe setup met dynamishe naam
		if (!line)		// Ctrl-D
		{
			printf("exit\n");
			free(line);
			break ;
		}

		if (*line)		// If not empty, add to history
		add_history(line);

		if (ft_streq(line, "history -c"))
		{
			clear_history();
			printf("history cleared\n");
			continue ;
		}
		free(line);
	}
}
// rl_replace_line("", 0);	// clear the current line
// rl_on_new_line();		// move to new line
// rl_redisplay();			// redraw prompt

char	*get_current_directory(void)
{
	char	*cwd;
	cwd = malloc(1024); //buffer voor current working directory
	if (!cwd)
	{
		perror("malloc dirctorypath buffer"); // tijdelijk aangepast aan eind als alles werkt
		exit(EXIT_FAILURE);
	}
	// get current (working) directory
	if (getcwd(cwd, 1024)== NULL)
	{
		perror("getcwd"); // weer weten waar het is foutgegaan.
		free(cwd);
		exit(EXIT_FAILURE);
	}
	// if in the home directory, replacestring with ~ (net als bash)
	char	*home;
	home = getenv("HOME");
	if (home && ft_strncmp(cwd, home, ft_strlen(home)) == 0)
	{
		char	*tilde;
		tilde = malloc(ft_strlen(cwd) - ft_strlen(home) + 2); // voor '~/' plus vervolg
		if (!tilde)
		{
			perror("malloc inside tildemalloc get_current_directory");
			free(cwd);
			exit(EXIT_FAILURE);
		}
		tilde[0] = '~';
		ft_strlcpy(tilde + 1, cwd + ft_strlen(home), ft_strlen(cwd) - ft_strlen(home) + 1);
		free(cwd);
		return (tilde);
	}
	return (cwd);
} // kan deze functie ook herschrijven met ft_strdup, dan is die veel korter.
// mss een idee aan het einde als we alles netjes maken voor nu kan je goed zien wat
// er gebeurd en internalizeren. Dus voor het lees"gemak" veel code voor inzichtelijkheid
// complexiteit

char	*get_username(void)
{
	char *username;
	username = getenv("USER"); // getenv: zoekt een "environmentvariable"
	if (username != NULL)
		return (username); // geeft gebruikersnaam als die gevonden is
	else
		return ("user"); // standin voor gebruikersnaam als geen gevonden is
}
char	*get_hostname(void)
{
	char	*hostname;

	hostname = getenv("HOSTNAME"); // zelfde als hierboven zoekt omgevingvariabele
	if(!hostname)
	{
		hostname = malloc(256);
		if (gethostname(hostname, 256) != 0) // POSIX is hostname_max (minstens 64) / voor linux 64 of 255 dus dit is overflow veilig
		{
			perror("gethostname");
			exit(EXIT_FAILURE);
		}
	}
	return (hostname);
}
