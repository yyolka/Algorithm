#include <stdio.h>
#include <stdlib.h>

#define CORRECT_INPUT 2

enum ProgramStatus {
    DONE,
    ERROR
};

int inputSize(int* sizeX, int* sizeY);
int checkConditionSize(int sizeX, int sizeY);
int checkZeroSize(int sizeX, int sizeY);
void transform(int** mat, int* vec, int sizeX, int sizeY);
int** allocateMatrix(int sizeX, int sizeY);
int inputMatrix(int** mat, int sizeX, int sizeY);
void outputMatrix(int** mat, int sizeX, int sizeY);
void freeMatrix(int** mat);
void printError();
void swap(int* a, int* b);
int* findPointerOfMax(int** mat, int sizeX, int sizeY);
int* findPointerOfMin(int** mat, int sizeX, int sizeY);

int main(){
    int sizeX, sizeY;
    enum ProgramStatus state = ERROR;
    if (inputSize(&sizeX, &sizeY) && checkConditionSize(sizeX, sizeY)) {
        if (checkZeroSize(sizeX, sizeY))
            state=DONE;
        else {
            int** mat = allocateMatrix(sizeX, sizeY);
            if (mat != NULL && inputMatrix(mat, sizeX, sizeY)) {
                state = DONE;
                int* max = findPointerOfMax(mat, sizeX, sizeY);
                int* min = findPointerOfMin(mat, sizeX, sizeY);
                swap(max, min);
                outputMatrix(mat, sizeX, sizeY);
                freeMatrix(mat);
            }
            else if (mat != NULL) {
                printError();
                freeMatrix(mat);
            }
            else
                printError();
        }
    }
    else
        printError();
    return state;
}

int inputSize(int* sizeX, int* sizeY) {
    return scanf("%d %d", sizeY, sizeX) == CORRECT_INPUT;
}

int checkConditionSize(int sizeX, int sizeY) {
    return (sizeX >= 0 && sizeY >= 0);
}

int checkZeroSize(int sizeX, int sizeY) {
    return (sizeX == 0 || sizeY == 0);
}

void transform(int** mat, int* vec, int sizeX, int sizeY) {
    for (int i = 0; i < sizeY; i++) {
        mat[i] = vec + i * sizeX;
    }
}

int** allocateMatrix(int sizeX, int sizeY)
{
    int** mat = (int**) malloc(sizeof(int*) * sizeY);
    int* vec = NULL;
    if(mat != NULL) {
        vec = (int*) malloc(sizeof(int) * sizeX * sizeY);
        if (vec == NULL) {
            free(mat);
            mat = NULL;
        }
    }
    if (mat != NULL && vec != NULL)
        transform(mat, vec, sizeX, sizeY);
    return mat;
}


int inputMatrix(int** mat, int sizeX, int sizeY) {
    int readValues = 0;
    for (int i = 0; i < sizeY; i++)
        for (int j = 0; j < sizeX; j++) {
            readValues += scanf("%d", mat[i] + j);
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

int* findPointerOfMax(int** mat, int sizeX, int sizeY) {
    int* pointerMax = mat[0];
    for (int i = 0; i < sizeY ; i++)
        for (int j = 0; j < sizeX; j++) {
            if (i + j < sizeY - 1 && (*(mat[i] + j) > *pointerMax))
                pointerMax = mat[i] + j;
        }
    return pointerMax;
}

int* findPointerOfMin(int** mat, int sizeX, int sizeY) {
    int* pointerMin = mat[sizeY - 1] + (sizeX - 1);
    for (int i = 0; i < sizeY; i++)
        for (int j = 0; j < sizeX ; j++) {
            if (i + j > sizeY - 1 && (*(mat[i] + j) <= *pointerMin))
                pointerMin = mat[i] + j;
        }
    return pointerMin;
}

