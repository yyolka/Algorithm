#include <stdio.h>
#include <math.h>

enum {
    CORRECT_INPUT = 3
};

enum ProgramStatus {
    DONE,
    ERROR
};

int readValues(double* a, double* b, double* errorRate);
double function(float x);
double simpsonIntegral (double a, double b, int n);
double calculateIntegral(double a, double b, double errorRate);
int checkTheCondition(double a, double b, double errorRate);
void printResult(double answer);
void printError();

int main() {
    double a, b, errorRate;
    enum ProgramStatus state = ERROR;
    if (readValues(&a, &b, &errorRate) && checkTheCondition(a, b, errorRate)) {
        double answer = calculateIntegral(a, b, errorRate);
        printResult(answer);
        state = DONE;
    }
    else
        printError();
    return state;
}

int readValues(double* a, double* b, double* errorRate) {
    return scanf("%lf%lf%lf", a, b, errorRate) == CORRECT_INPUT;
}

int checkTheCondition(double a, double b, double errorRate) {
    return errorRate > 0 && a > 0 && b > 0;
}

double function(float x) {
    return log(x);
}

double simpsonIntegral (double a, double b, int n) {
    double sum = function(a) + function(b);
    double sumOdd = 0;
    double sumEven = 0;
    double h = (b - a) / n;
    for (int i = 1; i <= n; i ++ ) {
        double x = a + i * h;
        if (i % 2 == 1)
            sumOdd += function(x);
        else
            sumEven += function(x);
    }
    sumOdd *= 4;
    sumEven *= 2;
    sum = sum + sumEven + sumOdd;
    return h / 3 * sum;
}

double calculateIntegral(double a, double b, double errorRate) {
    int n = 1;
    double previous = 0;
    double current = simpsonIntegral(a, b, n);
    do {
        previous = current;
        n *= 2;
        current = simpsonIntegral(a, b, n);
    }
    while (fabs(current - previous) >= errorRate);
    return current;
}

void printResult(double answer) {
    printf("%.6f", answer);
}

void printError() {
    printf("Incorrect input");
}

