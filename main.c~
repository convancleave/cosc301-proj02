#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <ctype.h>
#include <sys/resource.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <poll.h>
#include <signal.h>
//Conor Oliver, Connor Van Cleave, Matt Condit

// creates array from buffer
void make_array(char* buf, char** argv, int size) {
	char* token;
	char* cop = strdup(buf);
	
	int i=0;
	for (token =strtok(cop,"; "); token!=NULL; token=strtok(NULL,"; ")) {
		argv[i] = strdup(token);
		i++;
	}
	argv[size] = NULL;
	free(cop);
} 

// gets size of array from buffer
int size_of_array(char* buf) {
	char* token;
	char* cop = strdup(buf);

	int count=0;
	for (token=strtok(cop,"; "); token!=NULL;token=strtok(NULL," ;")) {
		count++;
	}
	return count;
}



//test function: print array
void print_array(char** a, int size) {
	int i=0;
	while (i<size) {
		printf("%s\n", a[i]);
		i++;
	}
}

int main(int argc, char **argv) {
	char prompt[] = "prompt> ";	
	printf("%s",prompt);
	fflush(stdout);
	
	char buffer[1024];
	while (fgets(buffer, 1024, stdin) != NULL) {
		printf("%s",prompt);
		
		//handles comments, but only at the end of command		
		int i=0;	
		while (buffer[i]!='\0') {
			if (buffer[i]=='#') {
				buffer[i] = '\0';
				i--;
			}
			i++;
		}
		//
		int size = size_of_array(buffer);		
		char** argv = (char**) malloc(sizeof(char*)*(size+1));
		make_array(buffer,argv,size);		
		//		print_array(argv,size);

		int childrv;
		pid_t pid = fork();

		if (pid==0) {
			printf("send it");
			childrv = execv(argv[0], argv);
		} else {
			wait(&childrv);
			printf("Child process finished\n");
		}
	
		
		
	}
	
    return 0;
}

	

