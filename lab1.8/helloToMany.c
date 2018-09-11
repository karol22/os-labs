//Karol Gutiérrez
#include <pthread.h>
#include <stdio.h>

void *runner(void *param){//function that runs the threads
    printf("Hello from thread %d - I was created in iteration %d\n", param+2, param);
    pthread_exit(0);
}

main(){
	int n, i; //number of threads
	printf("Enter the number of threads: \n");
	scanf("%d", &n);
	pthread_t tid[n];//stores thread ids
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	for(i=0; i<n; i++){
		printf("I am thread 1. Created new thread (%d) in iteration %d...\n", i+2, i);
		pthread_create(&tid[i],&attr,runner,(void *)i);
		if(i%5==0) sleep(1);
	}	
}


