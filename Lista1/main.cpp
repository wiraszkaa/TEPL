#include <iostream>
#include "main.h"

void v_alloc_table_fill_34(int iSize) {
    if (iSize < 0) {
        return;
    }

    int *table;
    table = new int[iSize];

    for (int i = 0; i < iSize; i++) {
        table[i] = number_34;
    }

    for (int i = 0; i < iSize; i++) {
        std::cout << table[i] << "\t";
    }
    std::cout << std::endl;

    delete [] table;
}

bool b_alloc_table_2_dim(int **&piTable, int iSizeX, int iSizeY) {
    if (iSizeX < 0 || iSizeY < 0) {
        return false;
    }

    piTable = new int*[iSizeX];

    for (int i = 0; i < iSizeX; i++) {
        piTable[i] = new int[iSizeY];
    }

    return true;
}

bool b_dealloc_table_2_dim(int **piTable, int iSizeX) {
    if (iSizeX < 0) {
        return false;
    }

    for (int i = 0; i < iSizeX; i++) {
        delete piTable[i];
    }

    delete piTable;

    return true;
}

class CTable {
public:
    CTable() {
        s_name = default_s_name;
        len = default_length;
        array = new int[len];
        std::cout << "bezp: " << s_name << std::endl;
    }

    CTable(std::string sName, int iTableLen) {
        s_name = sName;
        len = iTableLen;
        array = new int[len];
        std::cout << "parametr: " << s_name << std::endl;
    }

    CTable (CTable &pcOther) {
        s_name = pcOther.s_name;
        len = pcOther.len;
        array = new int[len];
        std::cout << "kopiuj: " << s_name << std::endl;
    }

    ~CTable() {
        std::cout << "usuwam: " << s_name << std::endl;
    }

    void vSetName(std::string sName) {
        s_name = sName;
    }

    bool bSetNewSize(int iTableLen) {
        if (iTableLen < 0) {
            return false;
        }
        len = iTableLen;
        array = new int[len];

        return true;
    }

    CTable *pcClone() {
        CTable *clone = new CTable(s_name, len);
        return clone;
    }

private:
    std::string s_name;
    int len;
    int *array;
};

int main() {
    // ZAD 1
    std::cout << "ZAD 1" << std::endl;
    v_alloc_table_fill_34(5);

    // ZAD 2
    std::cout << "\nZAD 2" << std::endl;

    int **piTable;
    b_alloc_table_2_dim(piTable, 5, 3);

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 3; j++) {
            piTable[i][j] = 2;
        }
    }

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 3; j++) {
            std::cout << piTable[i][j] << "\t";
        }
        std::cout << std::endl;
    }

    // ZAD 3
    std::cout << "\nZAD 3" << std::endl;

    b_dealloc_table_2_dim(piTable, 4);

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 3; j++) {
            std::cout << piTable[i][j] << "\t";
        }
        std::cout << std::endl;
    }

    // ZAD 4
    std::cout << "\nZAD 4" << std::endl;

    CTable *defaultCTable = new CTable();
    CTable *parameterCTable = new CTable("Parameter", 6);
    CTable *cloneCTable = new CTable(*parameterCTable);

    delete defaultCTable;

    CTable c_tab;
    CTable *pcCloneCTable;
    pcCloneCTable = c_tab.pcClone();

    return 0;
}