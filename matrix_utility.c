#include <stdio.h>

#define MAX 10

void inputMatrix(int a[][MAX], int r, int c);
void printMatrix(int a[][MAX], int r, int c);
void addMatrices();
void subtractMatrices();
void multiplyMatrices();
void transposeMatrix();

int main() {
    int choice;

    do {
        printf("\n===== Matrix Manipulation Utility =====\n");
        printf("1. Add two matrices\n");
        printf("2. Subtract two matrices\n");
        printf("3. Multiply two matrices\n");
        printf("4. Transpose of a matrix\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            addMatrices();
            break;
        case 2:
            subtractMatrices();
            break;
        case 3:
            multiplyMatrices();
            break;
        case 4:
            transposeMatrix();
            break;
        case 5:
            printf("Exiting program...\n");
            break;
        default:
            printf("Invalid choice! Please try again.\n");
        }

    } while (choice != 5);

    return 0;
}

void inputMatrix(int a[][MAX], int r, int c) {
    int i, j;
    printf("Enter elements (%d x %d):\n", r, c);
    for (i = 0; i < r; i++) {
        for (j = 0; j < c; j++) {
            printf("a[%d][%d] = ", i, j);
            scanf("%d", &a[i][j]);
        }
    }
}

void printMatrix(int a[][MAX], int r, int c) {
    int i, j;
    printf("Matrix (%d x %d):\n", r, c);
    for (i = 0; i < r; i++) {
        for (j = 0; j < c; j++) {
            printf("%4d ", a[i][j]);
        }
        printf("\n");
    }
}

void addMatrices() {
    int r, c;
    int A[MAX][MAX], B[MAX][MAX], C[MAX][MAX];
    int i, j;

    printf("\n--- Matrix Addition ---\n");
    printf("Enter number of rows and columns (same for both): ");
    scanf("%d %d", &r, &c);

    if (r <= 0 || c <= 0 || r > MAX || c > MAX) {
        printf("Invalid size!\n");
        return;
    }

    printf("\nEnter Matrix A:\n");
    inputMatrix(A, r, c);
    printf("\nEnter Matrix B:\n");
    inputMatrix(B, r, c);

    // Addition
    for (i = 0; i < r; i++) {
        for (j = 0; j < c; j++) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }

    printf("\nMatrix A:\n");
    printMatrix(A, r, c);
    printf("\nMatrix B:\n");
    printMatrix(B, r, c);
    printf("\nA + B = \n");
    printMatrix(C, r, c);
}

void subtractMatrices() {
    int r, c;
    int A[MAX][MAX], B[MAX][MAX], C[MAX][MAX];
    int i, j;

    printf("\n--- Matrix Subtraction (A - B) ---\n");
    printf("Enter number of rows and columns (same for both): ");
    scanf("%d %d", &r, &c);

    if (r <= 0 || c <= 0 || r > MAX || c > MAX) {
        printf("Invalid size!\n");
        return;
    }

    printf("\nEnter Matrix A:\n");
    inputMatrix(A, r, c);
    printf("\nEnter Matrix B:\n");
    inputMatrix(B, r, c);

    // Subtraction
    for (i = 0; i < r; i++) {
        for (j = 0; j < c; j++) {
            C[i][j] = A[i][j] - B[i][j];
        }
    }

    printf("\nMatrix A:\n");
    printMatrix(A, r, c);
    printf("\nMatrix B:\n");
    printMatrix(B, r, c);
    printf("\nA - B = \n");
    printMatrix(C, r, c);
}

void multiplyMatrices() {
    int r1, c1, r2, c2;
    int A[MAX][MAX], B[MAX][MAX], C[MAX][MAX];
    int i, j, k;

    printf("\n--- Matrix Multiplication (A x B) ---\n");
    printf("Enter rows and columns of Matrix A: ");
    scanf("%d %d", &r1, &c1);
    printf("Enter rows and columns of Matrix B: ");
    scanf("%d %d", &r2, &c2);

    if (r1 <= 0 || c1 <= 0 || r2 <= 0 || c2 <= 0 ||
        r1 > MAX || c1 > MAX || r2 > MAX || c2 > MAX) {
        printf("Invalid size(s)!\n");
        return;
    }

    if (c1 != r2) {
        printf("Matrix multiplication not possible! (c1 must equal r2)\n");
        return;
    }

    printf("\nEnter Matrix A:\n");
    inputMatrix(A, r1, c1);
    printf("\nEnter Matrix B:\n");
    inputMatrix(B, r2, c2);

    // Initialize result matrix C with 0
    for (i = 0; i < r1; i++) {
        for (j = 0; j < c2; j++) {
            C[i][j] = 0;
        }
    }

    // Multiplication
    for (i = 0; i < r1; i++) {
        for (j = 0; j < c2; j++) {
            for (k = 0; k < c1; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    printf("\nMatrix A:\n");
    printMatrix(A, r1, c1);
    printf("\nMatrix B:\n");
    printMatrix(B, r2, c2);
    printf("\nA x B = \n");
    printMatrix(C, r1, c2);
}

void transposeMatrix() {
    int r, c;
    int A[MAX][MAX], T[MAX][MAX];
    int i, j;

    printf("\n--- Transpose of a Matrix ---\n");
    printf("Enter number of rows and columns: ");
    scanf("%d %d", &r, &c);

    if (r <= 0 || c <= 0 || r > MAX || c > MAX) {
        printf("Invalid size!\n");
        return;
    }

    printf("\nEnter Matrix A:\n");
    inputMatrix(A, r, c);

    // Transpose logic
    for (i = 0; i < r; i++) {
        for (j = 0; j < c; j++) {
            T[j][i] = A[i][j];  // swapped indices
        }
    }

    printf("\nOriginal Matrix A:\n");
    printMatrix(A, r, c);
    printf("\nTranspose of A:\n");
    printMatrix(T, c, r);  // rows and columns swapped
}
