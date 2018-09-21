#include<stdlib.h>
#include<stdio.h>
#include <pthread.h>
#include<unistd.h>


//global variables
int NUM_BUFFERS;
long **buffers;
pthread_mutex_t *mutexes;
long *result;

//required functions
long *readMatrix(char* filename){
	int i;
	long *mat;
	mat=(long*)malloc(4000000*sizeof(long));
	FILE *f;
	f=fopen(filename, "r");
	for(i=0; i<4000000; i++){
		fscanf(f, "%ld", &mat[i]);	
	}
	fclose(f);
	return mat;
}
long *getColumn(int col, long*matrix);
long *getRow(int row, long * matrix);
int getLock();
int releaseLock(int lock);
long dotProduct(long *vec1, long *vec2){//assuming that the size is 2000
	long i, ans=0;
	for(i=0; i<2000; i++){
		ans+=vec1[i]*vec2[i];
	}
	return ans;
}
long *multiply(long *matA, long *matB);
int saveResultMatrix(long *result);


int main(int argc, char *argv[]){
	int i, j;
	char *a=argv[1];
	if(argc != 2){
		printf("You missed an argument, or you put more than one.\n");
		return 1; //error
	}
	int NUM_BUFFERS=atoi(a);
	printf("The number of buffers is %d\n", NUM_BUFFERS);

	long* matA=readMatrix("matA.dat");
	long* matB=readMatrix("matB.dat");
	
	printf("%ld",matA[1597829]+matB[1597829]); //the scan works


free(matA);
free(matB);
}
