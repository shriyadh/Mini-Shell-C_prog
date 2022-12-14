# README Please :)

# Introduction

<img src="./shell.png" alt="An example shell"/>

[Shell's](https://en.wikipedia.org/wiki/Shell_(computing)) (or sometimes called command-line interfaces) are text based applications that serve as an intermediate between the user and the operating system. The shell is also a tool for how a user interacts with the operating system.
 
Mini-Shell

<img src="./media/shell.gif" alt="An example of your minishell" width=400px/>

You are now ready to create Mini-Shell. Mini-Shell is inspired by other popular shells. The good news is you can validate the behavior of your shell against the Unix terminal to ensure it is working.

At a high level, implementing mini-shell takes the following components:
1. You will have a function that reads in commands a user types.
2. Your program will execute in an infinite loop.
3. Your program will execute child processes from the shell (the shell is the parent process) based on the command.

## The specifications for your shell

1. You should have a prompt "mini-shell>" in front of each command that is typed out.
	- (If you want to be creative you can include the machine name or other information you can derive).
2. The maximum input size(i.e. BUFFER SIZE) on a given line will be 80 characters for our shell. You can specify this as a constant global variable.
3. Implement a signal handler so when the user presses <kbd>Ctrl+C</kbd> the text 'mini-shell terminated' is printed out.
	- Make sure that all child processes are terminated when this occurs!
4. When you launch a new child process from your shell, the child process should run in the foreground by default until it is completed.
	- Here are some examples: https://www.tutorialspoint.com/unix/unix-processes.htm
5. If the user adds the pipe '|' then the output of one process should be the input to the next process.
	- You can assume only one '|' will be used at most. e.g. `ls -l | wc`
	- As a hint, it can be helpful to have a separate function or use case that handles parsing a series of commands if a pipe is found when parsing the individual tokens.
	- Here are some examples: https://www.tutorialspoint.com/unix/unix-pipes-filters.htm
	- - You may not use the 'system' command which makes handling pipes trivial. You must investigate [dup](https://linux.die.net/man/2/dup) and file descriptors.
6. Your shell should have some built-in functions that you will have to implement (i.e. functions written in C code). These include 'exit' to terminate your shell, 'cd' so you may change directories, and 'help' explaining all the built-in commands available in your shell.
	1. You can test `cd` by moving up or down the directory tree.
		- (Hint the C library has commands for this)
	2. `help` should print out all of the built-in commands that you implement (including your additional command (see bullet #9)).
	3. `exit` should terminate the shell 
		- Note: If you launch another shell from within your shell, exit should only close out of the most recently launched shell.
7. You will want to think about how to store these built-in commands.
	- I will hint that using an array with commands and an array of function pointers is one possibly effective solution.
	- What is a function pointer? [Eighth day in C](https://www.youtube.com/watch?v=fa_lIhqLTuk) or  https://www.geeksforgeeks.org/function-pointer-in-c/
	- You can further think about what an array of function pointers looks like and why this may be appropriate.
8. If a command is not found (whether a built-in or a program), your shell should print out an error message, and resume execution.
	- e.g. `mini-shell>Command not found--Did you mean something else?`
9. You need to implement 1 addditional built-in command `history` that keeps track of all of the input the user has input.. 
	1. This `history` built-in command can be implemented in whatever data structure that you like.
		- So your shell should store all of the commands that a user has typed in.
		- When the user types `history` that list of commands is printed out (the most recent command, at the end of the output).
	2. (Edit the readme below with your built-in `history` command)

-----------------------------------------------------
NAME: 

Shriya Dhaundiyal

SYNOPSIS: 

History keeps a track of all the previously typed out commands.

DESCRIPTION:

While working in a server environment, you???ll spend a lot of your time on the command line. Most likely, you???ll be using the bash shell, which is the default of most distributions.

During a terminal session, you???ll likely be repeating some commands often, and typing variations on those commands even more frequently. While typing each command repeatedly can be good practice in the beginning, at some point, it crosses the line into being disruptive and an annoyance.

Luckily, the bash shell has some fairly well-developed history functions. Learning how to effectively use and manipulate your bash history will allow you to spend less time typing and more time getting actual work done. Many developers are familiar with the DRY philosophy of Don???t Repeat Yourself. Effective use of bash???s history allows you to operate closer to this principle and will speed up your workflow.
Bash allows you to adjust the number of commands that it stores in history. It actually has two separate options for this: the HISTFILESIZE parameter configures how many commands are kept in the history file, while the HISTSIZE controls the number stored in memory for the current session

NOTES:

I used the linkedlist to implement the history command as it can be malloced as per requirement and stores every command in the correct order.

-----------------------------------------------------

## Some helpful things to ponder

1. You are running programs in your shell. The programs that are being run are found in the 'bin' directory. For example, you would find a program called 'cat' or 'ls' there, which someone wrote in C for you.
2. You can also execute programs from a relative or absolute filepath (e.g. ./minishell)
3. There is not a program called 'cd' in the 'bin' directory, which means it must be built into the actual shell.
4. There exists more than 1 [exec](https://linux.die.net/man/3/exec) command -- some are helpful for finding things on your [environment path](https://en.wikipedia.org/wiki/PATH_(variable)). Hmm!

Provided below is an example for program that forks a new process, executes the process, and then resumes execution in the parent.

```c
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int main(){

	char* myargv[16];
	myargv[0]="/bin/ls"; // Try changing this to "ls" Will the program work?
			     // Note: There are many versions of exec that will look in
			     //	      environment variable paths. See execvpe for example.
	myargv[1]="-F";
	myargv[2]=NULL; // Terminate the argument list
	
	if(fork()==0){
		// Executes command from child then terminates our process
		execve(myargv[0],myargv,NULL);
		printf("Child: Should never get here\n");
		exit(1);
	}else {
		wait(NULL); // This call makes the parent wait on its children.
	}

	printf("Finally, print from the parent\n");
	
	return 0;
}
```

## How do I test mini-shell?

The good news is you can validate the behavior of your shell against the Unix terminal to ensure it is working. Some samples you can reasonably test when getting started are the following:

```bash
./mini-shell
cat shell.c
nl shell.c
ls -l
pwd
cd .
pwd
nl shell.c | wc -l
cat shell.c | head 2
./mini-shell # Running a mini-shell within a mini-shell and then executing commands
cd ..
```

# Resources to help

- (See links above)
- And otherwise think about commands like fork, execvp, wait, waitpid, getpid, etc. :)

### Glossary and Tips
1. Commit your code changes to the repository often, this is best practice.
2. Do not commit your .o file or your executable file to the repository, this is considered bad practice!
3. On Functionality/Style
	1. You should have comments in your code to explain what is going on, and use good style (80 characters per line maximum for example, functions that are less than 50 lines, well named variables, well named functions etc.).
4. You may use any stdio.h functions that are useful, such as getline. You are welcome to implement these functions from scratch if you like however.
	1. You will want to include 'signal.h' as well for your signal handlers.
5. Careful when parsing. Things like newline characters '\n' like to sneak in and may make it difficult for strcmp to provide accurate results. "teststring" != "teststring\n"	

# Going Further

You might consider some of the following optional features in your shell.
1. Switching processes between forground and background (fg and bg commands).
2. Handling the '|', pipe  between an arbitrary number of processes.
3. Handle tab completion or moving through the history of commands with arrowkeys (This is a good example of a built-in command).

# Feedback Loop

(An optional task that will reinforce your learning throughout the semester)

Implementing a shell is one of the more fun exercises in learning C programming (in my opinion). However, it is quite relevant, especially in the context of the web browser and other applications (video games for example, often have a real-time shell interface for debugging).

Choose one of the following 3 papers to skim, and you can add notes here with two interesting things you discovered (Note this is not graded and completely optional).

- Grocoli: https://dl.acm.org/citation.cfm?id=2442019
- Integrating Command Shell in Web Browser: https://www.usenix.org/techsessionssummary/integrating-command-shell-web-browser
- Inky: http://people.csail.mit.edu/emax/papers/uist08-inky/uist08-inky.pdf

# F.A.Q.

- Q: Do I have to implement every shell command?
- A: No--that would be completely unreasonable! Think about how the 'exec' family of commands work and PATH. You are only implementing a few built-in commands('help','exit','cd',and your own custom command) that will execute. If a command is not a built-in command, then you attempt to exec it as a linux programs found on PATH.
- Q: Can I split my program into multipl .c and .h files?
	- A: Yes, we'll assume we can compile your program with some command like: `gcc *.c -o minishell`
