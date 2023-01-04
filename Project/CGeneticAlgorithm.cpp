#include <random>
#include "CGeneticAlgorithm.h"

CGeneticAlgorithm::CGeneticAlgorithm() {
    iterations = 4;
    populationSize = 4;
    mutChance = 0.1;
    crossChance = 0.6;
}

CGeneticAlgorithm::~CGeneticAlgorithm() {
    individuals.clear();
}

CGeneticAlgorithm::CGeneticAlgorithm(int iIterations, int iPopulationSize, float fMutChance, float fCrossChance) {
    iterations = iIterations;
    populationSize = iPopulationSize;
    mutChance = fMutChance;
    crossChance = fCrossChance;
}

void CGeneticAlgorithm::createPopulation(int gcLength) {
    std::default_random_engine generator(rd());
    std::uniform_int_distribution<int> random(0, 10);
    for (int i = 0; i < populationSize; i++) {
        std::vector<bool> geneticCode;
        for (int j = 0; j < gcLength; j++) {
            if (random(generator) <= 5) {
                geneticCode.push_back(true);
            } else {
                geneticCode.push_back(false);
            }
        }
        individuals.push_back(new CIndividual(geneticCode, gcLength));
    }

    best = individuals[0];
}

int CGeneticAlgorithm::chooseRandomIndividual(int skipped) {
    std::default_random_engine generator(rd());
    std::uniform_int_distribution<int> random(0, populationSize - 1);
    int fIndex = random(generator);
    while (fIndex == skipped) {
        fIndex = random(generator);
    }

    int sIndex = random(generator);
    while (sIndex == fIndex || sIndex == skipped) {
        sIndex = random(generator);
    }

    if (individuals[fIndex]->getQuality() < individuals[sIndex]->getQuality()) {
        return sIndex;
    }

    return fIndex;
}

void CGeneticAlgorithm::crossPopulation() {
    std::vector<CIndividual*> nextPopulation;
    for (int i = 0; i < populationSize; i += 2) {
        int fIndex = chooseRandomIndividual(-1);
        int sIndex = chooseRandomIndividual(fIndex);

        individuals[fIndex]->cross(*individuals[sIndex], crossChance, nextPopulation);
    }
    individuals = nextPopulation;
}

void CGeneticAlgorithm::mutatePopulation() {
    for (int i = 0; i < populationSize; i++) {
        individuals[i]->mutate(mutChance);
    }
}

void CGeneticAlgorithm::setPopulationQuality(CKnapsackProblem &cKnapsackProblem) {
    for (int i = 0; i < populationSize; i++) {
        CIndividual *individual = individuals[i];
        float quality = cKnapsackProblem.evaluate(individual->getGeneticCode());
        individual->setQuality(quality);
//        individual->print();
//        std::cout << "Quality: " << quality << std::endl;

        if (quality > best->getQuality()) {
            best = individual;
        }
    }
}

void CGeneticAlgorithm::start(CKnapsackProblem &cKnapsackProblem) {
//    std::cout << "\nIteration 0\n" << std::endl;
    createPopulation(cKnapsackProblem.getItemsNumber());
    setPopulationQuality(cKnapsackProblem);
    for (int i = 0; i < iterations; i++) {
//        std::cout << "\nIteration " << i + 1 << "\n\n";
        crossPopulation();
        mutatePopulation();
        setPopulationQuality(cKnapsackProblem);
    }
    std::cout << "Best Result: " << best->getQuality() << " GC: ";
    best->print();
}

void CGeneticAlgorithm::print() {
    std::cout << "Iterations: " << iterations << "\nPopulation: " << populationSize << std::endl;
    std::cout << "Mutation: " << mutChance << "\nCross: " << crossChance << std::endl;
}
