#pragma once
#include <iostream>
#include <random>
#include "CIndividual.h"
#include "CKnapsackProblem.h"
#include <vector>

class CGeneticAlgorithm {
public:
    CGeneticAlgorithm();
    ~CGeneticAlgorithm();
    CGeneticAlgorithm(int iIterations, int iPopulationSize, float fMutChance, float fCrossChance);

    void start(CKnapsackProblem & cKnapsackProblem);
    void print();
private:
    int iterations;
    int populationSize;
    float mutChance;
    float crossChance;
    std::vector<CIndividual*> individuals;
    CIndividual* best;
    std::random_device rd;

    void createPopulation(int gcLength);
    int chooseRandomIndividual(int skipped);
    void crossPopulation();
    void mutatePopulation();
    void setPopulationQuality(CKnapsackProblem & cKnapsackProblem);
};
