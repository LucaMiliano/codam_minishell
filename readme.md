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




Absolutely! Here’s a concise recap you can pick up from later — I’ll make it very clear so it’s easy to jump back in:

---

### **Minishell Expansion Issue Recap**

**Current situation:**

1. Tokens (`t_tokens`) have:

   * `value` → the string
   * `quoted` → 0: none, 1: single quote, 2: double quote
   * `expandable` → 1/0 depending on whether `$VAR` should expand

2. Parser builds commands (`t_cmd`) and redirections (`t_redir`):

   * `argv` and `redirs->target` are **just strings**, usually with quotes **already stripped**
   * **Problem:** Once quotes are stripped, we lose the information about single vs double quotes.

3. `expand_pipeline()` currently:

   * Operates on `argv` and `redirs->target` strings
   * Tries to expand `$VAR` everywhere
   * **Problem:** It has no way of knowing if the original token was single-quoted → `$VAR` should not expand

---

**Root cause:**

* The expander cannot know which words should or should not expand because the quote information is **lost after parsing**.
* Relying on the string content alone (Option B) is unsafe if quotes are stripped.

---

**Solution (Option A — recommended):**

1. **Propagate expandable info from tokens to parsed commands**:

   * Add `expandable` field to:

     ```c
     t_cmd->argv_expandable[i]
     t_redir->expandable
     ```
   * Set it during parsing from `token->quoted`:

     ```c
     token->quoted == 1 → expandable = 0
     else → expandable = 1
     ```
2. `expand_pipeline()` can then check this flag instead of guessing from the string.

---

✅ **Benefit:**

* Expansion works exactly like the shell: single-quoted → no expansion, double/unquoted → expand.
* Parser and expander stay separated and safe.

---

When you come back, the next step will be:

* Modify parser to **store expandable info from tokens**
* Update `t_cmd` and `t_redir`
* Update `expand_pipeline()` to **use the new expandable flags**

---

If you want, I can **write the exact patched code for parser + expand_pipeline** so you can just drop it in when you return.

Do you want me to prepare that?



<!-- ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// -->
Perfect! I’ll lay out a concrete patch for you so that expansion respects single quotes without breaking anything else. I’ll include **parser changes, struct changes, and the updated expander**.

---

## **1️⃣ Update structs**

Add an `expandable` field to the argv inside `t_cmd` (or just track per argv element) and make sure `t_redir` already has `expandable`.

```c
typedef struct s_cmd
{
    char        **argv;
    int         *argv_expandable;  // NEW: 1 if expandable, 0 if not
    t_redir     *redirs;
    struct s_cmd *next;
}   t_cmd;
```

* For each `argv[i]`, `argv_expandable[i]` corresponds to whether the original token was expandable.
* `t_redir->expandable` already exists → just set it during parsing.

---

## **2️⃣ Parser change: propagate expandable info**

Where you build `argv` from tokens in the parser:

```c
// Example pseudocode inside parser function
int count = 0;
t_tokens *tmp = token_list;
while (tmp && tmp->type == TOK_WORD)
{
    count++;
    tmp = tmp->next;
}

cmd->argv = malloc(sizeof(char *) * (count + 1));
cmd->argv_expandable = malloc(sizeof(int) * (count + 1));

int i = 0;
while (token && token->type == TOK_WORD)
{
    cmd->argv[i] = ft_strdup(token->value);   // copy string
    cmd->argv_expandable[i] = (token->quoted == 1) ? 0 : 1; // single quotes → no expansion
    i++;
    token = token->next;
}
cmd->argv[i] = NULL;
cmd->argv_expandable[i] = 0;
```

* This ensures we know which argv elements can expand.
* Similarly for redirections:

```c
r->expandable = (token->quoted == 1) ? 0 : 1;
```

---

## **3️⃣ Update `expand_pipeline()`**

Use the new flags instead of guessing from the string:

