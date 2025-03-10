#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

#define MAX_LINE 80 

int main(void) 
{
    char input[MAX_LINE];
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

        char *args[MAX_LINE / 2 + 1];
        char *file = NULL;
        int i = 0, redirect_out = 0, redirect_in = 0;
        
        char *token = strtok(input, " ");
        while (token != NULL) 
        {
            if (strcmp(token, ">") == 0) 
            { 
                redirect_out = 1;
                token = strtok(NULL, " ");
                file = token; 
            } 
            else if (strcmp(token, "<") == 0) 
            {
                redirect_in = 1;
                token = strtok(NULL, " ");
                file = token; 
            } 
            else 
            {
                args[i++] = token;
            }
            token = strtok(NULL, " ");
        }
        args[i] = NULL; 

        pid_t pid = fork();
        if (pid < 0) 
        {
            // Failed
            perror("Fork failed");
            exit(1);
        } 
        else if (pid == 0) 
        { 
            // Child Process
            if (redirect_out) 
            {
                int fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
                if (fd < 0) 
                {
                    perror("File open failed");
                    exit(1);
                }
                dup2(fd, STDOUT_FILENO); 
                close(fd);
            } 
            else if (redirect_in) 
            {
                int fd = open(file, O_RDONLY);
                if (fd < 0) 
                {
                    perror("File open failed");
                    exit(1);
                }
                dup2(fd, STDIN_FILENO); 
                close(fd);
            }

            if (execvp(args[0], args) < 0) 
            {
                perror("Execution failed");
                exit(1);
            }
        } 
        else 
        { 
            // Parent process
            wait(NULL); 
        }
    }
    return 0;
}
