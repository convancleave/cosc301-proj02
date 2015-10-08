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
		
	}
    return 0;
}


