#include <stdlib.h>
#include <stdio.h>

struct Process{
  int number;
  int bursttime;
  int priority;
  int remaining;
};
int compare1(const void *s1, const void *s2) {
      struct Process *e1 = (struct Process *)s1;
      struct Process *e2 = (struct Process *)s2;
      return e1->bursttime - e2->bursttime;
}
int compare2(const void *s1, const void *s2) {
      struct Process *e1 = (struct Process *)s1;
      struct Process *e2 = (struct Process *)s2;
      return e1->priority - e2->priority;
}

int main(){
  printf("_Welcome to the Algorithm Scheduler simulator_\n");
  printf("  You can choose one of the following algorithms to simulate the execution of the processes:\n    1. First Come, First Serve\n    2. Shortest Job First\n    3. Priority Scheduling\n    4. Round-Robin Scheduling\n");
  printf("Press the number of your choice and then press enter. Press 0 and then Enter to exit\n");

  int e=8;
  struct Process p[10];
  scanf("%d", &e);
  while(e!=0){
    if(e<0||e>4){
      printf("That option is not valid. Try again.\n");
    }else{
      float waittime=0;
      for(int i=0; i<10; i++){
        p[i].number=i+1;
        p[i].bursttime=rand() %10+1;//number between 1 and 10
        p[i].priority=i;
        p[i].remaining=p[i].bursttime;
      }
      if(e==1){
        printf("  You chose First Come, First Serve Algorithm\n");
        printf("A random set of 10 processes was generated: Here you have it: \n");
        for(int i=0; i<10; i++){
          printf("P%d. Burst Time: %d\n", p[i].number, p[i].bursttime);
          if(i!=9) waittime+=p[i].bursttime;
        }
        printf("\nThe processes were executed in the order they appear.\n");
        printf("\nThe average wait time is %f.\n\n", waittime/10);
      }else if(e==2){
        printf("  You chose Shortest Job First Algorithm\n");
        printf("A random set of 10 processes was generated: Here you have it: \n");
        for(int i=0; i<10; i++){
          printf("P%d. Burst Time: %d\n", p[i].number, p[i].bursttime);
        }
        qsort(p, 10, sizeof(struct Process), compare1);
        printf("\nThe processes were executed in the following order.\n");
        for(int i=0; i<10; i++){
          printf("P%d. Burst Time: %d\n", p[i].number, p[i].bursttime);
          if(i!=9) waittime+=p[i].bursttime;
        }
        printf("\nThe average wait time is %f. Consider that the sorting process takes O(n log n)\n\n", waittime/10);
      }else if (e==3){
        printf("  You chose Priority Scheduling Algorithm\n");
        int i;
        for(i=1; i<10; i++){
          int j=rand()%9;
          int temp=p[i].priority;
          p[i].priority=p[9].priority;
          p[9].priority=temp;
        }

        printf("A random set of 10 processes was generated: Here you have it: \n");
        for(int i=0; i<10; i++){
          printf("P%d. Burst Time: %d Priority: %d\n", p[i].number, p[i].bursttime, p[i].priority);
        }
        qsort(p, 10, sizeof(struct Process), compare2);
        printf("\nThe processes were executed in the following order.\n");
        for(int i=0; i<10; i++){
          printf("P%d. Burst Time: %d Priority: %d\n", p[i].number, p[i].bursttime, p[i].priority);
          if(i!=9) waittime+=p[i].bursttime;
        }
        printf("\nThe average wait time is %f.\n\n", waittime/10);

      }else if(e==4){
        printf("  You chose Round-Robin Scheduler Algorithm\n");
        printf("The quantum is 3");
        int q=4;
        printf("A random set of 10 processes was generated: Here you have it: \n");
        int sum=0;
        for(int i=0; i<10; i++){
          printf("P%d. Burst Time: %d\n", p[i].number, p[i].bursttime);
          sum+=p[i].bursttime;
        }
        int ini=0;
        while(sum>0){
          if(p[ini].remaining>0){
            if(p[ini].remaining<=q){
              sum-=p[ini].remaining;
              printf("  %d executed from P%d. Remaining = 0. This process is complete!\n",p[ini].remaining,ini);
              p[ini].remaining=0;
            }else{
              sum-=q;
              p[ini].remaining-=q;
              printf("  %d executed from P%d. Remaining = %d.\n",q,ini,p[ini].remaining );
            }
          }
          ini++;
          if(ini>9) ini=0;
        }
        printf("Processing complete.\n");
      }
    }
    printf("Press the number of your choice and then press enter. Press 0 and then Enter to exit\n");
    scanf("%d", &e);
  }
}
