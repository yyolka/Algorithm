#include <stdio.h>
#include <stdlib.h>

#define CORRECT_INPUT 1

enum ProgramStatus {
    DONE,
    ERROR
};

int inputSize(int* size);
int checkConditionSize(int size);
void transform(int** mat, int* vec, int size);
int** allocateMatrix(int size);
int inputMatrix(int** mat, int size);
void outputMatrix(int** mat, int size);
void freeMatrix(int** mat);
void printError();
void swap(int* a, int* b);
void transposeAboutSecondaryAxis(int** mat, int size);

int main(){
    int size;
    enum ProgramStatus state = ERROR;
    if (inputSize(&size) && checkConditionSize(size)) {
        int** mat = allocateMatrix(size);
        if (mat != NULL && inputMatrix(mat, size)) {
            state = DONE;
            transposeAboutSecondaryAxis(mat, size);
            outputMatrix(mat, size);
            freeMatrix(mat);
        }
        else if (mat != NULL) {
            printError();
            freeMatrix(mat);
        }
        else
            printError();
    }
    else
        printError();
    return state;
}

int inputSize(int* size) {
    return scanf("%d", size) == CORRECT_INPUT;
}

int checkConditionSize(int size) {
    return size >= 0;
}

void transform(int** mat, int* vec, int size) {
    for (int i = 0; i < size; i++) {
        mat[i] = vec + i * size;
    }
}

int** allocateMatrix(int size) {
    int **mat = (int **)calloc(size, sizeof(int*));
    int *vec = (int *)calloc(size * size, sizeof(int));
    transform(mat, vec, size);
    return mat;
}

int inputMatrix(int** mat, int size) {
    int readValues = 0;
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++) {
            readValues += scanf("%d", mat[i] + j);
        }
    return size * size == readValues;
}

void outputMatrix(int** mat, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            printf("%d ", mat[i][j]);
        }
        printf("\n");
    }
}

void freeMatrix(int** mat) {
    free(*mat);
    free(mat);
}

void printError() {
    printf("Incorrect input");
}

void transposeAboutSecondaryAxis(int** mat, int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            swap(mat[i] + j, mat[size - j - 1] + size - i - 1);
        }
    }
}

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}
