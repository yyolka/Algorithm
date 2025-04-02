#include <stdio.h>
#include <math.h>

enum ProgramStatus {
    DONE,
    ERROR
};

int readValue(float* errorRate);
int checkCondition(float errorRate);
float calculateSum(float errorRate);
float calculateValue(float n, float factorialN);
void printResult(float sum);

int main() {
    float errorRate;
    enum ProgramStatus state = ERROR;
    if (readValue(&errorRate) && checkCondition(errorRate)) {
        float sum = calculateSum(errorRate);
        printResult(sum);
        state = DONE;
    }
    return state;
}

int readValue(float* errorRate) {
    return scanf("%f", errorRate);
}

int checkCondition(float errorRate) {
    return errorRate > 0;
}

float calculateSum(float errorRate) {
    float sum = 1;
    float factorialN = 1;
    for (int n = 1; fabs(calculateValue(n, factorialN)) > errorRate; n++ ) {
        factorialN *= n;
        sum += calculateValue(n, factorialN);
    }
    return sum;
}

float calculateValue(float n, float factorialN) {
    float result;
    if (n == 0)
        result = 1;
    else 
        result = pow(-1, n) / factorialN;
    return result;
}

void printResult(float sum) {
    printf("%.6f", sum);
}

