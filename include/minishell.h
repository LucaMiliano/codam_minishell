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
// typedef struct s_lexer
// {
// 	int	word;
// 	int option;
// 	int num;
// 	int squote;
// 	int dsquote;
// 	int pipt;
// 	int redir_in;
// 	int redir_out;
// 	int append;
// 	int heredoc;
// } t_lexer;

enum e_toktype
{
	TOK_WORD,
	TOK_PIPE,
	TOK_REDIR_IN, // <
	TOK_REDIR_OUT, // >
	TOK_APPEND, // >>
	TOK_HEREDOC, // <<
};

typedef struct s_tokens
{
	char			*value;
	enum e_toktype	type;
	struct s_tokens	*next;
}	t_tokens;

// functions
//////////////////
//    prompt    //
//////////////////
void	prompt(void);
void	setup_signals(void);
void	sigint_handler(int sig);
int		ft_streq(const char *s1, const char *s2);
char	*get_current_directory(void);
char	*get_username(void);
char	*get_hostname(void);
int		is_space(char c);
int		is_operator(char c);
int		 operator_len(char *s);

#endif


