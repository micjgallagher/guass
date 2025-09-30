struct matrix{
    double * body;
    int rows; 
    int columns;
};
//Matrices will be zero indexed but the rows and columns will still be accurate

typedef struct matrix Matrix; 

Matrix createMatrix(int r, int c);
Matrix copyMatrix(Matrix * matrix);
void destroyMatrix(Matrix * matrix);
double getElement(Matrix * matrix, int r, int c);
void setElement(Matrix * matrix, double value, int r, int c);
void multiplyElement(Matrix * matrix, double coefficient, int r, int c);
int getIndex(Matrix * matrix, int r, int c);
void printMatrix(Matrix *matrix);

//Gaussian Functions
void reduceMatrix(Matrix * matrix);

//Row Equivalency Functions

void multiplyRow(Matrix * matrix, int row, double coefficient);
void multiplyRowThenAdd(Matrix * matrix, int row_source, int row_destination, double coefficient);

//Parsing Functions

/*
 * Variable must be 26 characters long, function will write to the array. Returns amount of variables identified
 */
int identifyVariables(char variables[26], int argc, char **argv);
int isLowerAlpha(char c);
int isNumeric(char c);
int containsChar(char *string, int size, char c);

//equations should point to the first valid equation
//num_equations should be the actual number of equations, not simply argc
Matrix constructMatrixFromEquations(int num_equations, int num_variables, char variables[26], char **equations);
void collectCoefficients(Matrix *matrix, char variables[26], int num_variables, char * equation, int row);

//Array helper functions
//Negative -1 indicates value could not be found 
int locateInArray(char * array, int array_length, char target);
