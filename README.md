![296512556-a7d89350-81ee-4159-9d51-d0212461784a](https://github.com/diocode/42-Minishell/assets/107859177/b934a795-bd43-4029-9adf-f868d3825754)


<p align="center">
	<img src="https://img.shields.io/badge/status-finished-success?color=%2312bab9&style=flat-square"/>
	<img src="https://img.shields.io/badge/evaluated-05%20%2F%2002%20%2F%202024-success?color=%2312bab9&style=flat-square"/>
	<img src="https://img.shields.io/badge/score-102%20%2F%20105-success?color=%2312bab9&style=flat-square"/>
	<img src="https://img.shields.io/github/last-commit/diocode/42-Minishell?color=%2312bab9&style=flat-square"/>
	<a href='https://www.linkedin.com/in/diogo-gsilva' target="_blank"><img alt='Linkedin' src='https://img.shields.io/badge/LinkedIn-100000?style=flat-square&logo=Linkedin&logoColor=white&labelColor=0A66C2&color=0A66C2'/></a>
</p>

<p align="center">
	<a href="#about">About</a> •
	<a href="#how-to-use">How to use</a> •
	<a href="#norminette">Norminette</a>
</p>

## ABOUT ([Subject](/.github/en.subject.pdf))

**The Challenge**

Minishell, an individual project, represented a significant milestone in my programming journey. Tasked with creating a miniature version of Bash, this project was the most extensive I had undertaken. The objective was to replicate key functionalities of Bash, encompassing prompt display, command history, executable execution, quoting handling, redirections, pipes, environment variables, signals, and built-in commands.

**Understanding Bash**

To grasp Bash's intricacies, I delved into its fundamental processes—breaking down the system into lexer, parser, expander, and executor stages. This step-by-step approach was crucial to ensuring accuracy and completeness in the implementation.

<br>

## Implementation

**Lexer**<br>
The lexer/tokenizer processed user input, creating a linked list of tokens and words. It identified special characters and organized them for further parsing.

**Parser**<br>
The parser grouped tokens into commands, managing redirections and determining if a command was a built-in. It created a structured data representation for execution.

**Builtins**<br>
Built-in commands, such as `echo`, `cd`, `pwd`, `export`, `unset`, `env`, and `exit`, were handled through function pointers stored in the command structure. This allowed for efficient execution and streamlined the overall code.

**Executor**<br>
The executor managed the execution of commands, handling multiple commands, pipes, and child processes. It ensured proper communication between commands through pipes.

**Expander**<br>
Before execution, the expander replaced variables with their values and processed heredocs, ensuring the command's readiness.

**Heredoc**<br>
Heredocs were managed by creating temporary files to store input, following a simple yet effective approach similar to Bash.

**Single and Multiple Commands**<br>
The executor distinguished between single and multiple commands, creating child processes and managing communication through pipes when necessary.

**Reset**<br>
A full reset ensured the program could handle new commands by freeing resources and resetting variables after each execution.

<br>

## Challenges and Takeaways

Handling edge cases proved to be the most challenging aspect. Despite thorough testing, edge cases continued to emerge, requiring careful debugging and refinement. The project's solo nature allowed for deep personal engagement and mastery of system-level programming concepts. 

The iterative nature of the evaluation process led to a more profound understanding of the intricacies involved, resulting in a successful final submission after addressing identified issues. Minishell stands as a testament to my dedication to mastering system-level programming and creating a functional, efficient shell.

<br>

<a href="/.github/en.subject.pdf">Click here</a> for the subject of this project.

<br>

## HOW TO USE
#### COMPILATION AND EXECUTION
#### 1º - Clone the repository
```bash
$ ./git clone git@github.com:diocode/42-Minishell.git
```

#### 2º - Enter the project folder and run `make`
```bash
$ ./cd 42-Minishell
$ ./make
```

#### 3º - Launch the program
```bash
$ ./minishell
```

<br>

#### MAKEFILE COMMANDS
`make` or `make all` - Compile program **mandatory** files.

`make clean` - Delete all .o (object files) files.

`make fclean` - Delete all .o (object file) and .a (executable) files.

`make re` - Use rules `fclean` + `all`.

<br>

## NORMINETTE
At 42 School, projects are generally expected to adhere to the Norm, the school's coding standard:

```
- No for, do while, switch, case or goto are allowed
- No more than 25 lines per function and 5 functions per file
- No assigns and declarations in the same line (unless static)
- No more than 5 variables in 1 function
... 
```

* [Norminette](https://github.com/42School/norminette) - Tool by 42, to respect the code norm. `GitHub`
* [42 Header](https://github.com/42Paris/42header) - 42 header for Vim. `GitHub`
