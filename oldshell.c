#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int main( int argc, char *argv[], char *env[] )
{
    //declare value
    pid_t child_pid;
   int status;
   char command[1001]; //to keep the input command
   char history[1001][1001]; //history list
   char *token;
   char *args[10]; //keep argument

	int i = 0;
	int commandCount = 0;
	while (1) {
		command[0] = '\0';
		printf("[CustomShell] "); //telling user that the program ready for getting input
		fgets(command, 1000, stdin); //get the input
		command[strlen(command) - 1] = '\0';

		if (strcmp(command, "history") == 0) //checking that command is history or not
        {
			int j = 0;
			for (j = 0; j < commandCount; j++)
			{
				printf("%d. %s\n", j+1, history[j]); //print out the history
			}
			strcpy(history[commandCount], command); //then add the history command into history list
			commandCount++;
			continue;
		} else if (strcmp(command, "exit") == 0) {
			return 0;
		} else {
			strcpy(history[commandCount], command);
			commandCount++;
		}

		//printf("Untokenized: %s\n", command);
		token = strtok(command, " "); //separate white space
		while( token != NULL ) //split string into array
		{
			args[i] = token;
			i++;
		   token = strtok(NULL, " ");
		}
		if((child_pid = fork()) < 0) //if the fork fail
		{
		   perror("Fork Failed: ");
		   exit(1);
		}
		else if(child_pid == 0) // it's a child process
		{
		   execvp(command, args);
		   perror("Execution Failed: ");
		   exit(0);
		}
		else
		{
		   wait(NULL); //waiting other fork to running
		}
	}
   return 0;
}
