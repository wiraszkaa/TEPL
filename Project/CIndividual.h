#pragma once
#include <iostream>
#include <vector>
#include <random>


class CIndividual {
public:
    CIndividual();
    ~CIndividual();
    CIndividual(std::vector<bool> cGeneticCode, int iLength);
    void setQuality(float fQuality);
    void mutate(float chance);
    void print();
    float getQuality();
    std::vector<bool>& getGeneticCode();
    void cross(CIndividual & pcOther, float chance, std::vector<CIndividual*>  &individuals);

private:
  std::vector<bool> geneticCode;
  int length;
  float quality;
  std::random_device rd;
};
