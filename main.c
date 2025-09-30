#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"

const int var_array_size = 26;


int main(int argc, char ** argv){
    if(argc > 1){
        for(int i=1;i<argc;i++){
            printf("%s\n", argv[i]);
        }
    }
    char vars[var_array_size];
    int num_var = identifyVariables(vars, argc, argv);
    printf("Identified %d variables\n", num_var);

    for(int i=0;i<num_var;i++){
        printf("%c ", vars[i]);
    }
    printf("\n");
    
    if(argc > 1){
        //construct matrix from equations
        Matrix augmented = createMatrix(argc-1, num_var);
        collectCoefficients(&augmented, vars, num_var, argv[1], 0);
        printf("\nTESTING MATRIX\n");
        printMatrix(&augmented);
        printf("\nTESTING MATRIX\n");
        destroyMatrix(&augmented);
    }

    Matrix m = createMatrix(2, 2);
    setElement(&m, 2.52, 0, 0);
    setElement(&m, 3, 0, 1);
    setElement(&m, 5, 1, 0);
    setElement(&m, 10, 1, 1);
    printMatrix(&m);
    /*
    setElement(&m, 10, 0,0);
    setElement(&m, 10, 0,1);
    setElement(&m, 5, 1,0);
    setElement(&m, 5, 1,1);
    printMatrix(&m);
    multiplyRowThenAdd(&m, 1, 0, -2);
    printMatrix(&m);
    */

    //testing matrix reduction
    reduceMatrix(&m);
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

        printMatrix(matrix);
        //Zero out the rest of function
        for(int r2=0; r2<matrix->rows; r2++){
            if (r2 == r){
                continue; //no need to reduce because this row contains a desired coefficient
            }

            double coefficient_to_clean = getElement(matrix, r2, r) / getElement(matrix, r, r); 
            printf("Coefficient %lf\n", coefficient_to_clean);
            multiplyRowThenAdd(matrix, r, r2, -coefficient_to_clean);
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
    printf("\n");
}

int identifyVariables(char variables[26], int argc, char **argv){
    //test comment
    const int array_size = 26;
    int occupied = 0;
    for(int string_index = 1; string_index < argc; string_index++){
        //debug 
        char *current = argv[string_index];
        printf("Now examining : %s\n", current);

        while (*current!='\0'){
            if(isLowerAlpha(*current)){
                if(!containsChar(variables, occupied, *current)){
                    variables[occupied] = *current;
                    occupied++;
                }
            }
            current++;
        }

    }
    return occupied;
}

int isLowerAlpha(char c){
    return c >= 'a' && c <= 'z';
}

int isNumeric(char c){
    return c>= '0' && c<='9';
}

int containsChar(char *string, int size, char c){
    for(int i=0; i<size; i++){
        if(string[i] == c){
            return 1;
        }
    }
    return 0;
}

int locateInArray(char *array, int array_length, char target){
    for (int i=0; i<array_length; i++){
        if(array[i] == target){
            return i;
        }
    }
    return -1;
}

Matrix constructMatrixFromEquations(int num_equations, int num_variables, char variables[26], char ** equations){
    int num_columns = num_variables + 1; //The additional column is to augment the matrix to collect the constants
    Matrix output = createMatrix(num_equations, num_columns);
    //collect coefficients
    return output;
}


void collectCoefficients(Matrix *matrix, char *variables, int num_variables, char *equation, int row){
    char buff[100]; //Determine whether to cap the size of the variables, or make an expandable buffer
    int buff_pos = 0;
    while(*equation != '\0'){
        if(isNumeric(*equation)){
            buff[buff_pos]=*equation;
            buff_pos++;
        } else if(buff_pos > 0){
            buff[buff_pos] = '\0';
            double coefficient = atof(buff);
            int column =  locateInArray(variables, num_variables, *equation); //Because the variables are put in the array in the order found, we can use that order to define their corresponding column in the matrix 
            
            if(column < 0){
                fprintf(stderr, "ERROR: UNABLE TO LOCATE VARIABLE. THIS MESSAGE SHOULD NEVER APPEAR");
                return;
            }

            setElement(matrix,coefficient, row, column);

            //debug 
            printf("extracted %lf\n", coefficient);
            memset(buff, 0, 100);
            buff_pos = 0;
        }
        equation++;
    }
}
