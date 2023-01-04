#pragma once
#include <iostream>
#include <vector>

class CKnapsackProblem {
public:
    CKnapsackProblem();
    CKnapsackProblem(int iItems, float fSize);
    bool loadFromFile(const std::string& filePath);
    bool setSize(float dSize);
    bool setItemsNumber(int iItems);
    bool addItem(float fValue, float fSize);
    int getItemsNumber();
    void print();
    void printItem(int iOffset);
    float evaluate(const std::vector<bool> & solution);
private:
    int items;
    float size;
    std::vector<float> sizes;
    std::vector<float> values;
};
