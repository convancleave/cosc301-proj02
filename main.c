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



void make_array(char* buf, char** argv, int size) {
	char* token;
	char* cop = strdup(buf);
	
	int i=0;
	
	for (token=strtok(cop,";"); token!=NULL; token=strtok(NULL,";")){
		argv[i] = strdup(token);
		i++;
	}
	argv[size] = NULL;
	free(cop);
} 

void make_array2(char* buf, char** argv, int size) {
	char* token;
	char* cop = strdup(buf);
	
	int i=0;
	for (token=strtok(cop," \n\t"); token!=NULL; token=strtok(NULL," \n\t")){
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
	for (token=strtok(cop,";"); token!=NULL;token=strtok(NULL,";")) {
		count++;
	}
	return count;
}

int size_of_array2(char* buf) {
	char* token;
	char* cop = strdup(buf);

	int count=0;
	for (token=strtok(cop," \n\t"); token!=NULL;token=strtok(NULL," \n\t")) {
		count++;
	}
	free(cop);
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

int run_sequential(char** argv, int size) {
	int e=0;	
	int output = 0;
	for (int i=0;i<size; i++) {
			int subsize = size_of_array2(argv[i]);			
			char** cmd = (char**) malloc(sizeof(char*)*(subsize+1));
			//printf("%d\n",subsize);
			make_array2(argv[i],cmd,subsize);
			//print_array(cmd,subsize);			

			int childrv;
			
			
			//char *cmd[] = { "/bin/ls", "-ltr", ".", NULL };
			if (strcmp(cmd[0],"exit")==0) {
				e=1;
			}	
			if (strcmp(cmd[0],"mode")==0) {
				if (subsize==1) {
					printf("sequential");
				}
				else if (strcmp(cmd[1],"parallel")||strcmp(cmd[1],"p"))
					{output=1;}
			}			
			else { pid_t pid = fork();
			if (pid==0) {
				//printf("%s\n", argv[0]);
				childrv = execv(cmd[0], cmd);
				if (childrv<0) {
					fprintf(stderr, "execv failed: %s\n", strerror(1));
				}
			} else {
				wait(&childrv);
				//printf("Child process finished\n");
			} }
		} //end sequential for loop
		if (e==1) {
			exit(0);
		}
		return output;
}

int run_par(char** argv, int size) {
	int e=0;	
	int output = 1;

	while(1)	{
		for (int i=0;i<size; i++) {
		int subsize = size_of_array2(argv[i]);
		char			
		char** cmd = (char**) malloc(sizeof(char*)*(subsize+1));
		//printf("%d\n",subsize);
		make_array2(argv[i],cmd,subsize);
		//print_array(cmd,subsize);	
		}

	}

			

			int childrv;
			
			
			//char *cmd[] = { "/bin/ls", "-ltr", ".", NULL };
			if (strcmp(cmd[0],"exit")==0) {
				e=1;
			}	
			if (strcmp(cmd[0],"mode")==0) {
				if (subsize==1) {
					printf("parallel");
				}
				else if (strcmp(cmd[1],"sequential")||strcmp(cmd[1],"s"))
					{output=0;}
			}			
			else { pid_t pid = fork();
			if (pid==0) {
				//printf("%s\n", argv[0]);
				childrv = execv(cmd[0], cmd);
				if (childrv<0) {
					fprintf(stderr, "execv failed: %s\n", strerror(1));
				}
			} 
		}
		} //end par for loop
		if (e==1) {
			exit(0);
		}
		return output;
}



int main(int argc, char **argv) {
	char prompt[] = "prompt> ";	
	printf("%s",prompt);
	fflush(stdout);
	int m=0; //keep track of mode
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
		
		//print_array(argv,size);
		//printf("%d\n", size);

		
		
		if (m==0) {
			m = run_sequential(argv,size);
		}
		
		else if (m==1) {
			m = run_par(argv,size);
			pid_t pid;
			int num;
			/*while ((pid = waitpid(-1, &stat, WNOHANG))>0) {
				printf("child process finished /n");
			}*/
		
		}
		
	

	} // end shell while loop
	
    return 0;
}

	

