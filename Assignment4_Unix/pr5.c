#include <stdio.h>

struct Process{
  int id;
  int burst;
  int remaining;
};

int main()
{
  int n,time=0,quantum,done=1;
  
  printf("\nEnter Total Process : ");
  scanf("%d",&n);
  
  struct Process p[n];
  
  for(int i=0; i<n; i++)
  {
    p[i].id = i+1;
    printf("Enter Burst Time for PID %d : ",p[i].id);
    scanf("%d",&p[i].burst);
    p[i].remaining = p[i].burst;
  }
  
  printf("\nEnter Time Quantum : ");
  scanf("%d",&quantum);
  
  do
  {
    done = 1;
    for(int i=0; i<n; i++)
    {
      if(p[i].remaining>0)
      {
        done=0;
        if(p[i].remaining>quantum)
        {
          printf("\nProcess %d starts at %d",p[i].id,time);
          time+=quantum;
          p[i].remaining-=quantum;
        }
        else
        {
          printf("\nProcess %d starts at %d",p[i].id,time);
          time+=p[i].remaining;
          p[i].remaining = 0;
          printf("\nProcess %d finish at %d",p[i].id,time);
        }
      }
    }
    
  }while(!done);
  
  return 0;
}
