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

			int j = 0, k=0;

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



		} else if (strcmp(args[0], "exit") == 0) {

			return 0;

		}

		/*else if(strcmp(args[0],"!!") == 0){

			int k=0;

			token = strtok(history[commandCount-1]," ");

			while( token != NULL )

			{

				args[k] = token;

				k++;

				token = strtok(NULL, " ");

			}



			/*arg[k] = NULL;

			child_pid = fork();

			if(child_pid < 0)

			{

				perror("Fork Failed: ");

				exit(1);

			}

			else if(child_pid == 0)

			{

				execvp(arg[0], arg);

				perror("Execution Failed: ");

				exit(0);

			}

			else

			{

				wait(NULL);

			}

		} /*else if(regcomp(args[0],tofind,REG_EXTENDED)==0){

			printf("Helo");

		}*/

		else if(args[0][0] == '!'){

			int k=0;

			if(strcmp(args[0],"!!") == 0){

				printf("jeree");

				token = strtok(history[commandCount-1]," ");

				while( token != NULL )

				{

					args[k] = token;

					k++;

					token = strtok(NULL, " ");

				}

			}

			if(isdigit(args[0][1])){
printf("digit");

				int check = args[0][1] - '0';

				token = strtok(history[check-1]," ");

				printf("%s",history[check]);

				while( token != NULL )

				{

					args[k] = token;

					k++;

					token = strtok(NULL, " ");

				}

			}



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


			if(strcmp(args[0], "history") != 0) perror("Execution Failed: ");

			exit(0);

		}

		else

		{

			wait(NULL);

		}

	}

   return 0;

}
