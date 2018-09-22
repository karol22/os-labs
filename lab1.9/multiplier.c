#include<stdlib.h>
#include<stdio.h>
#include <pthread.h>

#define N 2000


//global variables
int NUM_BUFFERS;
long **buffers;
pthread_mutex_t *mutexes;
long *result;

//required functions
long *readMatrix(char* filename){
	int i;
	long *mat;
	mat=(long*)malloc(N*N*sizeof(long));
	FILE *f;
	f=fopen(filename, "r");
	for(i=0; i<9; i++){
		fscanf(f, "%ld", &mat[i]);
	}
	fclose(f);
	return mat;
}
void printMatrix(long *matrix, int len){
  int i, j;
  for(i=0; i<len; i++){
    for(j=0; j<len; j++){
      printf("%ld ", matrix[len*i+j]);
    }
    printf("\n");

  }
}
long *getColumn(int col, long*matrix){
	int i;
	long *ans=(long*)malloc(N*sizeof(long));
	for(i=0; i<N; i++){
		ans[i]=matrix[i*N+col];
	}
	return ans;
}
long *getRow(int row, long * matrix){
	int i;
	long *ans=(long*)malloc(N*sizeof(long));
	for(i=0; i<N; i++){
		ans[i]=matrix[row*N+i];
	}
	return ans;
}
long dotProduct(long *vec1, long *vec2){
	long i, ans=0;
	for(i=0; i<N; i++){
		ans+=vec1[i]*vec2[i];
	}
	return ans;
}
int saveResultMatrix(){
  int i;
	FILE *f;
	f=fopen("result.dat", "w");
	for(i=0; i<N*N; i++){
		fprintf(f, "%ld\n", result[i]);
	}
	fclose(f);
  return 0;
}
int getLock(){
	int i;
	for(i=0; i<NUM_BUFFERS; i++)
		if(0==pthread_mutex_trylock(&mutexes[i])) return i;
	return -1;
}
int releaseLock(int lock){
	if(0==(pthread_mutex_unlock(&mutexes[lock]))) return 0;
		return -1;	
}

long *multiply(long *matA, long *matB){
	int i, j;
	long *rr=malloc(N*sizeof(long));
	long *cc=malloc(N*sizeof(long));
	for(i=0; i<N; i++){
		for(j=0; j<N; j++){
			rr=getRow(i, matA);
			cc=getColumn(j, matB);
			result[N*i+j]=dotProduct(rr,cc);
		}
	}
	return result;
}


int main(int argc, char *argv[]){
	int i, j;
	char *a=argv[1];
	if(argc != 2){
		printf("You missed an argument, or you put more than one.\n");
		return 1; //error
	}
	int NUM_BUFFERS=atoi(a);

	long* matA=readMatrix("matA.dat");
	long* matB=readMatrix("matB.dat");

	/* //se alenta mucho al usar mutexes pues se generan copias innecesarias
	mutexes=malloc(NUM_BUFFERS*sizeof(pthread_mutex_t));
	buffers=malloc(NUM_BUFFERS*sizeof(long*));
	for(i=0;i<NUM_BUFFERS;i++){
		buffers[i]=malloc(N*sizeof(long));
	}
  result=malloc(N*N*sizeof(long));
	*/

	multiply(matA, matB);
	saveResultMatrix();

	free(matA);
	free(matB);
	free(result);
	//free(buffers);
	//pthread_mutex_destroy(mutexes);
	return 0;
}
