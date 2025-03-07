#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_COMMAND_LENGTH 1024
#define MAX_ARGS 100

void execute_command(char *command);
void execute_piped_commands(char *cmd1, char *cmd2);

int main() 
{
    char input[MAX_COMMAND_LENGTH];

    while (1) 
    {
        printf("osh> ");
        fflush(stdout);

        if (!fgets(input, MAX_COMMAND_LENGTH, stdin)) 
        {
            break; 
        }

        input[strcspn(input, "\n")] = 0; 

        if (strcmp(input, "exit") == 0) 
        {
            printf("Exiting shell...\n");
            break;
        }

        char *pipe_position = strchr(input, '|');
        if (pipe_position) 
        {
            *pipe_position = '\0';
            char *cmd1 = input;
            char *cmd2 = pipe_position + 1;
            execute_piped_commands(cmd1, cmd2);
        } 
        else 
        {
            execute_command(input);
        }
    }

    return 0;
}

void execute_command(char *command) 
{
    char *args[MAX_ARGS];
    char *token = strtok(command, " ");
    int i = 0;

    while (token != NULL) 
    {
        args[i++] = token;
        token = strtok(NULL, " ");
    }
    args[i] = NULL;

    pid_t pid = fork();
    if (pid == 0) 
    { 
        execvp(args[0], args);
        perror("Error executing command");
        exit(1);
    } 
    else if (pid > 0) 
    {
        wait(NULL);
    } 
    else 
    {
        perror("Fork failed");
    }
}

void execute_piped_commands(char *cmd1, char *cmd2) 
{
    int pipe_fd[2];
    if (pipe(pipe_fd) == -1) 
    {
        perror("Pipe failed");
        return;
    }

    pid_t pid1 = fork();
    if (pid1 == 0) 
    { 
        dup2(pipe_fd[1], STDOUT_FILENO);
        close(pipe_fd[0]);
        close(pipe_fd[1]);
        execute_command(cmd1);
        exit(0);
    }

    pid_t pid2 = fork();
    if (pid2 == 0) 
    { 
        dup2(pipe_fd[0], STDIN_FILENO);
        close(pipe_fd[0]);
        close(pipe_fd[1]);
        execute_command(cmd2);
        exit(0);
    }

    close(pipe_fd[0]);
    close(pipe_fd[1]);

    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);
}
