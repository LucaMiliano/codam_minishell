[minishell] Refactor prompt loop
- Clean up main prompt
- Separate CTRL-D exit handling and history management

[minishell] Add quote handling in tokenizer
- Detect single and double quotes
- Report unclosed quote syntax errors
- Prevent incomplete words from being tokenized

[minishell] Exclude invalid operator sequences
- Handle `||`, `<<<`, `><`, `<>` as syntax errors
- Skip invalid sequences to prevent parser crashes

[minishell] Add token flags
- Add `quoted` and `expandable` fields to t_tokens
- Update add_token() to store flags for future parsing

[minishell] Fix compilation issues
- Correct return types and unused variable warnings
- Initialize new->quoted and new->expandable correctly
- Compile cleanly with -Wall -Wextra -Werror

[minishell] Improve tokenizer edge cases
- Handle empty strings, escaped characters, and mixed quotes/operators
- Assign correct token types (WORD, PIPE, REDIR_IN/OUT, APPEND, HEREDOC)
- Maintain shell stability on invalid input

[minishell] Manual testing & validation
- Syntax errors detected and reported correctly
- Quotes, escapes, and operators tokenized properly
- No segmentation faults or memory leaks (Valgrind clean)
