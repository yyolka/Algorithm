#include <stdio.h>
#include <stdlib.h>

#define CORRECT_INPUT 1

enum ProgramStatus {
    DONE,
    ERROR
};

int inputSize(int* size);
int checkConditionSize(int size);
void swap(int* pa, int* pb);
int inputArray(int size, int* arr);
int* createArray(int size);
void printError();
void outputArray(int* arr, int size);
void sort(int* arr, int size);
void moveNegativeToEnd(int* arr, int size, int i);
int findIndexOfFirstNonNegative(int* arr, int size);

int main() {
    int size;
    enum ProgramStatus state = ERROR;
    if (inputSize(&size) && checkConditionSize(size)) {
        int* arr = createArray(size);
        if (arr != NULL) {
            if (inputArray(size, arr)) {
                state = DONE;
                sort(arr, size);
                int indexOfFirstNonNegative = findIndexOfFirstNonNegative(arr, size);
                if (indexOfFirstNonNegative < size && indexOfFirstNonNegative > 0) {
                    moveNegativeToEnd(arr, size, indexOfFirstNonNegative);
                }
                outputArray(arr, size);
                free(arr);
            }
            else {
                printError();
                free(arr);
            }
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

    int checkConditionSize(int size)
    {
        return size >= 0;
    }

    void swap(int* pa, int* pb) {
        int temp = *pa;
        *pa = *pb;
        *pb = temp;
    }

    int inputArray(int size, int* arr) {
        int readValues = 0;
        for (int i = 0; i < size; i++)
            if (scanf("%d", arr + i))
                readValues += 1;
            else
                break;
        return size == readValues;
    }

    int* createArray(int size) {
        return (int*) malloc(size * sizeof(int));
    }

    void printError() {
        printf("Incorrect input");
    }

    void outputArray(int* arr, int size) {
        for (int i = 0; i < size; i++) {
            printf("%d ", arr[i]);
        }
    }

    void sort(int* arr, int size) {
        for (int i = 0; i < size - 1; i++) {
            for (int j = 0; j < size - i - 1; j++) {
                if (arr[j] > arr[j + 1])
                    swap(arr + j, arr + j + 1);
            }
        }
    }

    int findIndexOfFirstNonNegative(int* arr, int size) {
        int indexOfFirstNonNegative = size;
        for (int i = 0; i < size; i++)
            if (arr[i] >= 0) {
                indexOfFirstNonNegative = i;
                break;
            }
        return indexOfFirstNonNegative;
    }

    void moveNegativeToEnd(int* arr, int size, int i) {
        int temp[i];
        for (int j = 0; j < i; j++) {
            temp[j] = arr[j];
        }
        for (int j = i, k = 0; j < size; j++, k++) {
            arr[k] = arr[j];
        }
        for (int k = 0; k < i; k++) {
            arr[size - i + k] = temp[k];
        }
    }
