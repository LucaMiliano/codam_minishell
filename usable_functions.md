readline: Reads a full line from standard input with editing capabilities.
rl_clear_history: Clears the entire readline history list.
rl_on_new_line: Tells readline that the cursor is now on a new line.
rl_replace_line: Replaces the current input buffer with a new string.
rl_redisplay: Redraws the current input line on the terminal.
add_history: Adds a line to the readline history list.

printf: Prints formatted output to stdout.
malloc: Allocates a block of memory on the heap.
free: Frees previously allocated heap memory.
write: Writes bytes to a file descriptor.
access: Checks whether a file exists or is accessible with given permissions.
open: Opens a file and returns a file descriptor.
read: Reads bytes from a file descriptor.
close: Closes a file descriptor.

fork: Creates a new child process by duplicating the current process.
wait: Waits for any child process to finish.
waitpid: Waits for a specific child process to finish.
wait3: Waits for a child and retrieves resource-usage info without specifying which child.
wait4: Same as wait3 but allows specifying a particular child PID.

signal: Sets a simple signal handler for a specific signal.
sigaction: Installs a detailed signal handler with fine-grained control.
sigemptyset: Initializes a signal set to contain no signals.
sigaddset: Adds a signal to a signal set.
kill: Sends a signal to a process or process group.
exit: Terminates the current process with a status code.

getcwd: Returns the current working directory path.
chdir: Changes the current working directory.
stat: Retrieves information about a file by pathname.
lstat: Like stat but does not follow symbolic links.
fstat: Retrieves file info using a file descriptor.
unlink: Removes a file name (deletes a file).

execve: Replaces the current process image with a new program.

dup: Duplicates a file descriptor to the lowest unused number.
dup2: Duplicates a file descriptor to a specified number.
pipe: Creates a unidirectional data channel with two file descriptors.

opendir: Opens a directory stream.
readdir: Reads the next entry from a directory stream.
closedir: Closes a directory stream.

strerror: Returns a human-readable string for an error number.
perror: Prints an error message based on the global errno.

isatty: Tests if a file descriptor refers to a terminal.
ttyname: Returns the terminal device name for a file descriptor.
ttyslot: Returns the index of the current terminal in the tty table.
ioctl: Performs device-specific I/O control operations.

getenv: Retrieves the value of an environment variable.

tcsetattr: Sets terminal attributes (like canonical mode or echo).
tcgetattr: Retrieves current terminal attributes.

tgetent: Loads terminal capability information.
tgetflag: Gets a boolean terminal capability.
tgetnum: Gets a numeric terminal capability.
tgetstr: Gets a string terminal capability.
tgoto: Computes a cursor movement control sequence.
tputs: Outputs a terminal capability string with padding.
