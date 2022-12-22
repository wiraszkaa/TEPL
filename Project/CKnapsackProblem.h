#pragma once
#include <iostream>
#include <vector>

class CKnapsackProblem {
public:
    CKnapsackProblem();
    CKnapsackProblem(int iItems, float fSize);
    bool setSize(float dSize);
    bool setItemsNumber(int iItems);
    bool setItem(int iOffset, float fValue, float fSize);
    int getItemsNumber();
    void print();
    void printItem(int iOffset);
    float evaluate(const std::vector<bool> & solution);
private:
    int items;
    float size;
    float *sizes;
    float *values;

    void setItems(int iItems);
};
