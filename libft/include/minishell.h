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

//////////////////
//   colors     //
//////////////////
#define RESET   "\001\033[0m\002"
#define RED     "\001\033[1;31m\002"
#define GREEN   "\001\033[1;32m\002"
#define YELLOW  "\001\033[1;33m\002"
#define CYAN    "\001\033[1;36m\002"
#define BLUE    "\001\033[1;34m\002"
#define MAGENTA "\001\033[1;35m\002"
#define CYAN    "\001\033[1;36m\002"
#define WHITE   "\001\033[1;37m\002"

typedef struct s_prompt
{
	char	*cwd;
	char	*user;
	char	*host;
	char	*prompt_str;
}	t_prompt;

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
	int				expandable;	// boolian 1 / 0 (noodzakelijk voor toekomst)
	int				quoted; 	// 0: no quote, 1: single quote, 2: double quote (uitzonderingen)
	struct s_tokens	*next;
}	t_tokens;


// functions
//////////////////
//    promt     //
//////////////////
// prompt
void		prompt(void);

// signals
void		setup_signals(void);
void		sigint_handler(int sig);

// prompt utils
char		*get_current_directory(void);
char		*get_username(void);
char		*get_hostname(void);
char		*build_prompt(t_prompt *p);
void		free_prompt(t_prompt *p);
// prompt colors
void		color_prompt(t_prompt *p);
char		*ft_strjoin_multiple(const char *first, ...);
//////////////////
// tokenization //
//////////////////
// tokenization.c
t_tokens	*tokenize(char *prompt);
void		handle_operator(char *str, int *i, t_tokens **list);
void		handle_word(char *str, int *i, t_tokens **list);
char		*extract_word(char *str, int *i);
t_tokens	*add_token(t_tokens **tokens, char *val, int type, int quoted, int expandable);
// tokenization_utils.c
int			is_space(char c);
int			is_operator(char c);
int 		operator_len(char *s);
int			operator_type(char *op);
// tokenization_more_utils.c
char		*remove_quotes(char *s);
int			handle_operator_exclusion(char *str, int *i);
// debug_tokens.c
void		print_tokens(t_tokens *lst);
void		free_tokens(t_tokens *lst); // this one isn't actually debug we need it to adress memleaks
void		print_tokens2(t_tokens *tokens);

#endif

