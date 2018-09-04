#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_LINE		80 /* 80 chars per line, per command */
char hist[10][MAX_LINE];
int counter=0;

void inputHandler(char *, char **,int *);
void historyHandler();

int main(void){
  char *args[MAX_LINE/2+1];
  int should_run=1, concurrent;
  char line[MAX_LINE];
  pid_t pid;
  while (should_run){
    concurrent=0;
    printf("kzh>");
    fflush(stdout);
    inputHandler(line, args, &concurrent);
    pid=fork();
    if (pid<0){
      printf("Error while forking! \n");
      return 1;
    }else if (pid==0){
        if (execvp(args[0], args)==-1 && strcmp(line, "history")!=0)
          printf("Invalid command\n");
    }else if (concurrent==0)
        wait(NULL);
  }
  return 0;
}

void inputHandler(char line[], char *args[],int *concurrent)
{
    int length, index=0, next=-1, i=0;
    length=read(STDIN_FILENO, line, MAX_LINE);
    if (length==0)
        return;
    while(i<length){
      if(line[i]==' '){
        if(next!=-1){
          args[index]=&line[next];
          index++;
        }
        line[i]='\0';
        next=-1;
      }else if(line[i]=='\n'){
        if (next !=-1){
          args[index]=&line[next];
          index++;
        }
        line[i]='\0';
        args[index]=NULL;
      }else if(line[i]=='&'){
        *concurrent=1;
        line[i]='\0';
      }else if (next==-1){
        next=i;
      }
      i++;
    }
    args[index]=NULL;
    if(strcmp(args[0],"history")==0){
          historyHandler();
    } else if (*args[0]=='!'){
    		int first=args[0][1];
    		int second=args[0][2];
    		if(first-'0'>counter || first=='0'){
      		printf("\nEnter a number between 1 and 9\n");
    		}else if(second!=0){
    			printf("\nInvalid command. Enter a number between 1 and 9\n");
    		}else{
    		    if(first=='!'){
    					 strcpy(line,hist[0]);
            }	else if(first>=1){
                printf("caso 3");
    						strcpy(line,hist[counter-(first-'0')]);
    				}
    		}
    }
    for(i=9; i>0; i--)
    	strcpy(hist[i], hist[i-1]);
    strcpy(hist[0],line);
    counter++;
    if(counter>10){
    	counter=10;
    }
}

void historyHandler(){
    int i, j;
    for (i=counter-1; i>=0; i--){
       	printf("%d  ", i+1);
        for(j=0; hist[i][j]!='\n' && hist[i][j]!=0; j++)
          printf("%c", hist[i][j]);
        printf("\n");
    }
}