```c
void expand_pipeline(t_cmd *cmds)
{
    int i;
    char *expanded;
    t_redir *r;

    while (cmds)
    {
        // Expand argv
        i = 0;
        while (cmds->argv && cmds->argv[i])
        {
            if (cmds->argv_expandable[i])
            {
                expanded = expand_word(cmds->argv[i]);
                if (expanded)
                {
                    free(cmds->argv[i]);
                    cmds->argv[i] = expanded;
                }
            }
            i++;
        }

        // Expand redirections
        r = cmds->redirs;
        while (r)
        {
            if (r->expandable)
            {
                expanded = expand_word(r->target);
                if (expanded)
                {
                    free(r->target);
                    r->target = expanded;
                }
            }
            r = r->next;
        }

        cmds = cmds->next;
    }
}
```

✅ Now expansion **will skip single-quoted strings** safely.

---

## **4️⃣ Summary**

* Added `argv_expandable` array to `t_cmd`
* Set it in the parser from token’s `quoted` field
* `expand_pipeline()` now checks `argv_expandable` instead of trying to guess from content
* `t_redir->expandable` already exists, just set it during parsing

---

If you want, I can **also provide a minimal diff for the parser functions** so you can literally paste it in and it works without touching any other logic.

Do you want me to do that next?

Perfect — this is **exactly** the right moment to switch from coding to **systematic validation**.
Below is a **structured test plan with concrete commands and expected results**, aligned with the 42 minishell subject and **adapted to what you currently implement** (i.e. no word-joining, no advanced bonus unless stated).

I’ll clearly mark:

* ✅ **Expected to work**
* ⚠️ **Allowed limitation (not a bug)**
* ❌ **Must fail gracefully**

You can copy-paste and test block by block, and then send me **only the failing ones**.

---

# 🧪 MINISHELL TEST PLAN (WITH EXPECTED OUTPUTS)

---

## 1️⃣ Arguments (no quotes)

### Test

```sh
/bin/ls
/bin/ls -l
/bin/echo hello world
/bin/ls /does/not/exist
```

### Expected

* `/bin/ls` → lists files
* `/bin/ls -l` → long listing
* `echo hello world` → `hello world`
* `/bin/ls /does/not/exist` → error message, **no crash**

✅ If any crash → **CRASH**
❌ If command runs but output wrong → **INCOMPLETE**

---

## 2️⃣ echo

### Test

```sh
echo
echo hello
echo hello world
echo -n hello
echo -n hello world
```

### Expected

```text
<empty line>
hello
hello world
hellohello world
```

Notes:

* `-n` → no newline
* Multiple args printed with spaces

⚠️ If spacing slightly differs but logic correct → OK

---

## 3️⃣ exit

### Test

```sh
exit
exit 0
exit 42
exit 999
exit abc
```

### Expected

* `exit` → shell exits
* `exit 0` → exit status 0
* `exit 42` → exit status 42
* `exit 999` → exit status `999 % 256 = 231`
* `exit abc` → error message, **do not exit** (bash behavior)

❌ If minishell exits on `exit abc` → **INCOMPLETE**

---

## 4️⃣ Return value `$?`

### Test

```sh
/bin/ls
echo $?

/bin/ls /does/not/exist
echo $?

false
echo $?

true
echo $?
```

### Expected

```text
0
2 (or non-zero, depending on system)
1
0
```

Also test:

```sh
echo $? $?
```

Expected:

```text
0 0
```

⚠️ Arithmetic like `$? + $?` is **not required**

---

## 5️⃣ Signals

### Empty prompt

| Key    | Expected              |
| ------ | --------------------- |
| Ctrl-C | New line + new prompt |
| Ctrl-\ | Nothing               |
| Ctrl-D | Exit minishell        |

### While typing

```text
echo hello<Ctrl-C>
```

Expected:

* New prompt
* Press Enter → nothing executes

### Blocking command

```sh
cat
```

| Key    | Expected              |
| ------ | --------------------- |
| Ctrl-C | Stops cat, new prompt |
| Ctrl-\ | Usually ignored       |
| Ctrl-D | Ends input, cat exits |

❌ Crash → **CRASH**

---

## 6️⃣ Double quotes (NO `$` here)

### Test

