#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void transpose(double ** trainmatrix, double ** transposematrix, int rows, int columns){
 
  int i, j;
  for (i = 0; i < rows; i++){
    for (j = 0; j < columns; j++){
      transposematrix[j][i] = trainmatrix[i][j];
    }
  }

}

void multiply(double ** transpose, double ** multipliedmatrix, double ** matrix, int row1, int row2, int col2){
  
  int i = 0, j = 0, k = 0;
  double sum = 0;
  for (i = 0; i < row1; i++){
    for (j = 0; j < row2; j++){
      for (k = 0; k < col2; k++){
	sum = sum + (transpose[i][k] * matrix[k][j]);
      }
      multipliedmatrix[i][j] = sum;
      sum = 0;
    }
  }
}

void inverse(double ** matrix, double ** input, int size){
 double ** augMatrix = (double **)malloc(sizeof(double*) * size);
  
  int i = 0;
  int j = 0;
  int identitycounter = 0;  
  while (i < size){
    augMatrix[i] = (double*)malloc(sizeof(double) * 2 * size);
    i++;
  }
  
  for (i = 0; i < size; i++){
    for (j = 0; j < 2 * size; j++){
      if (j < size){
	augMatrix[i][j] = matrix[i][j];
      }
      else if (identitycounter == i){
	augMatrix[i][j+identitycounter] = 1;
	identitycounter++;
      }
      else{
	if (augMatrix[i][j] == 1){
	  continue;
	}
	else{
	  augMatrix[i][j] = 0;
	}
      }
    }
  }
  
  int col = 2 * size;
  double t;
  int k;
  
  for (i = 0; i < size; i++){
    for (j = 0; j < size; j++){
  	t = augMatrix[j][i];
	for (k = 0; k < col; k++){
		if (i != j){
		augMatrix[j][k] = (augMatrix[i][i] * augMatrix[j][k]) - (t * augMatrix[i][k]);
		}
	}
    }
  } 	

double divisor;

for ( i = 0; i < size; i++){
	for (j = 0; j < col; j++){
		if (i == j){
		divisor = augMatrix[i][j];
		augMatrix[i][j] = augMatrix[i][j] / divisor;
		}
		if (j >= size){
		augMatrix[i][j] = augMatrix[i][j] / divisor;
		}
	}
}

for (i = 0; i < size; i++){
  for (j = size; j < col; j++){
    input[i][j - size] = augMatrix[i][j];
   }
}


}

int main(int argc, char ** argv){

FILE *train, *test;

if (argc != 3){
  printf("error\n");
  return 0;    
}

train = fopen(argv[1], "r");
test = fopen (argv[2], "r");

if (train == NULL || test == NULL){
  printf("error\n");
  return 0;    
}
int rows = 0;
int cols = 0;

fscanf(train, "%d\n%d", &cols,&rows);

double ** trainmatrix = (double**)malloc(sizeof(double*) * rows);
double ** trainmatriy = (double**)malloc(sizeof(double*) * rows);
double ** matrix = (double**)malloc(sizeof(double*) * rows);

int i = 0, a = 0, b = 0;

while (i < rows){
  trainmatrix[i] = (double*)malloc(sizeof(double) * (cols+1));
  trainmatriy[i] = (double*)malloc(sizeof(double));
  matrix[i] = (double*)malloc(sizeof(double) * (cols+1));
  i++;
}

cols = cols + 1;

for (a = 0; a < rows; a++){
  for (b = 0; b < cols; b++){
    fscanf(train, "%lf,", &trainmatrix[a][b]);
  }
}

for (a = 0; a < rows; a++){
  trainmatriy[a][0] = trainmatrix[a][cols - 1];
}

for ( a = 0; a < rows; a++){
  for (b = 0; b < cols; b++){
    if(b ==0){
      matrix[a][b] = 1;
    }
    else{
      matrix[a][b] = trainmatrix[a][b-1];
    }
  }
}
double ** transposematrix = (double**)malloc(sizeof(double*) * cols);
double ** multipliedmatrix = (double**)malloc(sizeof(double*) * cols);
double ** inversed = (double**)malloc(sizeof(double*) * cols);
double ** asd = (double**)malloc(sizeof(double*) * cols);
double ** asd1 = (double**)malloc(sizeof(double*) * cols);

i = 0;
while (i < cols){
   transposematrix[i] = (double*)malloc(sizeof(double) * rows);
   multipliedmatrix[i] = (double*)malloc(sizeof(double) * cols);
   inversed[i] = (double*)malloc(sizeof(double) * cols);
   asd[i] = (double*)malloc(sizeof(double));
   asd1[i] = (double*)malloc(sizeof(double));
   i++;
}
  transpose(matrix, transposematrix, rows, cols);
  
  multiply(transposematrix, multipliedmatrix, matrix, cols, cols, rows);
  
  inverse(multipliedmatrix, inversed, cols);
  
  multiply(transposematrix, asd, trainmatriy, cols, 1, rows);
  
  multiply(inversed, asd1, asd, cols, 1, cols);
  
  int something;
  fscanf(test, "%d\n", &something);
  
  double total;
  double reading;
  
  for (a = 0; a < something; a++){
    for (b = 0; b < cols; b++){
      if (b == 0){
	total = total + asd1[b][0];
      }
      else{
	fscanf(test, "%lf,", &reading);
	total = total + (asd1[b][0] * reading);
      }
    }
    printf("%0.0f\n", total);
      total = 0;
  }
  

return 0;
}