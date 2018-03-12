#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char ** argv){
	
if (argc < 2){
	printf("error");
	return 0;
}

FILE *file;

char buffer[300];

file = fopen(argv[1],"r");

if (file == NULL){
	printf("error/n");
	return 0;
}

fscanf(file,"%s\n",buffer);

char * squarepoint = strtok(buffer,"\n");

int square = atoi(squarepoint);

int matrix1[(square)*(square)];
int matrix[square][square];

int a = 0, b = 0;

while (fscanf(file, "%s", buffer)!=EOF){
	int number = atoi(buffer);
	matrix1[a] = number;
	a++;
}

for (a = 0; a < sizeof(matrix1)/sizeof(matrix1[0]); a++){
	int checka = matrix1[a];
	for (b = a+1; b < sizeof(matrix1)/sizeof(matrix1[0]); b++){
		int checkb = matrix1[b];
		if (checka == checkb){
			printf("not-magic");
			return 0;
		}
	}
}

int i = 0;

for (a = 0; a < square; a++){
	for (b = 0; b < square; b++){
		matrix[a][b] = matrix1[i];
		i++;
	}
} 

int checkingNum = 0;

for (a = 0; a < square; a++){
	checkingNum += matrix[0][a];
}

int resulthor = 0;
int resultvert = 0;
int resultleftx = 0;
int resultrightx = 0;

for (a = 0; a < square; a++){
	for(b = 0; b < square; b++){
		resulthor += matrix[a][b];
		resultvert += matrix[b][a];
		if (a == b){
			resultleftx += matrix[a][b];
		}
		if (a+b == square-1){
			resultrightx += matrix[a][b];
		}
	}
	if (resultvert != checkingNum || resulthor != checkingNum){
		printf("not-magic");
		return 0;
	}
	resulthor = 0;
	resultvert = 0;
}	

if (resultrightx != checkingNum || resultleftx != checkingNum){
	printf("not-magic");
	return 0;
}
printf("magic");
return 0;
}



	