```sh
echo "hello world"
echo "   spaced   text   "
echo "cat lol.c | cat > lol.c"
```

### Expected

* Everything inside quotes is literal
* Pipes and redirections are NOT interpreted

---

## 7️⃣ Single quotes

### Test

```sh
echo '$USER'
echo '$HOME'
echo '   '
echo ''
echo 'cat | grep a > file'
```

### Expected

```text
$USER
$HOME

<empty line>
cat | grep a > file
```

✅ **Nothing interpreted**

---

## 8️⃣ env

### Test

```sh
env
```

### Expected

* List of `KEY=VALUE`
* Should include `PATH`, `PWD`, `USER` (if set)

---

## 9️⃣ export

### Test

```sh
export TEST=hello
env | grep TEST
export TEST=world
env | grep TEST
export ABC
env | grep ABC
```

### Expected

```text
TEST=hello
TEST=world
ABC=
```

---

## 🔟 unset

### Test

```sh
unset TEST
env | grep TEST
```

### Expected

* No output

---

## 1️⃣1️⃣ cd

### Test

```sh
pwd
cd ..
pwd
cd .
pwd
cd /does/not/exist
```

### Expected

* `cd ..` → directory changes
* `cd .` → stays
* Invalid path → error, stay in same dir

---

## 1️⃣2️⃣ pwd

### Test

```sh
pwd
cd ..
pwd
```

### Expected

* Correct absolute path each time

---

## 1️⃣3️⃣ Relative paths

### Test

```sh
../minishell
./minishell
../../bin/ls
```

### Expected

* Executes if path is valid
* Error otherwise

---

## 1️⃣4️⃣ PATH resolution

### Test

```sh
ls
unset PATH
ls
export PATH=/bin:/usr/bin
ls
```

### Expected

* `ls` works initially
* After `unset PATH` → `ls: command not found`
* After reset → works again

---

## 1️⃣5️⃣ Redirections

### Test

```sh
echo hello > file
cat file

echo world >> file
cat file

cat < file
```

### Expected

```text
hello
hello
world
hello
world
```

Multiple redirections:

```sh
echo test > file > file2
```

Expected:

* Last redirection wins

---

## 1️⃣6️⃣ Heredoc (if implemented)

```sh
cat << EOF
hello
$HOME
EOF
```

Expected (unquoted):

* `$HOME` expands

```sh
cat << 'EOF'
$HOME
EOF
```

Expected:

* `$HOME` literal

⚠️ If not implemented → **INCOMPLETE**, not crash

---
# 1️⃣7️⃣#Pipes

### Test

```sh
ls | wc -l
cat file | grep hello
ls filethatdoesntexist | grep bla
```

Expected:

* Pipes work
* Errors propagate, no crash

Mix:

```sh
cat file | grep hello > out
```

---

## 1️⃣8️⃣ History & chaos

### Test

* Use ↑ ↓
* Ctrl-C then Enter → nothing runs
* Invalid command:

```sh
dsbksdgbksdghsd
```

Expected:

* Error message
* Shell continues

---

## 1️⃣9️⃣ Environment variables (expansion)

### Test

```sh
echo $USER
echo "$USER"
echo '$USER'
```

Expected:

```text
cpinas
cpinas
$USER
```

---

## 2️⃣0️⃣ Special “surprise” tests

```sh
export USER=hello
echo "'$USER'"
echo '"$USER"'
```

Expected:

```text
hello
$USER
```

This one **confirms your quote + expansion logic is perfect**.

---

# 🟢 How to report back

Send me:

* ❌ Commands that **crash**
* ⚠️ Commands that **behave differently than expected**
* ✅ Everything else you can ignore

Example reply:

```
FAILED:
- echo "$HOME"'test' → output: ...
- ctrl-\ during cat → ...
```

You are now testing like a **reviewer**, not a student — that’s a very good sign.

||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||

||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||

||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||

Exactly! Signals are a bit “context-sensitive” in a shell because different processes should react differently depending on whether they’re **interactive shell, child process, or heredoc**. Here’s the breakdown of what we still need to handle:

