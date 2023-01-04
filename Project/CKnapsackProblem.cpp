#include "CKnapsackProblem.h"
#include <iostream>
#include <fstream>


CKnapsackProblem::CKnapsackProblem() {
    items = 5;
}

CKnapsackProblem::CKnapsackProblem(int iItems, float fSize) {
    items = iItems;
    size = fSize;
}

bool CKnapsackProblem::setSize(float dSize) {
    if (dSize >= 0) {
        size = dSize;
        return true;
    }
    return false;
}

bool CKnapsackProblem::setItemsNumber(int iItems) {
    if (iItems >= 0) {
        items = iItems;
        return true;
    }
    return false;
}

bool CKnapsackProblem::addItem(float fValue, float fSize) {
    if (values.size() < items) {
        values.push_back(fValue);
        sizes.push_back(fSize);
        return true;
    }
    return false;
}

void CKnapsackProblem::print() {
    std::cout << "KnapsackProblem:\nItems: "<< items << "\nLp.\tV.\tS." << std::endl;
    for (int i = 0; i < values.size(); i++) {
        printItem(i);
    }
}

void CKnapsackProblem::printItem(int iOffset) {
    if (iOffset >= 0 && iOffset < values.size()) {
        std::cout << (iOffset + 1) << ".\t" << values[iOffset] << "\t" << sizes[iOffset] << std::endl;
    }
}

float CKnapsackProblem::evaluate(const std::vector<bool> &solution) {
    float fSize = 0;
    float fValue = 0;
    for (int i = 0; i < items; i++) {
        if (solution[i]) {
            fSize += sizes[i];
            fValue += values[i];
        }
    }
    if (fSize <= size) {
        return fValue;
    }
    return 0;
}

int CKnapsackProblem::getItemsNumber() {
    return items;
}

bool CKnapsackProblem::loadFromFile(const std::string &filePath) {
    std::ifstream file(filePath);

    if (!file.is_open()) {
        std::cout << "Could not open " << filePath << std::endl;
        return false;
    }

    sizes.clear();
    values.clear();
    items = 0;

    std::string text;
    int i = 0;
    while (file >> text) {
        if (i == 0) {
            size = std::stof(text);
        } else {
            if (i % 2 == 0) {
                sizes.push_back(std::stof(text));
            } else {
                values.push_back(std::stof(text));
            }
        }

        i++;
    }

    if (sizes.size() != values.size()) {
        std::cout << "Sizes does not match Values" << std::endl;
        sizes.clear();
        values.clear();
        items = 0;
        return false;
    }

    items = sizes.size();

    return true;
}