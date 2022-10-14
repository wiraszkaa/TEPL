#include <iostream>
#include "main.h"

//ZAD 1
void v_alloc_table_fill_34(int iSize) {
    if (iSize < 0) {
        return;
    }

    int *table;
    table = new int[iSize];

    for (int i = 0; i < iSize; i++) {
        table[i] = NUMBER_34;
    }

    for (int i = 0; i < iSize; i++) {
        std::cout << table[i] << "\t";
    }
    std::cout << std::endl;

    delete table;
}
//ZAD 2
bool b_alloc_table_2_dim(int **&piTable, int iSizeX, int iSizeY) {
    if (iSizeX < 0 || iSizeY < 0 || piTable == NULL) {
        return false;
    }

    piTable = new int*[iSizeY];

    for (int i = 0; i < iSizeY; i++) {
        piTable[i] = new int[iSizeX];
    }

    return true;
}
//ZAD 3
bool b_dealloc_table_2_dim(int **piTable, int iSizeY) {
    if (iSizeY < 0 || piTable == NULL) {
        return false;
    }

    for (int i = 0; i < iSizeY; i++) {
        delete piTable[i];
    }

    delete piTable;

    return true;
}
//ZAD 4
class CTable {
public:
    CTable() {
        s_name = DEFAULT_S_NAME;
        len = DEFAULT_LEN;
        array = new int[len];
        std::cout << DEFAULT_STRING << s_name << std::endl;
    }

    CTable(std::string sName, int iTableLen) {
        s_name = sName;
        len = iTableLen;
        array = new int[len];
        std::cout << PARAMETER_STRING << s_name << std::endl;
    }

    CTable (CTable &pcOther) {
        s_name = pcOther.s_name + "_copy";
        len = pcOther.len;
        array = new int[len];
        std::cout << COPY_STRING << s_name << std::endl;
    }

    ~CTable() {
        std::cout << DELETE_STRING << s_name << std::endl;
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

    void printSize() {
        std::cout << SIZE_STRING << len << std::endl;
    }

private:
    std::string s_name;
    int len;
    int *array;
};

void v_mod_tab(CTable *pcTab, int iNewSize) {
    pcTab->bSetNewSize(iNewSize);
}

void v_mod_tab(CTable c_tab, int iNewSize) {
    c_tab.bSetNewSize(iNewSize);
}
// TESTY
int main() {
    // ZAD 1
    std::cout << ZAD1 << std::endl;
    v_alloc_table_fill_34(SIZE_X);

    // ZAD 2
    std::cout << ZAD2 << std::endl;

    int **piTable;
    b_alloc_table_2_dim(piTable, SIZE_X, SIZE_Y);

    for (int i = 0; i < SIZE_Y; i++) {
        for (int j = 0; j < SIZE_X; j++) {
            piTable[i][j] = 1;
        }
    }

    for (int i = 0; i < SIZE_Y; i++) {
        for (int j = 0; j < SIZE_X; j++) {
            std::cout << piTable[i][j] << "\t";
        }
        std::cout << std::endl;
    }

    // ZAD 3
    std::cout << ZAD3 << std::endl;

    std::cout << b_dealloc_table_2_dim(piTable, SIZE_Y) << std::endl;

    // ZAD 4
    std::cout << ZAD4 << std::endl;

    CTable *defaultCTable = new CTable();
    CTable *parameterCTable = new CTable("parameter", SIZE_X);
    CTable *cloneCTable = new CTable(*parameterCTable);

    delete defaultCTable;
    delete parameterCTable;
    delete cloneCTable;

    CTable c_tab;
    CTable *pcCloneCTable;
    pcCloneCTable = c_tab.pcClone();

    int iNewSize = 2;
    v_mod_tab(c_tab, iNewSize);
    c_tab.printSize();
    v_mod_tab(pcCloneCTable, iNewSize);
    pcCloneCTable->printSize();

    delete pcCloneCTable;

    return 0;
}