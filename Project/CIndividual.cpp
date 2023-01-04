#include "CIndividual.h"
#include <random>
#include <utility>

CIndividual::CIndividual() {
    quality = 0;
}

CIndividual::~CIndividual() {
    geneticCode.clear();
}

CIndividual::CIndividual(std::vector<bool> cGeneticCode, int iLength) {
    quality = 0;
    geneticCode = std::move(cGeneticCode);
    length = iLength;
}

void CIndividual::setQuality(float fQuality) {
    quality = fQuality;
}

void CIndividual::mutate(float chance) {
    std::default_random_engine generator(rd());
    std::uniform_int_distribution<int> random(0.0, 1.0);
    for (int i = 0; i < length; i++) {
        if (random(generator) <= chance) geneticCode[i] = !geneticCode[i];
    }
}

void CIndividual::print() {
    for (int i = 0; i < length; i++) {
        std::string binary = "0";
        if (geneticCode[i]) binary = "1";
        std::cout << binary;
    }
    std::cout << std::endl;
}

float CIndividual::getQuality() {
    return quality;
}

std::vector<bool> & CIndividual::getGeneticCode() {
    return geneticCode;
}

void CIndividual::cross(CIndividual &pcOther, float chance, std::vector<CIndividual*>  &individuals) {
    std::default_random_engine generator(rd());
    std::uniform_int_distribution<int> random(0.0, 1.0);
    if (random(generator) > chance) {
        individuals.push_back(this);
        individuals.push_back(&pcOther);
    } else {
        int split = (random(generator) + 1) % (length - 2);
        std::vector<bool> gc1;
        std::vector<bool> gc2;
        for (int i = 0; i < length; i++) {
            if (i < split) {
                gc1.push_back(pcOther.geneticCode[i]);
                gc2.push_back(geneticCode[i]);
            } else {
                gc1.push_back(geneticCode[i]);
                gc2.push_back(pcOther.geneticCode[i]);
            }
        }
        individuals.push_back(new CIndividual(gc1, length));
        individuals.push_back(new CIndividual(gc2, length));
    }
}