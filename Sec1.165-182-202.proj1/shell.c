#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <ctype.h>

int main( int argc, char *argv[], char *env[] )
{

	pid_t child_pid;
	int status;
	char command[1001];
	char temp[1001];
	char tempp[1001];
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
		args[j] = NULL;

		if (strcmp(args[0], "history") == 0 && j == 1) {
			int j = 0, k = 0;
			for (j = 0; j < commandCount; j++)
			{
				while(i<strlen(history[j])) {
					if (history[j][i]==' ') {
					    for (k=i; k<strlen(history[j]); k++)
						history[j][k]=history[j][k+1];
					} else break;
				}
				printf("%d. %s\n", j+1, history[j]);
			}

			if (commandCount>=100) {
				for(i=0; i<commandCount-1; i++) {
					strcpy(history[i], history[i+1]);
				}
				strcpy(history[i], temp);

			} else {
				strcpy(history[commandCount], temp);
				commandCount++;
			}

			continue;

		} else if (strcmp(args[0], "exit") == 0 && j == 1) {
			return 0;

		} else if(args[0][0] == '!'){
			int k=0;
			if(strcmp(args[0],"!!") == 0 && j == 1){
				strcpy(temp, history[commandCount-1]);
				strcpy(tempp, history[commandCount-1]);

				token = strtok(tempp," ");

				while( token != NULL )
				{
					args[k] = token;
					k++;
					token = strtok(NULL, " ");
				}
			}

			if(isdigit(args[0][1])){
				int check = args[0][1] - '0';
				strcpy(temp, history[check-1]);
				strcpy(tempp, history[check-1]);

				token = strtok(tempp," ");
				while( token != NULL )

				{
					args[k] = token;
					k++;
					token = strtok(NULL, " ");
				}
			}

			if(strlen(args[0]) == 3){
				int check = (args[0][1] - '0')*10;
				if(isdigit(args[0][2])) {
					check = check+(args[0][2] - '0');
				}
				strcpy(temp, history[check-1]);
				strcpy(tempp, history[check-1]);

				token = strtok(tempp," ");

				while( token != NULL )
				{
					args[k] = token;
					k++;
					token = strtok(NULL, " ");
				}
			}
			args[k] = NULL;
		}

		if (commandCount>=100) {
			for(i=0; i<commandCount-1; i++) {
				strcpy(history[i], history[i+1]);
			}
			strcpy(history[i], temp);

		} else {
			strcpy(history[commandCount], temp);
			commandCount++;
		}

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
