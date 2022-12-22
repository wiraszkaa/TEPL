#include "CKnapsackProblem.h"
#include "CGeneticAlgorithm.h"
#include <iostream>

int main() {
    CKnapsackProblem cKnapsackProblem(4, 5);
    cKnapsackProblem.setItem(0, 5, 4);
    cKnapsackProblem.setItem(1, 1, 1);
    cKnapsackProblem.setItem(2, 4, 3);
    cKnapsackProblem.setItem(3, 3, 2);
    cKnapsackProblem.print();

    CGeneticAlgorithm cGeneticAlgorithm;
    cGeneticAlgorithm.start(cKnapsackProblem);

    return 0;
}
