#include <random>
#include "CGeneticAlgorithm.h"

CGeneticAlgorithm::CGeneticAlgorithm() {
    iterations = 4;
    populationSize = 4;
    mutChance = 0.1;
    crossChance = 0.6;
}

CGeneticAlgorithm::CGeneticAlgorithm(int iIterations, int iPopulationSize, float fMutChance, float fCrossChance) {
    iterations = iIterations;
    populationSize = iPopulationSize;
    mutChance = fMutChance;
    crossChance = fCrossChance;
}

void CGeneticAlgorithm::createPopulation(int gcLength) {
    std::uniform_int_distribution<int> random(0, 100);
    for (int i = 0; i < populationSize; i++) {
        std::vector<bool> cGeneticCode;
        for (int j = 0; j < gcLength; j++) {
            if (random(generator) <= 50) {
                cGeneticCode.push_back(true);
            } else {
                cGeneticCode.push_back(false);
            }
        }
        individuals[i] = new CIndividual(cGeneticCode, gcLength);
    }
}

CIndividual *CGeneticAlgorithm::chooseRandomIndividual() {
    CIndividual * result;
    std::uniform_int_distribution<int> random(0, populationSize - 1);
    int fIndex = random(generator);
    result = individuals[fIndex];

    int sIndex = random(generator);
    while (sIndex == fIndex) {
        sIndex = random(generator);
    }

    if (result->getQuality() < individuals[sIndex]->getQuality()) {
        return individuals[sIndex];
    }

    return result;
}

void CGeneticAlgorithm::crossPopulation() {
    CIndividual * person1 = chooseRandomIndividual();
    CIndividual * person2 = chooseRandomIndividual();
    std::vector<CIndividual *> children = person1->cross(*person2);
    individuals[0] = children[0];
    individuals[1] = children[1];
}

void CGeneticAlgorithm::mutatePopulation() {
    for (int i = 0; i < populationSize; i++) {
        individuals[i]->mutate(mutChance);
    }
}

void CGeneticAlgorithm::setPopulationQuality(CKnapsackProblem & cKnapsackProblem) {
    for (int i = 0; i < populationSize; i++) {
        float quality = cKnapsackProblem.evaluate(individuals[i]->getGeneticCode());
        individuals[i]->setQuality(quality);
        std::cout << "Quality: " << quality << std::endl;
    }
}

void CGeneticAlgorithm::start(CKnapsackProblem & cKnapsackProblem) {
    std::cout << "Iteration 0\n" << std::endl;
    createPopulation(cKnapsackProblem.getItemsNumber());
    setPopulationQuality(cKnapsackProblem);
    for (int i = 0; i < iterations; i++) {
        std::cout << "\nIteration " << i + 1 << "\n\n";
        crossPopulation();
        mutatePopulation();
        setPopulationQuality(cKnapsackProblem);
    }
}