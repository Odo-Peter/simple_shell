# Simple Shell - Simple shell team project

This is the solution to the simple shell project for ALX low level programming language [ALX SWE](https://alxafrica.com). A team project to improve collaborations and problem solving skills amongst ALX students.

## Table of contents

- [Overview](#overview)
  - [The requirements](#the-requirements)
    - [The challenge](#the-challenge)
    - [Authorized functions and macros](#authorized-functions-and-macros)
    - [Functions and descriptions](#functions-and-descriptions)
    - [Compilation](#compilation)
    - [Testing](#testing)
  - [Our process](#our-process)
    - [Built with](#built-with)
    - [What we learned](#what-we-learned)
    - [Continued development](#continued-development)
    - [Useful resources](#useful-resources)
  - [Authors](#authors)
  - [Acknowledgments](#acknowledgments)

## Overview

### The requirements

The general requirements for the project tasks were:

- All files were compiled on Ubuntu 20.04 LTS using `gcc`, using the options `-Wall -Werror -Wextra -pedantic -std=gnu89`
- All files ended with a new line
- A `README.md` file, at the root of the folder of the project was created
- Code used the Betty style
- The shell should not have any memory leaks
- No more than 5 functions per file
- The prototypes of all functions were included in the header file called `main.h`
- All header files were 'include guarded'
- A README with the description of the project was written
- An 'AUTHORS' file at the root of the project repository, listing all individuals having contributed content to the repository was created.

### The challenge

The project was to achieve the following:

- Write a simple UNIX command interpreter.
  - All files should pass betty linter test.
  - Write a UNIX command line interpreter, the shell should do the following:
    - Display a prompt and wait for a user to type a command.
    - The prompt is displayed again each time a command has been executed.
    - The command lines are simple, no semicolons, no pipes, no redirections or any other advanced features.
    - If an executable cannot be found, print an error message and display the prompt again.
    - Handle errors.
    - The "end of file" condition should be handled `ctrl+D`
  - Handle command lines with arguments.
  - Handle the `PATH`
  - `fork` must not be called if the command doesn't exist.
  - Implement the exit built-in, that exits the shell.
    - Usage: `exit`
    - Any argument to the built-in `exit` must not be handled.
  - Implement the `env` built-in, that prints the current environment.

### Authorized functions and macros

The authorized functions and macros:

- `access`
- `chdir`
- `close`
- `closedir`
- `execve`
- `exit`
- `_exit`
- `fflush`
- `fork`
- `free`
- `getcwd`
- `getline`
- `getpid`
- `isatty`
- `kill`
- `malloc`
- `open`
- `opendir`
- `perror`
- `read`
- `readdir`
- `signal`
- `stat`
- `lstat`
- `fstat`
- `strtok`
- `wait`
- `waitpid`
- `wait3`
- `wait4`
- `write`

### Functions and descriptions

The several functions used to making the simple shell project in its entirety and their descriptions are thus:

| Function   | Description                                        |
| ---------- | -------------------------------------------------- |
| shell_init | Prompts the user to enter a command (i.e (EdPe$ )) |
| shell_exit | Exit the simple shell and returns to the terminal  |

**\*\***....... (This is just an overview, we will edit this part as the tasks progresses with the appropraite functions and descriptions) .......**\*\*\*\***

### Compilation

The code(s) was compiled this way:

```
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh
```

### Testing

The interactive mode of the shell is expected to be thus:

```
$ ./hsh
(EdPe$ ) /bin/ls
hsh main.c shell.c
(EdPe$ )
(EdPe$ ) exit
$
```

The non-interactive mode of the shell:

```
$ echo "/bin/ls" | ./hsh
hsh main.c shell.c test_ls_2
$
$ cat test_ls_2
/bin/ls
/bin/ls
$
$ cat test_ls_2 | ./hsh
hsh main.c shell.c test_ls_2
hsh main.c shell.c test_ls_2
$
```

## Our process

### Built with

The simple shell project, was built with C language.

### What we learned

**\*\***....... What we both learned in the course of the tasks goes here, we will keep updating (this part individually, probably after each task) as time goes by.......**\*\*\*\***

### Continued development

What we hope to do after completing this tasks, eg, implementing more of the functionalities of a regular UNIX shell, etc...
**\*\***....... (We will also update this with suitable ideas in due time) .......**\*\*\*\***

### Useful resources

[Code Blocks](https://docs.readme.com/rdmd) - The rdmd docs from this site helped us to write a well structured readme for this project, alongside proper formatting of inline codes and code blocks

[Stack Overflow](https://stackoverflow.com/) - This aided us to help find questions and appropraite answers to bugs we faced while doing the project. (we can come add more to this later)

[GitHub Docs](https://docs.github.com/en/get-started/) - GitHub Docs was used to create nicely formatted tables for writing functions and their descriptions.

[Geeks For Geeks](https://geeksforgeeks.org) - Geeks for geeks, a great place for well detailed technical articles encompassing several programming languages, this helped in getting several informations on how some of the functions works.

**\*\***....... (we can add more resources we might use to update the readme e.g, adding the official unix docs where those manual pages we see on terminal can be gotten online) .......**\*\*\*\***

## Authors

This project was done by:

- Edward Annan
- Peter Odo

## Acknowledgments

**\*\***....... We will put the Acknowledgments here, thank alx for the opportunity and prolly add some one or two things we are grateful for as regarding the completion of this task. .......**\*\*\*\***
