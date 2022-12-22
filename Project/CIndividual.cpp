#include "CIndividual.h"
#include <random>

CIndividual::CIndividual() {
    quality = 0;
}

CIndividual::CIndividual(std::vector<bool> cGeneticCode, int iLength) {
    quality = 0;
    geneticCode = cGeneticCode;
    length = iLength;
}

void CIndividual::setQuality(float fQuality) {
    quality = fQuality;
}

void CIndividual::mutate(float chance) {
    std::uniform_int_distribution<int> random(0, 100);
    for (int i = 0; i < length; i++) {
        if (random(generator) <= chance * 100.0) geneticCode[i] = !geneticCode[i];
    }
}

float CIndividual::getQuality() {
    return quality;
}

std::vector<bool> & CIndividual::getGeneticCode() {
    return geneticCode;
}

std::vector<CIndividual*> CIndividual::cross(CIndividual &pcOther) {
    std::uniform_int_distribution<int> random(1, length - 1);
    int split = random(generator);
    std::vector<bool> gc1;
    std::vector<bool> gc2;
    for(int i = 0; i < length; i++) {
        if (i < split) {
            gc1.push_back(pcOther.geneticCode[i]);
            gc2.push_back(geneticCode[i]);
        } else {
            gc1.push_back(geneticCode[i]);
            gc2.push_back(pcOther.geneticCode[i]);
        }
    }
    std::vector<CIndividual*> result;
    result.push_back(new CIndividual(gc1, length));
    result.push_back(new CIndividual(gc2, length));
    return result;
}

