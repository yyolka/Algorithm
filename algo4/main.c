#include <stdio.h>
#include <stdlib.h>

enum Status {
    DONE,
    ERROR
};

int checkTheCondition(int arrayLen);
int* memoryAllocation(int size);
int inputArray(int* arr, int arrayLen);
int inputArrayLen(int* arrayLen);
int findMinElem(int* arr, int arrayLen);
int findIndexOfMaxElem(int* arr, int arrayLen);
int calculateSum(int *arr, int arrayLen, float sumOfMaxMin, int indexOfMaxElem);
void printResult(int sum);
void printError();

int main() {
    int arrayLen;
    int* arr = NULL;
    enum Status state = ERROR;
    if (inputArrayLen(&arrayLen) && checkTheCondition(arrayLen)) {
        arr = memoryAllocation(arrayLen);
        if (arr != NULL && inputArray(arr, arrayLen)) {
            state = DONE;
            int indexOfMaxElem = findIndexOfMaxElem(arr, arrayLen);
            float sumOfMaxMin = (arr[indexOfMaxElem] + findMinElem(arr, arrayLen)) / 2;
            if (indexOfMaxElem < arrayLen - 1) {
                int sum = calculateSum(arr, arrayLen, sumOfMaxMin, indexOfMaxElem);
                printResult(sum);
            }
            else
                printf("0");
            free(arr);
        }
        else if (arr != NULL) {
            free(arr);
            printError();
        }
        else
            printError();
    }
    else
        printError();
    return state;
}

int* memoryAllocation(int size) {
    return malloc(sizeof(int) * size);
}

int inputArray(int* arr, int arrayLen) {
    int readValues = 0;
    for (int i = 0; i < arrayLen; i ++)
        readValues += scanf("%d", arr + i);
    return readValues == arrayLen;
}

int inputArrayLen(int* arrayLen) {
    return (scanf("%d", arrayLen));
}

int checkTheCondition(int arrayLen) {
    return arrayLen > 0;
}

int findMinElem(int* arr, int arrayLen) {
    int min = arr[0];
    for (int i = 1; i < arrayLen; i ++ ) {
        if (min > arr[i])
            min = arr[i];
    }
    return min;
}

int findIndexOfMaxElem(int* arr, int arrayLen) {
    int indexMax = 0;
    for (int i = 1; i < arrayLen; i ++) {
        if (arr[indexMax] < arr[i])
            indexMax = i;
    }
    return indexMax;
}

int calculateSum(int *arr, int arrayLen, float sumOfMaxMin, int indexOfMaxElem) {
    int sum = 0;
    for (int i = indexOfMaxElem + 1; i < arrayLen; i++) {
        if (arr[i] > sumOfMaxMin)
            sum += arr[i];
    }
    return sum;
}

void printResult(int sum) {
    printf("%d", sum);
}

void printError() {
    printf("Incorrect input");
}
