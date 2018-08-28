#include <stdio.h>
#include <stdlib.h>


FILE *txt;

void recursivo(char path[1024]){
	fprintf(txt, "The current location is %s \n", path);
	char c_command[1024]="cd ";
	strcat(c_command, path);
	strcat(c_command, "; ls -R | grep \"\\.c$"); 
	fprintf(txt, "The .c files are: \n");
	FILE *f = popen(c_command, "r");
	char data[1024];
	
	while(fgets(data, sizeof(data)-1, f)!=NULL){
		fprintf(txt,"%s", data);
	}
	fclose(f);

	char h_command[1024]="cd ";
	strcat(h_command, path);
	strcat(h_command, "; ls -R | grep \"\\.h$"); 
	fprintf(txt, "The .h files are: \n");
	FILE *f2 = popen(h_command, "r");
	char data2[1024];
	while(fgets(data2, sizeof(data2)-1, f2)!=NULL){
		fprintf(txt,"%s", data2);
	}
	fclose(f2);
		
}

int main(){
	txt = fopen("linux_source_structure.txt", "a");
	
	FILE *f = popen("cd ..", "r");
	f=popen("pwd", "r");
	char data[1024];
	
	while(fgets(data, sizeof(data)-1, f)!=NULL){
		printf("%s", data);
	}
	char initial_path[1024]="/home/oscreader/os-labs/lab1.5";

	
	pclose(f);
	recursivo(initial_path);
	return 0;
}
