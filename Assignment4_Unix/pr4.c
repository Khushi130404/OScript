#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>

int main()
{
  int rw[2]; // 0 for read, 1 for fwrite
  pid_t pid;
  char msg[] = "Tahiti a magical place.";
  char buffer[50];
  
  if(pipe(rw)==-1)
  {
    perror("Pipeline Failed");
    return 1;
  }
  
  pid = fork();
  
  if(pid<0)
  {
    printf("Child Creation Failed");
    perror("Child Creation Failed");
    return 1;
  }
  else if(pid==0)
  {
    printf("\nThis is child %d",getpid());
    close(rw[1]);
    read(rw[0],buffer,sizeof(buffer));
    printf("\nChild read : %s",buffer);
    close(rw[0]);
  }
  else
  {
    printf("\nThis is Parent : %d",getpid());
    close(rw[0]);
    write(rw[1],msg,strlen(msg)+1);
    close(rw[1]);
  }
  
  return 0;
}