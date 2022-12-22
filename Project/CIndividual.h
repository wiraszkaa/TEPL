#pragma once
#include <iostream>
#include <vector>
#include <random>


class CIndividual {
public:
    CIndividual();
    CIndividual(std::vector<bool> cGeneticCode, int iLength);
    void setQuality(float fQuality);
    void mutate(float chance);
    float getQuality();
    std::vector<bool>& getGeneticCode();
    std::vector<CIndividual*> cross(CIndividual & pcOther);
private:
  std::vector<bool> geneticCode;
  int length;
  float quality;
  std::default_random_engine generator;
};
