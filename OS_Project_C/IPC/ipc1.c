#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_LINE 80

int main(void)
{
    char *args[MAX_LINE / 2 + 1];
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
            should_run = 0;
            continue;
        }

        char *token = strtok(input, " ");
        int i = 0;
        while (token != NULL)
        {
            args[i++] = token;
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
            // Child process
            if (execvp(args[0], args) < 0)
            {
                perror("Execution failed");
                exit(1);
            }
        }
        else
        { 
            // Parent process
            waitpid(pid, NULL, 0);
        }
    }
    return 0;
}
