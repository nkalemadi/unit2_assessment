#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_SIZE 10

void print_menu(void);
void input_matrix(double matrix[][MAX_SIZE], int *rows, int *cols, const char *name);
void print_matrix(double matrix[][MAX_SIZE], int rows, int cols, const char *name);
void add_matrices(double A[][MAX_SIZE], double B[][MAX_SIZE], double result[][MAX_SIZE], 
                  int rows, int cols);
void multiply_matrices(double A[][MAX_SIZE], double B[][MAX_SIZE], double result[][MAX_SIZE],
                       int rowsA, int colsA, int colsB);
double calculate_determinant(double matrix[][MAX_SIZE], int n);
void get_cofactor(double matrix[][MAX_SIZE], double temp[][MAX_SIZE], int p, int q, int n);
void transpose_matrix(double matrix[][MAX_SIZE], double result[][MAX_SIZE], int rows, int cols);
void scalar_multiply(double matrix[][MAX_SIZE], double result[][MAX_SIZE], 
                     int rows, int cols, double scalar);
bool get_valid_integer(int *value, const char *prompt);
bool get_valid_double(double *value, const char *prompt);

void print_menu(void) {
    printf("\n==============================================\n");
    printf("            LINEAR ALGEBRA CALCULATOR          \n");
    printf("================================================\n");
    printf("1. Matrix Addition\n");
    printf("2. Matrix Multiplication\n");
    printf("3. Calculate Determinant\n");
    printf("4. Transpose Matrix\n");
    printf("5. Scalar Multiplication\n");
    printf("6. Display Matrix\n");
    printf("7. Exit\n");
}

bool get_valid_integer(int *value, const char *prompt) {
    int result;
    char buffer[100];
    
    printf("%s", prompt);
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return false;
    }
    
    if (sscanf(buffer, "%d", &result) != 1) {
        printf("Invalid input! Please enter a valid integer.\n");
        return false;
    }
    
    *value = result;
    return true;
}

bool get_valid_double(double *value, const char *prompt) {
    double result;
    char buffer[100];
    
    printf("%s", prompt);
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return false;
    }
    
    if (sscanf(buffer, "%lf", &result) != 1) {
        printf(" Invalid input! Please enter a valid number.\n");
        return false;
    }
    
    *value = result;
    return true;
}

void input_matrix(double matrix[][MAX_SIZE], int *rows, int *cols, const char *name) {
    printf("\n Enter dimensions for %s:\n", name);
    
    do {
        if (!get_valid_integer(rows, "Number of rows (1-10): ")) {
            continue;
        }
        if (*rows < 1 || *rows > MAX_SIZE) {
            printf(" Rows must be between 1 and %d\n", MAX_SIZE);
            *rows = 0;
        }
    } while (*rows < 1 || *rows > MAX_SIZE);
    
    do {
        if (!get_valid_integer(cols, "Number of columns (1-10): ")) {
            continue;
        }
        if (*cols < 1 || *cols > MAX_SIZE) {
            printf(" Columns must be between 1 and %d\n", MAX_SIZE);
            *cols = 0;
        }
    } while (*cols < 1 || *cols > MAX_SIZE);
    
    printf("\n Enter elements for %s (%dx%d):\n", name, *rows, *cols);
    for (int i = 0; i < *rows; i++) {
        for (int j = 0; j < *cols; j++) {
            char prompt[50];
            sprintf(prompt, "Element [%d][%d]: ", i + 1, j + 1);
            while (!get_valid_double(&matrix[i][j], prompt)) {
                // Keep trying until valid input
            }
        }
    }
}

void print_matrix(double matrix[][MAX_SIZE], int rows, int cols, const char *name) {
    printf("\n%s (%dx%d):\n", name, rows, cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf(" %8.2f ", matrix[i][j]);
        }
        printf("\n");
    }
}

void add_matrices(double A[][MAX_SIZE], double B[][MAX_SIZE], double result[][MAX_SIZE], 
                  int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result[i][j] = A[i][j] + B[i][j];
        }
    }
}

void multiply_matrices(double A[][MAX_SIZE], double B[][MAX_SIZE], double result[][MAX_SIZE],
                       int rowsA, int colsA, int colsB) {
    for (int i = 0; i < rowsA; i++) {
        for (int j = 0; j < colsB; j++) {
            result[i][j] = 0;
        }
    }
    
    for (int i = 0; i < rowsA; i++) {
        for (int j = 0; j < colsB; j++) {
            for (int k = 0; k < colsA; k++) {
                result[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

void get_cofactor(double matrix[][MAX_SIZE], double temp[][MAX_SIZE], int p, int q, int n) {
    int i = 0, j = 0;
    
    for (int row = 0; row < n; row++) {
        for (int col = 0; col < n; col++) {
            if (row != p && col != q) {
                temp[i][j++] = matrix[row][col];
                if (j == n - 1) {
                    j = 0;
                    i++;
                }
            }
        }
    }
}

double calculate_determinant(double matrix[][MAX_SIZE], int n) {
    double det = 0;
    
    if (n == 1) {
        return matrix[0][0];
    }
    
    if (n == 2) {
        return (matrix[0][0] * matrix[1][1]) - (matrix[0][1] * matrix[1][0]);
    }
    
    double temp[MAX_SIZE][MAX_SIZE];
    int sign = 1;
    
    for (int f = 0; f < n; f++) {
        get_cofactor(matrix, temp, 0, f, n);
        det += sign * matrix[0][f] * calculate_determinant(temp, n - 1);
        sign = -sign;
    }
    
    return det;
}

void transpose_matrix(double matrix[][MAX_SIZE], double result[][MAX_SIZE], int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result[j][i] = matrix[i][j];
        }
    }
}

void scalar_multiply(double matrix[][MAX_SIZE], double result[][MAX_SIZE], 
                     int rows, int cols, double scalar) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result[i][j] = matrix[i][j] * scalar;
        }
    }
}

