#include <stdio.h>
#include <math.h>

enum Status {
    DONE,
    ERROR,
    MIN_NUMBER,
    CORRECT_INPUT
};

enum Status readValues(float* left, float* right, int* number);
float calculateInterval(float left, float right, int number);
float function(float x);
void countCycleFor(float left, float right, float step);
void countCycleWhile(float left, float right, float step);
void countCycleDoWhile(float left, float right, float step);
void printFunction(float x);
void printX(float x);

int main() {
    float left, right;
    int number;
    enum Status state = ERROR;
    if (readValues(&left, &right, &number) == CORRECT_INPUT) {
        float step = calculateInterval(left, right,  number);
        countCycleFor(left, right, step);
        countCycleWhile(left, right, step);
        countCycleDoWhile(left, right, step);
        state = DONE;
    }
    return state;
}

enum Status readValues(float* left, float* right, int* number) {
    enum Status state = CORRECT_INPUT;
    if (scanf("%f %f %d", left, right, number) != CORRECT_INPUT || *left >= *right || *number < MIN_NUMBER) {
        printf("Incorrect input");
        state = ERROR;
    }
    return state;
}

float calculateInterval(float left, float right, int number) {
    return (right - left) / (number - 1);
}

float function(float x) {
    return (sin(x) * sin(x)) / x;
}

void countCycleFor(float left, float right, float step) {
    printf("for:\nx    ");
    for (float i = left; i <= right; i += step) {
        printX(i);
    }
    printf("|\nf(x) ");
    for (float i = left; i <= right; i += step) {
        printFunction(i);
    }
    printf("|\n\n");
}

void countCycleWhile(float left, float right, float step) {
    printf("while:\nx    ");
    float i = left;
    while (left <= right) {
        printX(left);
        left += step;
    }
    printf("|\nf(x) ");
    while (i <= right) {
        printFunction(i);
        i += step;
    }
    printf("|\n\n");
}

void countCycleDoWhile(float left, float right, float step) {
    printf("do while:\nx    ");
    float i = left;
    do {
        printX(left);
        left += step;
    }
    while (left < right);
    printX(left);
    printf("|\nf(x) ");
    do {
        printFunction(i);
        i += step;
    }
    while (i <= right);
    printf("|\n");
}

void printFunction(float x) {
    if (isnan(function(x)) == 0 )
        printf("|%6.3f ", function(x));
    else
        printf("|  nan  ");
}

void printX(float x) {
    printf("|%6.3f ", x);
}
