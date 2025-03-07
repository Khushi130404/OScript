#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_LINE 80

int main(void) 
{
    char input[MAX_LINE];
    char lastCommand[MAX_LINE] = ""; 
    int should_run = 1;

    while (should_run) 
    {
        printf("osh> ");
        fflush(stdout);

        if (fgets(input, MAX_LINE, stdin) == NULL) 
        {
            perror("fgets failed");
            exit(1);
        }

        input[strcspn(input, "\n")] = '\0'; 

        if (strcmp(input, "exit") == 0) 
        {
            break;
        }

        if (strcmp(input, "!!") == 0) 
        {
            if (strlen(lastCommand) == 0) 
            {
                printf("No commands in history.\n");
                continue;
            } 
            else 
            {
                printf("%s\n", lastCommand); 
                strcpy(input, lastCommand); 
            }
        } 
        else 
        {
            strcpy(lastCommand, input);
        }

        char *args[MAX_LINE / 2 + 1];
        int i = 0;
        char *token = strtok(input, " ");
        while (token != NULL) 
        {
            args[i++] = token;
            token = strtok(NULL, " ");
        }
        args[i] = NULL; 

        pid_t pid = fork();
        if (pid < 0) 
        {
            perror("Fork failed");
            exit(1);
        } 
        else if (pid == 0) 
        {
            if (execvp(args[0], args) < 0) 
            {
                perror("Execution failed");
                exit(1);
            }
        } 
        else 
        {
            wait(NULL); 
        }
    }
    return 0;
}
