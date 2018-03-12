#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char ** argv){

FILE *file;
char buffer[300];

file = fopen(argv[1],"r");

fgets(buffer,sizeof(buffer),file);

char * arraySize = strtok(buffer,"\n");
int arraySze = atoi(arraySize);

int array[arraySze];

int i = 0;
	
while (fscanf(file,"%s",buffer) != EOF){
	array[i] = atoi(buffer);
	i++;
}

int a,b, key;
for (a = 1; a < sizeof(array)/sizeof(array[0]); a++){
	key = array[a];
	b = a-1;
	while (b >= 0 && array[b] > key){
		array[b+1] = array[b];
		b = b-1;
	}
	array[b+1] = key;
}

for (a = 0; a < sizeof(array)/sizeof(array[0]); a++){
	printf("%d\t", array[a]);
}

printf("\n");

return 0;
}
