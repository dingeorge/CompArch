#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char ** argv){
int i = 1;

for (i = 1; i < argc; i++){
	char * currentword = argv[i];
	int a = 0;
	
	while (currentword[a] != '\0'){
		a++;
	}
	
	printf("%c", currentword[a-1]);
}
return 0;
}
