<div align="center">
  <a href="https://github.com/mpeyre-s/42_minishell"><img src="https://github.com/mpeyre-s/42_project_badges/raw/main/badges/minishell.svg"/></a>
  <p>The aim of this project is to create a simple shell that mimics the behavior of Bash, providing a fundamental understanding of command-line interfaces and system programming.</p>
  <br>
</div>

# ➡️ Competencies Acquired

- **System Programming**: Learned how to interact with the operating system through system calls for process management, file I/O, and signals.
  
- **Shell Implementation**: Gained insight into the inner workings of a Unix shell, including parsing, command execution, and pipeline handling.

- **Process Management**: Worked with `fork()`, `execve()`, and `wait()` to manage multiple processes efficiently.

- **Error Handling**: Strengthened debugging skills by implementing robust error checking and handling edge cases.

- **Memory Management**: Applied best practices for memory allocation and deallocation to avoid leaks and ensure stability.

- **Team Collaboration**: Collaborated with peers using Git, improving teamwork and version control skills.

# ➡️ Program Features

1. **Command Execution**:  
   - Supports basic commands like `ls`, `echo`, `pwd`, and more.  
   - Handles absolute and relative paths.  

2. **Built-in Commands**:  
   - Implemented built-ins such as:  
     - `cd`: Change the current directory.  
     - `echo`: Display text.  
     - `pwd`: Print the current working directory.  
     - `export`/`unset`: Manage environment variables.  
     - `exit`: Exit the shell.  

3. **Pipes and Redirections**:  
   - Supports multiple pipes (e.g., `cmd1 | cmd2 | cmd3`).  
   - Handles input (`<`), output (`>`), and append (`>>`) redirections.  

4. **Environment Variables**:  
   - Access and expand variables (e.g., `$PATH`, `$HOME`).  
   - Support for custom environment variable manipulation.  

5. **Signals**:  
   - Custom handling of `CTRL+C`, `CTRL+Z`, and `CTRL+D`.  

6. **Error Handling**:  
   - Provides descriptive error messages for invalid commands, syntax errors, and system call failures.  

7. **Bonus Features** (if applicable):  
   - Wildcard expansion (`*`).  
   - Support for advanced redirection combinations.  

# ➡️ Project Insights

- **Challenges Faced**:  
  - Managing memory leaks in complex scenarios.  
  - Handling edge cases for redirections and pipelines.  
  - Implementing a robust lexer and parser for command-line inputs.  

- **Lessons Learned**:  
  - The importance of modular code and clear function responsibilities.  
  - Debugging and testing are key to building a stable shell.  
