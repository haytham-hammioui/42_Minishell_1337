<h1 align="center">42_MINISHELL_1337</h1>
<p align="center">
  <a href="https://github.com/haytham-hammioui/42_Minishell_1337">
    <img src="https://raw.githubusercontent.com/ayogun/42-project-badges/refs/heads/main/badges/minishelle.png" alt="42 Badge">
  </a>
</p>

# Minishell

The `minishell` project is part of the 42 network curriculum. It is a simplified `Unix shell` implementation that recreates basic shell functionality including command execution, pipes, redirections, environment variables, and built-in commands.

## Features

- **Command Execution**: Execute system commands and programs
- **Built-in Commands**:
  - `echo` - Print text with `-n` option to omit newline
  - `cd` - Change directory with relative/absolute paths
  - `pwd` - Print current working directory
  - `export` - Set and export environment variables
  - `unset` - Remove environment variables
  - `env` - Display current environment
  - `exit` - Terminate the shell with optional exit code
- **Pipes**: Support for multiple commands connected with pipes (`|`)
- **Redirections**: 
  - Input (`<`) - Redirect input from files
  - Output (`>`) - Redirect output to files (overwrite)
  - Append (`>>`) - Redirect output to files (append)
  - Heredoc (`<<`) - Read input until delimiter
- **Environment Variables**: Expansion of `$VAR` and `$?` (exit status)
- **Signal Handling**: Proper handling of `Ctrl-C`, `Ctrl-D`, and `Ctrl-\`
- **History**: Command history navigation with arrow keys
- **Error Handling**: Comprehensive error messages and proper memory management

## Getting Started

### Installation

1. **Clone the Repository**
   ```sh
   git clone https://github.com/haytham-hammioui/42_Minishell_1337.git 7allal_shell
   ```

2. **Compile the Program**
   Navigate to the `7allal_shell` directory and run `make`. This will generate the `minishell` executable.
   ```sh
   cd 7allal_shell
   make
   ```

### Usage

1. Run the program `minishell`:
    ```sh
     ./minishell
    ```

2. Available Commands:
    - Execute system commands: `ls -la`, `grep pattern file`, etc.
    - Use built-ins: `cd /path`, `export VAR=value`, `exit`.
    - Pipe commands: `ls | grep test | wc -l`.
    - Redirect I/O: `echo "hello" > file.txt`, `cat < input.txt`.
    - Environment variables: `echo $HOME`, `export TEST=123`.
    - ...

3. Exit the Shell:
    ```sh
     exit
     or press Ctrl-D
    ```
## Technical Details

 - **Memory Management**: Proper allocation and freeing of memory to prevent leaks.
 - **Error Handling**: Comprehensive error checking and meaningful error messages.
 - **Signal Handling**: Proper handling of interrupt signals.
 - **Norm Compliance**: Code follows 42's coding standard (Norminette).

## Developed By

  - **[smaksiss](https://github.com/M4KSS1S)**  
  - **[hhammiou](https://github.com/haytham-hammioui)**
  
## Contributing

Contributions to `minishell` are welcome! Whether you've found a bug, have a feature request, or want to contribute code:

1. Fork the repository.
2. Create a new branch for your changes.
3. Add your contributions.
4. Push your branch and open a pull request against the `minishell` repository.