---

### 1️⃣ **Interactive shell (main prompt)**

* **Ctrl-C (SIGINT)** → interrupt current input, clear line, but **don’t exit the shell**.
* **Ctrl-\ (SIGQUIT)** → ignored.
* This is basically what your `sigint_handler` already does with readline. ✅

---

### 2️⃣ **Child process (executed command)**

* **Ctrl-C (SIGINT)** → should kill the child process.
* **Ctrl-\ (SIGQUIT)** → default behavior (usually prints `Quit` and core dumps if unhandled).
* In code, you set this with:

```c
void setup_signals_child(void)
{
    signal(SIGINT, SIG_DFL);
    signal(SIGQUIT, SIG_DFL);
}
```

* This is because the shell itself should **not be killed**, only the child process.

---

### 3️⃣ **Heredoc**

* **Ctrl-C (SIGINT)** → abort the heredoc input **and return control to the main shell**.
* **Ctrl-\ (SIGQUIT)** → ignored.
* For heredoc, you usually need a **special signal handler**:

```c
static void sigint_heredoc(int signo)
{
    (void)signo;
    write(1, "\n", 1);
    exit(1); // abort heredoc
}

void setup_signals_heredoc(void)
{
    signal(SIGINT, sigint_heredoc);
    signal(SIGQUIT, SIG_IGN);
}
```

* Called **right before you start reading lines for heredoc**.
* After heredoc finishes (or is interrupted), you should **restore the shell’s normal signal handlers**.

---

### 🔹 Key points

1. **Shell vs child vs heredoc** — same signal can do very different things depending on context.
2. **Heredoc signals are temporary** — they only override signals while reading heredoc.
3. Ctrl-C **inside heredoc** should stop the heredoc **without killing the shell**, unlike in child processes where it kills the command.

---

If you want, I can make a **small diagram showing which signal goes where and what it does**, so it’s easier to implement and remember.

Perfect! Here’s a clear diagram showing the **signal behavior in your shell**, separated by context. This is super handy when wiring signals for the main shell, heredoc, and child processes.

---

### **Signal Handling Overview**

```
+---------------------+
| Interactive Shell   |
+---------------------+
| Ctrl-C  (SIGINT)   | → Clear current input line, show new prompt, do NOT exit
| Ctrl-\ (SIGQUIT)   | → Ignored
+---------------------+

+---------------------+
| Child Process       |
+---------------------+
| Ctrl-C  (SIGINT)   | → Kill the running child process
| Ctrl-\ (SIGQUIT)   | → Default (may quit & core dump)
+---------------------+

+---------------------+
| Heredoc Input       |
+---------------------+
| Ctrl-C  (SIGINT)   | → Abort heredoc, return to main shell
| Ctrl-\ (SIGQUIT)   | → Ignored
+---------------------+
```

---

### **Implementation Notes**

#### 1️⃣ Interactive Shell

```c
signal(SIGINT, sigint_handler);  // readline-aware
signal(SIGQUIT, SIG_IGN);
```

#### 2️⃣ Child Process (before `execve`)

```c
signal(SIGINT, SIG_DFL);
signal(SIGQUIT, SIG_DFL);
```

#### 3️⃣ Heredoc (temporary)

```c
signal(SIGINT, sigint_heredoc); // exits heredoc only
signal(SIGQUIT, SIG_IGN);
```

* **Important:** After heredoc finishes (or is aborted), restore shell’s normal handlers.
* `sigint_heredoc` is usually a simple function that prints `\n` and exits the heredoc reading loop.

---

### **Control Flow Summary**

1. User types command → shell uses shell handlers (Ctrl-C clears input).
2. Shell forks child → child uses default signals (Ctrl-C kills child, shell unaffected).
3. Shell executes heredoc → temporarily overrides signals to handle Ctrl-C properly.
4. After heredoc or child finishes → restore normal shell handlers.

---

If you want, I can also give a **small C snippet showing exactly how to wrap heredoc reading with signal setup and restoration**, which is the cleanest way to implement it.

For continueation after the lunch


