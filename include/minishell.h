/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpinas <cpinas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 18:30:58 by cpinas            #+#    #+#             */
/*   Updated: 2026/02/11 20:35:47 by cpinas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"

# define RESET	"\001\033[0m\002"
# define RED		"\001\033[1;31m\002"
# define GREEN	"\001\033[1;32m\002"
# define YELLOW	"\001\033[1;33m\002"
# define CYAN	"\001\033[1;36m\002"
# define BLUE	"\001\033[1;34m\002"
# define MAGENTA	"\001\033[1;35m\002"
# define CYAN	"\001\033[1;36m\002"
# define WHITE	"\001\033[1;37m\002"

typedef struct s_shell
{
	char		**env;
	int			last_status;
	int			saved_stdin;
	int			saved_stdio_in;
	int			saved_stdio_out;
	char		*cur_line;
	void		*cur_cmds;
	void		*cur_prompt;
	int			cur_is_tty;
}	t_shell;

extern int	g_last_status;

typedef struct s_prompt
{
	char	*cwd;
	char	*user;
	char	*host;
	char	*prompt_str;
}	t_prompt;

typedef struct s_prompt_ctx
{
	t_prompt	*p;
	char		*line;
	int			is_tty;
	int			saved_stdin;
}	t_prompt_ctx;

enum e_toktype
{
	TOK_WORD,
	TOK_PIPE,
	TOK_REDIR_IN,
	TOK_REDIR_OUT,
	TOK_APPEND,
	TOK_HEREDOC,
};

typedef struct s_tokens
{
	char			*value;
	enum e_toktype	type;
	int				expandable;
	int				quoted;
	struct s_tokens	*next;
}	t_tokens;

typedef enum e_redir_type
{
	R_IN,
	R_OUT,
	R_APPEND,
	R_HEREDOC
}	t_redir_type;

typedef struct s_redir
{
	t_redir_type	type;
	char			*target;
	int				expandable;
	int				fd;
	struct s_redir	*next;
}	t_redir;

typedef struct s_cmd
{
	char			**argv;
	int				*argv_expandable;
	t_redir			*redirs;
	struct s_cmd	*next;
}	t_cmd;

t_redir_type	redir_type(enum e_toktype tok_type);

int				prompt(t_shell *shell);
int				build_prompt1(t_shell *shell, t_prompt *p, int is_tty);
char			*get_prompt_line(t_prompt *p, int is_tty);
char			*read_from_stdin(void);
int				handle_line(char *line, t_prompt *p, int is_tty);
t_cmd			*create_cmds(char *line, t_prompt *p, int is_tty);
int				execute_and_cleanup(t_shell *shell,
					t_cmd *cmds, t_prompt_ctx *ctx);
int				restore_and_return(int saved_stdin, int ret);
int				handle_heredoc(t_shell *shell, t_redir *redir);
int				builtin_history(char *line);
char			*get_current_directory(void);
char			*get_username(t_shell *shell);
char			*get_hostname(void);
char			*build_prompt(t_prompt *p);
void			free_prompt(t_prompt *p);
void			color_prompt(t_prompt *p);
char			*ft_strjoin_multiple(const char *first, ...);
void			setup_signals_exec(void);
void			setup_signals_child(void);
void			setup_signals_prompt(void);
void			sigint_handler(int sig);
void			setup_signals_heredoc(void);
t_tokens		*tokenize(char *prompt);
void			handle_operator(char *str, int *i, t_tokens **list);
void			handle_word(char *str, int *i, t_tokens **list);
char			*extract_word(char *str, int *i, int *quoted, int *expand);
char			*check_for_quotes(char *str, int *quoted, int *i, int *expand);
char			*read_until_quote_closed(char *initial_line);
int				has_unclosed_quotes(char *str);
int				is_space(char c);
int				is_operator(char c);
int				operator_len(char *s);
int				operator_type(char *op);
char			*remove_quotes(char *s);
int				handle_operator_exclusion(char *str, int *i);
t_tokens		*new_token(char *val, int type, int quoted, int exp);
void			token_add_back(t_tokens **tokens, t_tokens *new);
void			print_tokens(t_tokens *lst);
void			free_tokens(t_tokens *lst);
void			print_redirs(t_redir *redir);
void			print_cmd(t_cmd *cmd, int index);
void			print_pipeline(t_cmd *head);
void			print_tokens_debug(t_tokens *tokens);
t_cmd			*parse(t_tokens *tokens);
t_cmd			*argv_add(t_cmd *cmd, char *word, int expandable);
int				parse_file_redir(t_tokens **tokens, t_cmd *cmd, t_cmd **head);
int				heredoc_syntax_error(t_cmd **head);
int				heredoc_alloc_error(t_cmd **head);
t_redir_type	redir_type(enum e_toktype tok_type);
int				redir_alloc_error(t_cmd **head);
int				parse_word(t_tokens **tokens, t_cmd *cmd);
int				parse_pipe(t_tokens **tokens, t_cmd **current);
int				parse_file_redir(t_tokens **tokens, t_cmd *cmd, t_cmd **head);
t_tokens		*skip_heredoc_body(t_tokens *delim);
int				parse_heredoc(t_tokens **tokens, t_cmd *cmd, t_cmd **head);
int				parse_redir(t_tokens **tokens, t_cmd *cmd, t_cmd **head);
int				parse_token(t_tokens **tokens, t_cmd **current, t_cmd **head);
t_cmd			*parse(t_tokens *tokens);
t_cmd			*cmd_new(void);
void			cmd_add_redir(t_cmd *cmd, t_redir *redir);
int				is_redir(enum e_toktype tok_type);
int				parse_redir(t_tokens **tokens, t_cmd *cmd, t_cmd **head);
int				check_pipe_syntax(t_tokens *tokens);
t_tokens		*skip_heredoc_body(t_tokens *delim);
void			expand_pipeline(t_cmd *cmds, t_shell *shell);
char			*expand_word(char *word, t_shell *shell);
char			*get_var_value(const char *s, int *consumed, t_shell *shell);
char			*append_char(char *result, char c);
char			*append_expanded_var(char *result,
					char *word, int *i, t_shell *shell);
void			exec_cmd(t_shell *shell, t_cmd *cmd, int in_fd, int out_fd);
void			exec_from_path(t_shell *shell, t_cmd *cmd);
void			execute_pipeline(t_shell *shell, t_cmd *cmds);
void			save_and_redirect1(t_shell *shell, t_cmd *cmd,\
				int *saved_in, int *saved_out);
void			restore_and_reset1(t_shell *shell, int saved_in, int saved_out);
int				handle_parent_builtin(t_shell *shell, t_cmd *cmd);
void			close_heredoc_fds(t_cmd *cmds);
void			pipe_loop(t_shell *shell, t_cmd *cmd, int prev_fd);
void			setup_pipe(t_cmd *cmd, int pipefd[2]);
void			handle_child(t_shell *shell, t_cmd *cmd,\
				int prev_fd, int write_fd);
int				handle_input(char *line);
void			exec_absolute_or_relative(t_shell *shell, t_cmd *cmd);
void			save_stdio1(int *saved_stdin, int *saved_stdout);
void			restore_stdio1(int saved_stdin, int saved_stdout);
int				prepare_heredocs(t_shell *shell, t_cmd *cmds);
t_redir			*redir_new(t_redir_type type, char *target, int expandable);
void			apply_redirections(t_redir *redir);
int				exec_builtin(t_cmd *cmd, t_shell *shell);
int				builtin_echo(char **argv);
char			*get_oldpwd(void);
char			*resolve_target(t_shell *shell, char **argv);
char			*get_oldpwd_or_error(void);
int				builtin_pwd(t_shell *shell);
int				builtin_env(t_shell *shell);
int				builtin_cd(t_shell *shell, char **argv);
int				builtin_exit(t_shell *shell, char **argv);
int				builtin_export(t_shell *shell, char **argv);
int				builtin_unset(t_shell *shell, char **argv);
int				builtin_echo(char **argv);
void			update_env(t_shell *shell, char *key, char *value);
char			*find_in_env(t_shell *shell, const char *name);
void			add_env_var(t_shell *shell, char *key, char *value);
void			remove_env_var(t_shell *shell, char *key);
char			*join_path(char *dir, char *cmd);
void			free_tokens(t_tokens *lst);
void			free_cmd_pipeline(t_cmd *cmd);
void			free_split(char **arr);
int				prompt_exit(t_prompt *p, int is_tty, int saved_stdin, int ret);
void			free_env(char **env);
void			free2_prompt(t_prompt *p);
int				is_builtin(char *cmd);

#endif
