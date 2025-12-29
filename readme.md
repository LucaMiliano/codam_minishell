# minishell
Voor minishell,
1. commandpromt / shell:
	1a.
	1b.
2. Lexer / Tokenizer
3. Parsing
4. Execution


# little bit of git
git branch "outline" (name behind makes clone of present git)
git switch master (back on the master)
git merge "outline"

for getting the branch of the other:
git pull (git will ask you to git add your changes)
once you have done that git pull again.
than it ask you if you want to merge in editor say yes.
And then merge files according to which one you want to keep.


minishell/
├── Makefile
├── minishell.h
├── main.c
├── prompt.c
├── signals.c
├── lexer.c
├── parser.c
├── exec.c
├── exec_utils.c
├── builtins.c
├── builtins_env.c
├── redirections.c
├── heredoc.c
├── env.c
├── free.c
├── libft/
structure that I'm aiming for today.



# testing

my argv is owned by tokens and freeed when tokens are freed. I must remeber to free this correctly and keep it in mind when I want to free on a "bad read in parser"

2.2 Consecutive pipes

Input: ls || wc

Tokens debug: ❌ Tokens don’t include PIPE for ||

Analysis: This is a lexer issue, not parser. Right now your lexer interprets || as two separate WORD tokens? That’s why the parser sees argv = ["ls", "wc"] instead of detecting || as an invalid token.

Action: Fix the lexer to tokenize operators correctly (| vs ||). Parser can then catch consecutive PIPEs.

remember for later 2


///////////////////////////////////////////////////////////////////////////////////////////

| Feature / Functionality         | Status            | Notes / Details                                                                 |
| ------------------------------- | ----------------- | ------------------------------------------------------------------------------- |
| **Environment handling**        | ✅ Done            | `g_shell.env` copy, `update_env()`, `find_in_env()` implemented                 |
| **Builtins**                    |                   |                                                                                 |
| `echo`                          | ✅ Done            | Handles `-n`, prints arguments correctly                                        |
| `pwd`                           | ✅ Done            | Uses `getcwd()` correctly, dynamic allocation                                   |
| `cd`                            | ✅ Done            | Updates `PWD` / `OLDPWD`, handles `~` and `-`                                   |
| `env`                           | ✅ Done            | Prints `g_shell.env`                                                            |
| `exit`                          | ✅ Done            | Basic implementation tested                                                     |
| `export`                        | ⚠️ Partially done | Needs `VAR=value` handling, `$VAR` expansion in shell, add variable if no value |
| `unset`                         | ❌ Not done        | Remove variable from `g_shell.env`                                              |
| **Variable expansion**          | ❌ Not done        | `$VAR` inside commands, redirections, heredoc, quotes                           |
| **Redirections**                |                   |                                                                                 |
| `<` (input)                     | ✅ Done            | Basic functionality implemented                                                 |
| `>` (output)                    | ✅ Done            | Basic functionality implemented                                                 |
| `>>` (append)                   | ✅ Done            | Basic functionality implemented                                                 |
| `<<` (heredoc)                  | ⚠️ Partially done | Works, but variable expansion missing                                           |
| **Command execution**           | ✅ Done            | `exec_cmd()`, `child_process()`, `execute_pipeline()`                           |
| **Pipelines**                   | ✅ Done            | Multiple commands connected with pipes                                          |
| **Signals**                     | ⚠️ Partially done | `CTRL-C`, `CTRL-D` handling partially, check exit codes                         |
| **Error handling / messages**   | ⚠️ Partially done | Some builtins like `rm` give extra errors, need cleanup                         |
| **Memory management / cleanup** | ⚠️ Partially done | Freeing `g_shell.env`, redirection buffers, strdup() results                    |
| **Advanced features / polish**  | ❌ Not done        | Multi-word expansion, quotes, proper exit codes, final testing                  |
