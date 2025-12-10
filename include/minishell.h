#ifndef MINISHELL_H
#define MINISHELL_H

#include "libft.h"

/*
Type definitions:
1 = WORD
2 = OPTION
3 = NUM
4 = SQUOTE
5 = DQUOTE
6 = PIPE
7 = REDIR_IN
8 = REDIR_OUT
9 = APPEND
10 = HEREDOC
*/
typedef struct s_lexer
{
	int	word;
	int option;
	int num;
	int squote;
	int dsquote;
	int pipt;
	int redir_in;
	int redir_out;
	int append;
	int heredoc;
} t_lexer;

typedef struct s_tokens
{
	char			*str;
	int				type;
	struct s_tokens	*next;
}	t_tokens;

// functions
//////////////////
//    promt     //
//////////////////
void	prompt(void);
void	setup_signals(void);
void	sigint_handler(int sig);
int		ft_streq(const char *s1, const char *s2);
char	*get_current_directory(void);
char	*get_username(void);
char	*get_hostname(void);

#endif


