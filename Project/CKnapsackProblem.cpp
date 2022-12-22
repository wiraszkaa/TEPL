#include "CKnapsackProblem.h"

CKnapsackProblem::CKnapsackProblem() {
    setItems(5);
}

CKnapsackProblem::CKnapsackProblem(int iItems, float fSize) {
    setItems(iItems);
    size = fSize;
}

void CKnapsackProblem::setItems(int iItems) {
    items = iItems;
    sizes = new float[items];
    values = new float[items];
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
        setItems(items);
        return true;
    }
    return false;
}

bool CKnapsackProblem::setItem(int iOffset, float fValue, float fSize) {
    if (iOffset >= 0 && iOffset < items) {
        values[iOffset] = fValue;
        sizes[iOffset] = fSize;
        return true;
    }
    return false;
}

void CKnapsackProblem::print() {
    std::cout << "KnapsackProblem:\nLp.\tV.\tS." << std::endl;
    for (int i = 0; i < items; i++) {
        printItem(i);
    }
}

void CKnapsackProblem::printItem(int iOffset) {
    if (iOffset >= 0 && iOffset < items) {
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
