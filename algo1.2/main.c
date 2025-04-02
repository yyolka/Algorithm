#include <stdio.h>

enum InputStatus
{
    INCORRECT_INPUT,
    CORRECT_INPUT = 2
};

enum ProgramStatus
{
    DONE,
    ERROR_OCCURRED
};

enum PointPosition
{
    ABOVE_LINE,
    UNDER_LINE,
    ON_LINE
};

enum PointLocation
{
    REGION0,
    REGION1,
    REGION2,
    REGION3,
    REGION4,
    REGION5,
    REGION6,
    REGION7,
    LINE1 = 10,
    LINE2 = 20,
    LINE3 = 30,
    LINES12 = 12,
    LINES13 = 13,
    LINES23 = 23,
};

enum TypeOfLocation
{
    LINE,
    LINES,
    REGION
};

enum InputStatus readCoordinates(float *x, float *y);
float function1(float x);
float function2(float x);
float function3(float x);
enum PointPosition findGraph1(float x, float y);
enum PointPosition findGraph2(float x, float y);
enum PointPosition findGraph3(float x, float y);
enum TypeOfLocation identifyLocation(float x, float y);
enum PointLocation findPosition(float x, float y, enum TypeOfLocation class);
enum PointLocation findLinePosition(float x, float y);
enum PointLocation findLinesPosition(float x, float y);
enum PointLocation findRegionPosition(float x, float y);
void printRegionResult(enum PointLocation position);
void printLineResult(enum PointLocation position);
void printLinesResult(enum PointLocation position);
void printResult(enum TypeOfLocation class, enum PointLocation position);

int main() {
    float x, y;
    enum TypeOfLocation class;
    enum PointLocation position;
    if (readCoordinates(&x, &y) == CORRECT_INPUT) {
        class = identifyLocation(x, y);
        position = findPosition(x, y, class);
        printResult(class, position);
        return DONE;
    }
    else return ERROR_OCCURRED;
}

enum InputStatus readCoordinates(float *x, float *y) {
    enum InputStatus input = CORRECT_INPUT;
    if (scanf("%f %f", x, y) != CORRECT_INPUT) {
        printf("Incorrect input");
        input = INCORRECT_INPUT;
    }
    return input;
}

float function1(float x) {
    return 2 * x + 2;
}

float function2(float x) {
    return 0.5 * x - 1;
}

float function3(float x) {
    return - x + 2;
}

enum PointPosition findGraph1(float x, float y) {
    enum PointPosition state = ON_LINE;
    if (function1(x) < y)
        state = ABOVE_LINE;
    else if (function1(x) > y)
        state = UNDER_LINE;
    return state;
}

enum PointPosition findGraph3(float x, float y) {
    enum PointPosition state = ON_LINE;
    if (function3(x) < y)
        state = ABOVE_LINE;
    else if (function3(x) > y)
        state = UNDER_LINE;
    return state;
}

enum PointPosition findGraph2(float x, float y) {
    enum PointPosition state = ON_LINE;
    if (function2(x) < y)
        state = ABOVE_LINE;
    else if (function2(x) > y)
        state = UNDER_LINE;
    return state;
}

enum TypeOfLocation identifyLocation(float x, float y) {
    enum TypeOfLocation class = REGION;
    if (findGraph1(x, y) == ON_LINE && findGraph2(x, y) == ON_LINE)
        class = LINES;
    else if (findGraph1(x, y) == ON_LINE && findGraph3(x, y) == ON_LINE)
        class = LINES;
    else if (findGraph2(x, y) == ON_LINE && findGraph3(x, y) == ON_LINE)
        class = LINES;
    else if (findGraph1(x, y) == ON_LINE || findGraph2(x, y) == ON_LINE || findGraph3(x, y) == ON_LINE)
        class = LINE;
    return class;
}

enum PointLocation findPosition(float x, float y, enum TypeOfLocation class) {
    enum PointLocation position;
    switch(class) {
    case LINE:
        position = findLinePosition(x, y);
        break;
    case REGION:
        position = findRegionPosition(x, y);
        break;
    case LINES:
        position = findLinesPosition(x, y);
        break;
    }
    return position;
}

enum PointLocation findLinesPosition(float x, float y) {
    enum PointLocation position = LINES23;
    if (findGraph1(x, y) == ON_LINE && findGraph2(x, y) == ON_LINE)
        position = LINES12;
    else if (findGraph1(x, y) == ON_LINE && findGraph3(x, y) == ON_LINE)
        position = LINES13;
    return position;
}

enum PointLocation findLinePosition(float x, float y) {
    enum PointLocation position = LINE3;
    if (findGraph1(x, y) == ON_LINE)
        position = LINE1;
    else if (findGraph2(x, y) == ON_LINE)
        position = LINE2;
    return position;
}

enum PointLocation findRegionPosition(float x, float y) {
    enum PointLocation position = REGION7;
    if (findGraph1(x, y) == UNDER_LINE && findGraph2(x, y) == ABOVE_LINE && findGraph3(x, y) == ABOVE_LINE)
        position = REGION1;
    else if (findGraph1(x, y) == UNDER_LINE && findGraph2(x, y) == UNDER_LINE && findGraph3(x, y) == ABOVE_LINE)
        position = REGION2;
    else if (findGraph1(x, y) == UNDER_LINE && findGraph2(x, y) == UNDER_LINE && findGraph3(x, y) == UNDER_LINE)
        position = REGION3;
    else if (findGraph1(x, y) == ABOVE_LINE && findGraph2(x, y) == UNDER_LINE && findGraph3(x, y) == UNDER_LINE)
        position = REGION4;
    else if (findGraph1(x, y) == ABOVE_LINE && findGraph2(x, y) == ABOVE_LINE && findGraph3(x, y) == UNDER_LINE)
        position = REGION5;
    else if (findGraph1(x, y) == ABOVE_LINE && findGraph2(x, y) == ABOVE_LINE && findGraph3(x, y) == ABOVE_LINE)
        position = REGION6;
    return position;
}

void printResult(enum TypeOfLocation class, enum PointLocation position) {
    switch(class){
    case LINE:
        printLineResult(position);
        break;
    case REGION:
        printRegionResult(position);
        break;
    case LINES:
        printLinesResult(position);
        break;
    }
}

void printRegionResult(enum PointLocation position) {
    printf("Point is placed in region %d", position);
}

void printLinesResult(enum PointLocation position) {
    printf("Point placed on lines %d and %d", position / 10, position % 10);
}

void printLineResult(enum PointLocation position) {
    printf("Point placed on line %d", position / 10);
}

