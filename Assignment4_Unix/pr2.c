#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main()
{
  pid_t pid = fork();
  
  if(pid<0)
  {
    printf("\nFailure");
    return 1;
  }
  else if(pid==0)
  {
    printf("\nThis is Child Process : %d",getpid());
    printf("\nMy Parent Process : %d",getppid());
  }
  else
  {
    wait(NULL);
    printf("\nThis is Parent Process : %d",getpid());
    printf("\nMy Child Process : %d",pid);
  }
  
  return 0;
}