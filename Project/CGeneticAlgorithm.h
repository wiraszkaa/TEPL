#pragma once
#include <iostream>
#include <random>
#include "CIndividual.h"
#include "CKnapsackProblem.h"

class CGeneticAlgorithm {
public:
    CGeneticAlgorithm();
    CGeneticAlgorithm(int iIterations, int iPopulationSize, float fMutChance, float fCrossChance);

    void start(CKnapsackProblem & cKnapsackProblem);
private:
    int iterations;
    int populationSize;
    float mutChance;
    float crossChance;
    CIndividual** individuals;
    std::default_random_engine generator;

    void createPopulation(int gcLength);
    CIndividual* chooseRandomIndividual();
    void crossPopulation();
    void mutatePopulation();
    void setPopulationQuality(CKnapsackProblem & cKnapsackProblem);
};
