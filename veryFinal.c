#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int main( int argc, char *argv[], char *env[] )
{
	pid_t child_pid;
	int status;
	char command[1001];
	char history[1001][1001];
	char *token;
	char *args[10];

	int i = 0;
	int commandCount = 0;
	while (1) {
		command[0] = '\0';
		printf("[CustomShell] ");
		fgets(command, 1000, stdin);
		command[strlen(command) - 1] = '\0';

		strcpy(temp, command);
		
		token = strtok(command, " ");
		int j = 0;
		while( token != NULL ) 
		{
			args[j] = token;
			j++;
			token = strtok(NULL, " ");
		}

		if (strcmp(args[0], "history") == 0) {
			int j = 0;
			for (j = 0; j < commandCount; j++)
			{
				printf("%d. %s\n", j+1, history[j]);
			}
			if (commandCount>=100) {
				for(i=0; i<commandCount-1; i++) {
					strcpy(history[i], history[i+1]);
				}
				strcpy(history[i], command);
			} else {
				strcpy(history[commandCount], command);
				commandCount++;
			}
			continue;
		} else if (strcmp(command, "exit") == 0) {
			return 0;
		} else {
			if (commandCount>=100) {
				for(i=0; i<commandCount-1; i++) {
					strcpy(history[i], history[i+1]);
				}
				strcpy(history[i], command);
			} else {
				strcpy(history[commandCount], command);
				commandCount++;
			}
		}

		args[j] = NULL;
		child_pid = fork();
		if(child_pid < 0)
		{
			perror("Fork Failed: ");
			exit(1);
		}
		else if(child_pid == 0)
		{
			execvp(args[0], args);
			perror("Execution Failed: ");
			exit(0);
		}
		else
		{
			wait(NULL);
		}
	}
   return 0;
}
