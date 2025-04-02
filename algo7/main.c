#include <stdio.h>
#include <stdlib.h>

#define CORRECT_INPUT 2

enum ProgramStatus {
    DONE,
    ERROR
};

int inputSize(int* sizeX, int* sizeY);
int checkConditionSize(int sizeX, int sizeY);
void transform(int** mat, int* vec, int sizeX, int sizeY);
int** allocateMatrix(int sizeX, int sizeY);
int inputMatrix(int** mat, int sizeX, int sizeY);
void outputMatrix(int** mat, int sizeX, int sizeY);
void freeMatrix(int** mat);
void printError();
void swap(int* a, int* b);
void sortRowDecrease(int** mat, int sizeX, int row);
void sortArray(int* vec, int size);
void sortRows(int** mat, int sizeX, int sizeY);

int main(){
    int sizeX, sizeY;
    enum ProgramStatus state = ERROR;
    if (inputSize(&sizeX, &sizeY) && checkConditionSize(sizeX, sizeY)) {
        int** mat = allocateMatrix(sizeX, sizeY);
        if (mat != NULL) {
            if (inputMatrix(mat, sizeX, sizeY)) {
                state = DONE;
                sortArray(*mat, sizeX * sizeY);
                sortRows(mat, sizeX, sizeY);
                outputMatrix(mat, sizeX, sizeY);
            }
            else
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

int inputSize(int* sizeX, int* sizeY) {
    return scanf("%d %d", sizeY, sizeX) == CORRECT_INPUT;
}

int checkConditionSize(int sizeX, int sizeY) {
    return (sizeX > 0 && sizeY > 0);
}

void transform(int** mat, int* vec, int sizeX, int sizeY) {
    for (int i = 0; i < sizeY; i++) {
        mat[i] = vec + i * sizeX;
    }
}

int** allocateMatrix(int sizeX, int sizeY) {
    int** mat = (int**) malloc(sizeof(int*) * sizeY);
    int* vec = NULL;
    if (mat != NULL) {
        vec = (int*) malloc(sizeof(int) * sizeX * sizeY);
        if (vec == NULL) {
            free(mat);
            mat = NULL;
        }
        else
            transform(mat, vec, sizeX, sizeY);
    }
    return mat;
}


int inputMatrix(int** mat, int sizeX, int sizeY) {
    int readValues = 0;
    for (int i = 0; i < sizeY; i++)
        for (int j = 0; j < sizeX; j++) {
            if (scanf("%d", mat[i] + j)) {
                readValues += 1;
            }
            else
                break;
        }
    return sizeX * sizeY == readValues;
}

void outputMatrix(int** mat, int sizeX, int sizeY) {
    for (int i = 0; i < sizeY; i++) {
        for (int j = 0; j < sizeX; j++) {
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

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void sortArray(int* vec, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (vec[j] < vec[j + 1])
                swap(vec + j, vec + j + 1);
        }
    }
}

void sortRowDecrease(int** mat, int sizeX, int row) {
    for (int i = 0; i < sizeX / 2; i++) {
        swap(mat[row] + i, mat[row] + sizeX - i - 1);
    }
}

void sortRows(int** mat, int sizeX, int sizeY) {
    for (int i = sizeY - 2; i >= 0; i -=2) {
        sortRowDecrease(mat, sizeX, i);
    }
}
