  /*
Lab 4.2 - The Dinning Philosophers Problem
Diego Ivan Contreras Villegas A00817130
Daniela Abigail Parrale Mejía A01228629
Karol Gutiérrez A01024536

Compile with the following commands:
gcc -o dinning_philosophers dinning_philosophers.c -lpthread

Stop the program with Ctrl+Z

*/

#include <stdio.h>  
#include <pthread.h> 
#include <semaphore.h> 
  

#define N 5 		//Number of philosophers
int THINKING=2;
int HUNGRY=1;
int EATING=0;
int state[N]; 
int phil[N]; 
  
sem_t mutex; 
sem_t S[N]; 
  
void test(int phils){ 
    if (state[phils] == HUNGRY && state[(phils+4)%N] != EATING && state[(phils+1)%N] != EATING) { 
        // state that eating 
        state[phils] = EATING; 
  
        sleep(2); 
  
        printf("Philosopher %d takes forks number #%d and #%d\n", phils + 1, (phils+4)%N+1, phils + 1); 
        printf("Philosopher %d is eating\n", phils + 1); 
        
        sem_post(&S[phils]); 
    } 
} 
  
// take up chopsticks 
void take_fork(int phils) { 
  
    sem_wait(&mutex); 
  
    // Define as hungry
    state[phils] = HUNGRY; 
  
    printf("Philosopher %d is hungry\n", phils + 1); 
  
    //Eat if neighbours are not eating 
    test(phils); 
  
    sem_post(&mutex); 
  
    //wait to be signalled if unable to eat 
    sem_wait(&S[phils]); 
  
    sleep(1); 
} 
  
// put down chopsticks 
void put_fork(int phils) { 
  
    sem_wait(&mutex); 
  
    // state that thinking 
    state[phils] = THINKING; 
  
    printf("Philosopher %d putting down the forks #%d and #%d\n", 
           phils + 1, (phils+4)%N+1, phils + 1); 
    printf("Philosopher %d is thinking\n", phils + 1); 
  
    test((phils+4)%N); 
    test((phils+1)%N); 
  
    sem_post(&mutex); 
} 
  
void* philospher(void* num) { 
  
    while (1) { 
  
        int* i = num; 
  
        sleep(1); 
  
        take_fork(*i); 
  
        sleep(0); 
  
        put_fork(*i); 
    } 
} 
  
int main(void){ 
  
    int i; 
    for(i=0; i<N; i++){
    	phil[i]=i;
    }
    pthread_t thread_id[N]; 
  
    // initialize the semaphores 
    sem_init(&mutex, 0, 1); 
  
    for (i = 0; i < N; i++) 
        sem_init(&S[i], 0, 0); 
  
    for (i = 0; i < N; i++){ 
        pthread_create(&thread_id[i], NULL, 
                       philospher, &phil[i]); 
        printf("Philosopher %d is thinking\n", i + 1); 
    }
  
    for (i = 0; i < N; i++) 
        pthread_join(thread_id[i], NULL); 
    return 0;
} 
