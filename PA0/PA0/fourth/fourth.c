#include <stdlib.h>
#include <stdio.h>
 
int** multiply(int** matrix, int** finalMatrix, int number, int size) {
    if(number == 1) return finalMatrix;
    if(number == 0) {
        int i = 0;
        for(; i < size; i++) {
        int j = 0;
            for(; j < size; j++) {
                finalMatrix[i][j] = 1;
            }
        }
        return finalMatrix;
    }
    int i = 0;
    int saveMatrix[size][size];
    for(; i < size; i++) {
        int j = 0;
        for(; j < size; j++) {
            int k = 0;
            int sum = 0;
            for(; k < size; k++) {
                sum+= finalMatrix[i][k] * matrix[k][j];
            }
            saveMatrix[i][j] = sum;
        }
    }
    int a = 0;
    for(; a < size; a++) {
        int b = 0;
        for(; b < size; b++) {
            finalMatrix[a][b] = saveMatrix[a][b];
        }
    }
    return multiply(matrix, finalMatrix, number - 1, size);
}
int main(int argc, char** argv) {
    if(argc != 2) {
        puts("error\n");
        return 1;
    }
    FILE *fp;
    fp = fopen(argv[1],"r");
    if(fp) {
        int size;
        fscanf(fp, "%d", &size);
        if(size == 0) return 0;
        int** finalMatrix = (int **)malloc(sizeof(int*)*size);
        int** matrix = (int **)malloc(sizeof(int*)*size);
        int number;
        int i = 0;
        for(; i < size; i++){
            matrix[i] = (int *)malloc(sizeof(int)*size);
            finalMatrix[i] = (int *)malloc(sizeof(int)*size);
            int j = 0;
            for(; j < size; j++) {
                fscanf(fp, "%d", &number);
                finalMatrix[i][j] = number;
                matrix[i][j] = number;
            }
        }  
        fscanf(fp, "%d", &number);
        multiply(matrix, finalMatrix, number, size);
        i = 0;
        for(; i < size - 1; i++){
            free(matrix[i]);
            int j = 0;
            for(; j < size - 1; j++) {
                printf("%d\t", finalMatrix[i][j]);
            }
            printf("%d\n", finalMatrix[i][j]);
            free(finalMatrix[i]);
        }
        int j = 0;
        for(; j < size - 1; j++) {
            printf("%d\t", finalMatrix[i][j]);
        }
        printf("%d", finalMatrix[i][j]);
        free(matrix[i]);
        free(matrix);
        free(finalMatrix);
    }
    else {
        puts("error\n");
        return 1;
    }
    return 0;
}