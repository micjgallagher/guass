#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"

int main(int argc, char ** argv){
    printf("Test\n");
    return 0;
}

Matrix createMatrix(int r, int c){
    Matrix output;
    output.rows = r;
    output.columns = c;
    output.body = calloc(sizeof(double) * r * c, 0); //Initialize the memory here so that each matrix is useable by default

    return output;
}

int getIndex(Matrix * matrix, int r, int c){
    return c + matrix -> columns * r;
}

double getElement(Matrix *matrix, int r, int c){
    return matrix->body[getIndex(matrix, r, c)];
}

void setElement(Matrix *matrix, double value, int r, int c){
    matrix->body[getIndex(matrix, r, c)] = value;
}

Matrix copyMatrix(Matrix *matrix){
    Matrix output;
    int size = matrix->rows * matrix->columns;
    output.body = malloc(sizeof(double) * size);
    memcpy(output.body, matrix->body, sizeof(double) * size);
    return output;
}

void destroyMatrix(Matrix *matrix){
    free(matrix->body);
    matrix->body=NULL;
    matrix->rows = 0;
    matrix->rows = 0;
}
