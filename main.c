#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"

int main(int argc, char ** argv){
    Matrix m = createMatrix(2, 2);
    setElement(&m, 2.52, 0, 0);
    setElement(&m, 3, 0, 1);
    setElement(&m, 5, 1, 0);
    setElement(&m, 10, 1, 1);
    printMatrix(&m);

    //testing matrix reduction
    // reduceMatrix(&m);
    printMatrix(&m);

    destroyMatrix(&m);
    return 0;
}

Matrix createMatrix(int r, int c){
    Matrix output;
    output.rows = r;
    output.columns = c;
    output.body = calloc(sizeof(double) * r * c, sizeof(double)); //Initialize the memory here so that each matrix is useable by default

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
void multiplyElement(Matrix *matrix, double coefficient, int r, int c){
    setElement(matrix, getElement(matrix, r, c) * coefficient, r, c);
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

void reduceMatrix(Matrix *matrix){
    //Bulk of the program will be in this function
    for(int r=0; r <matrix->rows;r++ ){
        double coefficient = getElement(matrix, r, r); //this works becaues we reduce across the diagonal
        multiplyRow(matrix, r, 1/coefficient); //TODO ad step for checking if coefficient is missing an swapping if not

        //Zero out the rest of function
        for(int r2=0; r2<matrix->rows; r2++){
            if (r2 == r){
                continue; //no need to reduce because this row contains a desired coefficient
            }

            double coefficient_to_clean = getElement(matrix, r2, r); 
            multiplyRowThenAdd(matrix, r, r2, -coefficient);
        }
    }
}

void multiplyRow(Matrix *matrix, int row, double coefficient){
   for (int i = 0; i < matrix->columns; i++) {
        multiplyElement(matrix, coefficient, row, i);
    }
}

void multiplyRowThenAdd(Matrix *matrix, int row_source, int row_destination, double coefficient){
    for(int c=0; c<matrix->columns; c++){
        double val = getElement(matrix, row_source, c) * coefficient + getElement(matrix, row_destination, c); 
        setElement(matrix, val, row_destination, c);
    }
}


void printMatrix(Matrix *matrix){
    for(int r=0; r < matrix->rows;r++){
        for(int c=0; c < matrix->columns;c++){
           printf("%lf ", getElement(matrix, r, c)); 
        }
        printf("\n");
    }
}