int main(void) {
    int choice;
    double matrixA[MAX_SIZE][MAX_SIZE] = {0};
    double matrixB[MAX_SIZE][MAX_SIZE] = {0};
    double result[MAX_SIZE][MAX_SIZE] = {0};
    int rowsA = 0, colsA = 0, rowsB = 0, colsB = 0;
    
    printf("\n Welcome to the Linear Algebra Calculator! \n");
    
    do {
        print_menu();
        
        while (!get_valid_integer(&choice, "Select your operation: ")) {
            printf("Please try again.\n");
        }
        
        switch (choice) {
            case 1:
                printf("\n MATRIX ADDITION\n");
                
                input_matrix(matrixA, &rowsA, &colsA, "Matrix A");
                input_matrix(matrixB, &rowsB, &colsB, "Matrix B");
                
                if (rowsA != rowsB || colsA != colsB) {
                    printf("\n Error: Matrices must have the same dimensions for addition!\n");
                    printf("Matrix A: %dx%d, Matrix B: %dx%d\n", rowsA, colsA, rowsB, colsB);
                } else {
                    add_matrices(matrixA, matrixB, result, rowsA, colsA);
                    print_matrix(matrixA, rowsA, colsA, "Matrix A");
                    print_matrix(matrixB, rowsB, colsB, "Matrix B");
                    print_matrix(result, rowsA, colsA, "Result (A + B)");
                }
                break;
                
            case 2:
                printf("\n  MATRIX MULTIPLICATION\n");
                
                input_matrix(matrixA, &rowsA, &colsA, "Matrix A");
                input_matrix(matrixB, &rowsB, &colsB, "Matrix B");
                
                if (colsA != rowsB) {
                    printf("\n Error: Number of columns in A must equal number of rows in B!\n");
                    printf("Matrix A: %dx%d, Matrix B: %dx%d\n", rowsA, colsA, rowsB, colsB);
                } else {
                    multiply_matrices(matrixA, matrixB, result, rowsA, colsA, colsB);
                    print_matrix(matrixA, rowsA, colsA, "Matrix A");
                    print_matrix(matrixB, rowsB, colsB, "Matrix B");
                    print_matrix(result, rowsA, colsB, "Result (A x B)");
                }
                break;
                
            case 3:
                printf("\n DETERMINANT CALCULATION\n");
                
                input_matrix(matrixA, &rowsA, &colsA, "Matrix A");
                
                if (rowsA != colsA) {
                    printf("\n Error: Matrix must be square to calculate determinant!\n");
                    printf("Matrix dimensions: %dx%d\n", rowsA, colsA);
                } else {
                    double det = calculate_determinant(matrixA, rowsA);
                    print_matrix(matrixA, rowsA, colsA, "Matrix A");
                    printf("\n Determinant of Matrix A: %.4f\n", det);
                }
                break;
                
            case 4:
                printf("\n MATRIX TRANSPOSE\n");
                
                input_matrix(matrixA, &rowsA, &colsA, "Matrix A");
                transpose_matrix(matrixA, result, rowsA, colsA);
                
                print_matrix(matrixA, rowsA, colsA, "Original Matrix A");
                print_matrix(result, colsA, rowsA, "Transpose of A");
                break;
                
            case 5:
                printf("\n SCALAR MULTIPLICATION\n");
                
                input_matrix(matrixA, &rowsA, &colsA, "Matrix A");
                
                double scalar;
                while (!get_valid_double(&scalar, "Enter scalar value: ")) {
                    printf("Please try again.\n");
                }
                
                scalar_multiply(matrixA, result, rowsA, colsA, scalar);
                
                print_matrix(matrixA, rowsA, colsA, "Original Matrix A");
                printf("\nScalar: %.2f\n", scalar);
                print_matrix(result, rowsA, colsA, "Result (scalar x A)");
                break;
                
            case 6:
                printf("\n DISPLAY MATRIX\n");
                
                input_matrix(matrixA, &rowsA, &colsA, "Matrix");
                print_matrix(matrixA, rowsA, colsA, "Your Matrix");
                break;
                
            case 7:
                printf("\n Thank you!\n");
                break;
                
            default:
                printf("\n Invalid choice! Please select a number between 1 and 7.\n");
        }
        
        if (choice >= 1 && choice <= 6) {
            printf("\nPress Enter to continue...");
            getchar();
        }
        
    } while (choice != 7);
    
    return 0;
}
