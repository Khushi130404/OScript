#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
  pid_t pid = fork();
  
  if(pid<0)
  {
    printf("Process Failed");
    perror("Failed");
    return 1;
  }
  else if(pid==0)
  {
    printf("\nThis is Child Process : %d\n",getpid());
    fflush(stdout); 
    execlp("/bin/ls","ls","-l",NULL);
    printf("execlp Failed");
    perror("Space Failed");
    return 1;
  }
  else
  {
    wait(NULL);
    printf("\nThis is Parent Process : %d",getpid());
  }
  
  return 0;
}