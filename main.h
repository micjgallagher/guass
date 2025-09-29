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
