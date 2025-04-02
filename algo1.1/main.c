#include <stdio.h>

#define ERROR 0.000001

enum ProgramStatus
{
    DONE,
    ERROR_OCCURRED,
};

enum PointPosition
{
    ABOVE_LINE,
    UNDER_LINE,
    ON_LINE
};

enum InputStatus
{
    INCORRECT_INPUT,
    CORRECT_INPUT = 2
};

void printResult(enum PointPosition state);
enum InputStatus readCoordinates(float *x, float *y);
enum PointPosition findLocation(float x, float y);
float function(float x);

int main() {
    float x, y;
    enum PointPosition state;
    if (readCoordinates(&x, &y) == CORRECT_INPUT) {
        state = findLocation(x, y);
        printResult(state);;
        return DONE;
    }
    else return ERROR_OCCURRED;
}

enum InputStatus readCoordinates(float* x, float* y) {
    int input = CORRECT_INPUT;
    if (scanf("%f %f", x, y) != CORRECT_INPUT ) {
        printf("Incorrect input");
        input = INCORRECT_INPUT;
    }
    return input;
}

float function(float x) {
    return 0.5 * x + 1;
}

enum PointPosition findLocation(float x, float y) {
    enum PointPosition state = ON_LINE;
    if (function(x) + ERROR < y)
        state = ABOVE_LINE;
    else if (function(x) - ERROR > y)
        state = UNDER_LINE;
    return state;
}

void printResult(enum PointPosition state){
    switch(state) {
    case ABOVE_LINE:
        printf("Point is above the line");
        break;
    case UNDER_LINE:
        printf("Point is under the line");
        break;
    case ON_LINE:
        printf("Point is on the line");
        break;
    }
}
