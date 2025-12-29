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
#define RESET	"\001\033[0m\002"
#define RED		"\001\033[1;31m\002"
#define GREEN	"\001\033[1;32m\002"
#define YELLOW	"\001\033[1;33m\002"
#define CYAN	"\001\033[1;36m\002"
#define BLUE	"\001\033[1;34m\002"
#define MAGENTA	"\001\033[1;35m\002"
#define CYAN	"\001\033[1;36m\002"
#define WHITE	"\001\033[1;37m\002"

/// global struct for envp ///
typedef struct s_shell
{
	char	**env;
	int		last_status;
}	t_shell;

extern t_shell g_shell;
/// comunicates envp position with the outside env ///

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

// parser structs
typedef enum e_redir_type
{
	R_IN,
	R_OUT,
	R_APPEND,
	R_HEREDOC
}   t_redir_type;

typedef struct s_redir
{
	t_redir_type	type;
	char			*target;	// delimeter or filename
	int				expandable;
	// char			*content;	// for HeredoC lines
	int				fd; 		// required for the heredoc
	struct s_redir	*next;
}	t_redir;

typedef struct s_cmd
{
	char			**argv;
	t_redir			*redirs;
	struct s_cmd	*next;
}	t_cmd;

// functions
//////////////////
//    promt     //
//////////////////
// prompt
// char		*prompt(void);
char		*prompt(void);
// int			execute_builtins(char *line);
int			builtin_history(char *line);
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
//     lexer    //
//////////////////
// tokenization.c
t_tokens	*tokenize(char *prompt);
void		handle_operator(char *str, int *i, t_tokens **list);
void		handle_word(char *str, int *i, t_tokens **list);
char		*extract_word(char *str, int *i, int *quoted, int *expand);
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
void		print_redirs(t_redir *redir);
void		print_cmd(t_cmd *cmd, int index);
void 		print_pipeline(t_cmd *head);
// void		print_tokens2(t_tokens *tokens);
void		print_tokens_debug(t_tokens *tokens);
//////////////////
//    parse     //
//////////////////
// parsing.c
t_cmd *parse(t_tokens *tokens);
// temporarily in parsing.c till I restructer now testing:
// int	parse_token(t_tokens **tokens, t_cmd **current, t_cmd **head);
// int	parse_word(t_tokens **tokens, t_cmd *cmd);
// int	parse_pipe(t_tokens **tokens, t_cmd **current);
// int	parse_redir(t_tokens **tokens, t_cmd *cmd, t_cmd **head);
// int	parse_file_redir(t_tokens **tokens, t_cmd *cmd, t_cmd **head);
// int	parse_heredoc(t_tokens **tokens, t_cmd *cmd, t_cmd **head);
// t_tokens	*skip_heredoc_body(t_tokens *delim);
// parser_add_word.c
char **argv_add(char **argv, char *new_arg);
// parser_cmd.c
t_cmd *cmd_new(void);
// parser_redir.c
void cmd_add_redir(t_cmd *cmd, t_redir *redir);
// t_redir	*redir_new(t_redir_type type, char *target, int expandable);
// parser_utils.c
int	check_pipe_syntax(t_tokens *tokens);
//////////////////
//    expand    //
//////////////////
// expand.c
void	expand_pipeline(t_cmd *cmds);
char	*expand_word(char *word);
//////////////////
//     exec     //
//////////////////
// exec_cmd.c
void	exec_cmd(t_cmd *cmd, int in_fd, int out_fd);
// exec_pipeline.c
void	execute_pipeline(t_cmd *cmds);
// void	execute_pipeline(t_cmd *cmds, char **envp);
// exec_utils.c
//////////////////
//  heredoc     //
//////////////////
// heredoc.c
int	prepare_heredocs(t_cmd *cmds);
//////////////////
// redirections //
//////////////////
// redirections.c
t_redir	*redir_new(t_redir_type type, char *target, int expandable);
void	apply_redirections(t_redir *redir);
//////////////////
//   builtins   //
//////////////////
int		exec_builtin(t_cmd *cmd);
int		builtin_echo(char **argv);
int		builtin_pwd(void);
int		builtin_env(void);
int		builtin_cd(char **argv);
int		builtin_exit(char **argv);
int		builtin_export(char **argv);
int		builtin_unset(char **argv);
// int builtin_cd(char **argv, char **envp);
// void update_env(char *key, char *value, char **envp);
int		builtin_echo(char **argv);
// int execute_builtins(char **argv);
// int	handle_builtin_line(char *line, char **envp);
//////////////////
//  update_env  //
//////////////////
void	update_env(char *key, char *value);
char	*find_in_env(const char *name);
char	*join_path(char *dir, char *cmd);
void	add_env_var(char *key, char *value);
void	remove_env_var(char *key);
//////////////////
//     free     //
//////////////////
void	free_tokens(t_tokens *lst);
void	free_cmd_pipeline(t_cmd *cmd);
void	free_split(char **arr);

#endif

