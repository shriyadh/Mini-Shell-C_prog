// Modify this file for your assignment
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include "linkedlist.h"
#include "linkedlist.c"


// Start shell view
int start_shell(int display)
{
	if(display == 1) {
	printf("**************************************************************\n");
	printf("\n\n\n\t**********Welcome to Shriya's Shelll**********\n");
	printf("\n\n\n***********************************************************\n");
    	
	sleep(1);
  	return  0; }
 return ;
	
}

// parse input 
void parseSpace(char* cmd, char** arguments) {
//printf("space entered");
	int i;

	for(i = 0; i < 80; i++) {
		arguments[i] = strsep(&cmd," \n");
                                 	
 		if (arguments[i] == NULL){
		 	break;
		}
	     	//printf("%s\n",arguments[i]);                                 	
                                 	
 		if(strlen(arguments[i]) == 0) {
			i--;
			}
		}

}

// executing linux built in commands
void executeBuiltIn(char** arguments) {
	pid_t pid = fork();

	if(pid < 0) {
		printf("\nFailed fork\n");
		exit(1);
	} 
	else if(pid == 0) {
		execvp(arguments[0], arguments);
		printf("\nCommand not found--Did you meant something else?\n");
		exit(1);
	} else { 
		wait(NULL);

		return;
	}
}


// built history command
void getHistory(linkedlist_t* history) {
	puts("\n********** This is the history command!************\n\n"
	     "User used the followings commands => \n");
	PrintLinkedList(history);
	
	return;
}	

// built help command
void helpCommand() {

	puts("\n **** WELCOME TO THE HELP COMMAND DESIGNED BY SHRIYA **** \n"
	     "\n         Copyright@ Shriya Dhaundiyal March 2022          \n"
	     "\n List of commands designed by developer and supported by   "
	     "\n               Shriya:mini-shell>                         \n"
	     "  >>>cd : change directory\n"
	     "  >>>help : Information about the non-builtin commands. \n"
	     "  >>>exit : Exit out of the mini-shell.\n"
	     "  >>>history: Prints out all the commands input by the user.\n");
	return;
}

// execute commands not defined in the system
int executeCommand(char** arguments, linkedlist_t* history ) {


	char* nonBuiltCommands[4];
         
	nonBuiltCommands[0] = "exit";
	nonBuiltCommands[1] = "cd"; 
	nonBuiltCommands[2] = "help"; 
	nonBuiltCommands[3] = "history"; 
	
	int caseNo = 0;
        int i;

	for( i = 0; i < 4; i++) {
		if(strcmp(arguments[0], nonBuiltCommands[i]) == 0) {
			caseNo = i + 1;
			break;
		} 
	}


	switch(caseNo) {

	case 1: 
		printf("\n********************************************************\n"
	               "********************************************************\n\n"
		       "\n====================Goodbye User!=======================\n\n"
		       "-------------Hope you enjoyed in Shriya's Shell!--------\n\n"
		       "====================See You Soon!!!=====================\n\n"
		       "\n***********************************************************\n"
	               "***********************************************************\n");
		FreeLinkedList(history);
		exit(0);

	case 2: 
		chdir(arguments[1]);
		return 1;

	case 3: 

		helpCommand();
		return 1;

	case 4:
		getHistory(history);
		return 1;

	default: 

		break;
 
     }
     return 0;

}

// finding pipe in inputs
int findPipe(char* cmd, char** pipeCmd) {
	int i;
	for(i = 0; i < 2; i++) {
		pipeCmd[i] = strsep(&cmd, "|");
		if(pipeCmd[i] == NULL)
			break;

	}

	if(pipeCmd[1] == NULL)
		return 0;// return 0 if no pipe found
	else {
 
		return 1; //pipe found 
	}
}

// execute pipe 
void executePipe(char** arguments, char** pipes) {

	int fd[2];
	pid_t p1;
	pid_t p2;

	if(pipe(fd) < 0){
		printf("\nPipe could not be initialized!\n");
		return;
	}
	p1 = fork();
	if(p1 < 0) {
		printf("\nFork failed!\n");
		return;
	}

	if(p1 == 0) {
		
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);

		if(execvp(arguments[0], arguments) < 0) {
			printf("\nCommand 1 failed!\n");
			exit(1);
                 }
	} else { 
		p2 = fork();

		if(p2 < 0) {
			printf("\nFork 2 Failed!\n");
			return;
		}


		if(p2 == 0) {
		
			dup2(fd[0], STDIN_FILENO);
			close(fd[1]);
			close(fd[0]);
			if(execvp(pipes[0], pipes) < 0) {
				printf("\nCommand 2 Failed!\n");	
				exit(1);
	
			}		

		} else {
		//	int status;
			close(fd[0]);
			close(fd[1]);
			wait(NULL);
			wait(NULL);
		//	waitpid(p1, &status, 0);
	//		waitpid(p2, &status, 0);
		}

		}
	}



// parse commands given by user
int parseInput(char* cmd, char** arguments, char** pipes, linkedlist_t* history) {
	char* pipeCmd[2];
	int piped = 0;
 	//find pipe 
	piped = findPipe(cmd, pipeCmd);

	if(piped) { 
		parseSpace(pipeCmd[0], arguments);
	
		parseSpace(pipeCmd[1], pipes);

	} else {   
		parseSpace(cmd, arguments);	
	}

	// if nothing is typed
	if(arguments[0] == NULL) {
     		return 9999;
	} 
	// if command execution is successful return 0
	if(executeCommand(arguments, history))
		return 0;
	else
	{
		return 1 + piped;
	}

}



// signal handler to exit Shriya's shell
void sigint_handler(int sig) {

	write(1, "Terminating through signal handler\n", 35);
	exit(0);

}

int main(){
  alarm(180); // Please leave in this line as the first statement in your program.
              // This will terminate your shell after 180 seconds,
              // and is useful in the case that you accidently create a 'fork bomb'
 
	// install signal handler
	signal(SIGINT, sigint_handler);

	printf("You can only terminate by pressing Ctrl+C\n");
        
        linkedlist_t* history = CreateLinkedList();
 	int display = 1;       
     	char cmd[80]; char cmdCopy[80];
	char* arguments[100];
        char* pipes[100];
	int toExecute = 0;

	while(1) {
		
		sleep(1);
                // display welcome message only once
                display = start_shell(display);
		// get input from user 	
      		printf("\nShriya:mini-shell> ");    
 	        fgets(cmd, 80, stdin);            
  		// if user does not input anything
		if(cmd == NULL) {
                    continue;}     
		// add to history 
		strcpy(cmdCopy, cmd);       	
		AppendToLinkedList(history, cmdCopy);
                         
		// we parse the input now to check for commands or piping
                toExecute = parseInput(cmd, arguments, pipes, history);  
                
		// pipe not found 
	        if(toExecute == 1){ 
		        executeBuiltIn(arguments);
	
		}
		// pipe was found
		if(toExecute == 2) {
		
			executePipe(arguments, pipes);
			}
 	}

	return 0;
}
	
















 


