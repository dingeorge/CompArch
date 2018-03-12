#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char ** argv){
if (argc != 2){
	printf("error\n");
	exit(0);
}

const char * string = argv[1];

int a = 0;
int boolean = 0;

for (a = 0; a < strlen(string); a++){
	if (string[a] == string[a+1]){
		boolean = 0;
		break;
	}
	boolean = 1;
}

if (boolean == 1){
	printf("%s",argv[1]);
	printf("\n");
	return 0;
}

int counter = 1;

for (a = 0; a < strlen(string); a++){
	if (string[a] == '0' || string[a] == '1' || string[a] == '2' || string[a] == '3' || string[a] == '4' || string[a] == '5' || string[a] == '6' || string[a] == '7' || string[a] == '8' || string[a] == '9'){
	    printf("error\n");
	    return 0;
	}
	if (string[a] == string[a+1]){
		counter++;
	}
	else if (string[a] == '\0'){
		break;
	}
	else{
		printf("%c",string[a]);
		printf("%d", counter);
		counter = 1;
	}
}
printf("\n");
return 0;
}
