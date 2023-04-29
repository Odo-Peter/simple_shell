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
	- The “end of file” condition should be handled `ctrl+D`
	- Handle command lines with arguments.	
	- Handle the `PATH`
	- `fork` must not be called if the command doesn’t exist.	
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

| Function          | Description                                                         |
| ----------------- | ------------------------------------------------------------------- |
| main              | The entry point of the main program                                 |
| \_\_h_shell       | The main shell loop, in this function, the user is prompt for input |
| \_\_find_builtins | A customizable function, that mocks the LINUX builtin commands      |
| \_\_find_commands | This finds the mocked commands and run them appropraitely           |
| \_\_fork_command  | This creates a child process and forks an execution thread          |
| \_\_error_puts    | This writes an error message to the STDERR                          |
| \_realloc         | This reallocate a block of memory                                   |

Alot of functions was used to get the shell to work appropraitely

### Compilation

The code(s) was compiled this way:

```
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh
```

### Testing

The interactive mode of the shell is expected to be thus:

```
$ ./hsh
(Konichiwa :)$ ) /bin/ls
hsh main.c shell.c
(Konichiwa :)$ )
(Konichiwa :)$ ) exit
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

**\*\***....... We learned many useful things, at first we thought finally we've gotten a hang of these only for it to be shown to us after the checker was released that we were mostly off about a lot of codes; luckily enough for us we made up with the second chance we were given and got it together to a T, doing hard things truly doesn't come easy but hen the hardness keeps coming, we fall back onto a single word "Tataka" .......**\*\*\*\***

### Continued development

What we hope to do after completing this tasks, eg, implementing more of the functionalities of a regular UNIX shell, etc...
**\*\***.......We hope to implement this new set of skills into our future projects, hopefully both of us get to team up and work on more projects as time goes forward but we both individually would apply the new set of skills in our fields .......**\*\*\*\***

### Useful resources

[Code Blocks](https://docs.readme.com/rdmd) - The rdmd docs from this site helped us to write a well structured readme for this project, alongside proper formatting of inline codes and code blocks

[Stack Overflow](https://stackoverflow.com/) - This aided us to help find questions and appropraite answers to bugs we faced while doing the project. (we can come add more to this later)

[GitHub Docs](https://docs.github.com/en/get-started/) - GitHub Docs was used to create nicely formatted tables for writing functions and their descriptions.

[Geeks For Geeks](https://geeksforgeeks.org) - Geeks for geeks, a great place for well detailed technical articles encompassing several programming languages, this helped in getting several informations on how some of the functions works.

[Youtube Channels](https://youtube.com) - Combinations of several channels and videos was used to aid the completion of this project, I will suggest that anyone wanting to top their developing game, should use Youtube more often.

[Google](https://google.com) - Google was the icing on the cake, as almost everything, started and ended with Google, a timely and accurate search can salvage one hours of debugging problems.

## Authors

This project was done by:

- Edward Annan
- Peter Odo

## Acknowledgments

We are both super grateful for the opportunity ALX is offering to young Africans as regards growing the technological atmosphere of the continent, we sure, will keep this flag flying high, ALX to the world.

P.S - Simple shell was not "simple", just "shell" :(
