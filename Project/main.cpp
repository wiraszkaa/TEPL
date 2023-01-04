#include <chrono>
#include "CKnapsackProblem.h"
#include "CGeneticAlgorithm.h"

int main() {
    CKnapsackProblem cKnapsackProblem;
    cKnapsackProblem.loadFromFile("../Project/problem_files/knapsack2.txt");
    cKnapsackProblem.print();

    CGeneticAlgorithm cGeneticAlgorithm(100000, 10, 0.2, 0.5);

    auto begin = std::chrono::steady_clock::now();
    cGeneticAlgorithm.start(cKnapsackProblem);
    auto now = std::chrono::steady_clock::now();

    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - begin);
    cGeneticAlgorithm.print();
    std::cout << "Execution took " << elapsed .count() << " milliseconds" << std::endl;

    return 0;
}
