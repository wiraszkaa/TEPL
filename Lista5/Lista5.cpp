#include "Lista5.h"

int CRefCounter::iAdd() {
    return (++i_count);
}

int CRefCounter::iDec() {
    return (--i_count);
}

int CRefCounter::iGet() {
    return (i_count);
}


CTab::CTab(const CTab &cOther) {
    v_copy(cOther);
    std::cout << "Copy ";
}

CTab::~CTab() {
    if (pi_tab != NULL) delete pi_tab;
    std::cout << "Destr ";
}

CTab::CTab(CTab &&cOther) {
    pi_tab = cOther.pi_tab;
    i_size = cOther.i_size;
    cOther.pi_tab = NULL;
    std::cout << "MOVE ";
}

CTab CTab::operator=(const CTab &cOther) {
    if (pi_tab != NULL) delete pi_tab;
    v_copy(cOther);
    std::cout << "op= ";
    return (*this);
}

CTab CTab::operator=(CTab &&cOther) {
    if (pi_tab != NULL) delete pi_tab;
    pi_tab = cOther.pi_tab;
    i_size = cOther.i_size;
    cOther.pi_tab = NULL;
    return (*this);
}

bool CTab::bSetSize(int iNewSize) {
    if (i_size < 0) {
        std::cout << "Negative length." << std::endl;
        return false;
    }
    i_size = iNewSize;
    int *newArray = new int[i_size];
    for (int i = 0; i < std::min(i_size, iNewSize); i++) {
        newArray[i] = pi_tab[i];
    }
    pi_tab = newArray;

    return true;
}

int CTab::iGetSize() {
    return (i_size);
}

void CTab::v_copy(const CTab &cOther) {
    pi_tab = new int[cOther.i_size];
    i_size = cOther.i_size;
    for (int ii = 0; ii < cOther.i_size; ii++)
        pi_tab[ii] = cOther.pi_tab[ii];
}


CTable::CTable() {
    s_name = DEFAULT_S_NAME;
    len = DEFAULT_LEN;
    array = new int[len];
    std::cout << DEFAULT_STRING << s_name << std::endl;
}

CTable::CTable(std::string sName, int iTableLen) {
    s_name = sName;
    len = iTableLen;
    array = new int[len];
    std::cout << PARAMETER_STRING << s_name << std::endl;
}

CTable::CTable(CTable &pcOther) {
    s_name = pcOther.s_name + "_copy";
    len = pcOther.len;
    array = new int[len];
    for (int i = 0; i < len; i++) {
        array[i] = pcOther.array[i];
    }
    std::cout << COPY_STRING << s_name << std::endl;
}

CTable::CTable(CTable &&pcOther) {
    s_name = pcOther.s_name + "_move";
    len = pcOther.len;
    array = pcOther.array;

    pcOther.array = NULL;

    std::cout << MOVE_STRING << s_name << std::endl;
}

void CTable::operator=(const CTable &pcOther) {
    if (array != NULL) {
        delete array;
    }

    s_name = pcOther.s_name + "_copy";
    len = pcOther.len;
    array = new int[len];
    for (int i = 0; i < len; i++) {
        array[i] = pcOther.array[i];
    }
}

void CTable::operator=(CTable &&pcOther) {
    if (array != NULL) {
        delete array;
    }

    s_name = pcOther.s_name + "_move";
    len = pcOther.len;
    array = pcOther.array;
    pcOther.array = NULL;
}

CTable CTable::operator+(const CTable &pcOther) {
    int newLength = len + pcOther.len;
    int *newArray = new int[newLength];
    int pointer = 0;

    for (int i = 0; i < len; i++) {
        newArray[pointer] = array[i];
        pointer += 1;
    }
    for (int i = 0; i < pcOther.len; i++) {
        newArray[pointer] = pcOther.array[i];
        pointer += 1;
    }

    CTable newCTable(s_name + " + " + pcOther.s_name, newLength);
    newCTable.array = newArray;

    return newCTable;
}

CTable CTable::operator+(CTable &&pcOther) {
    int newLength = len + pcOther.len;
    int *newArray = new int[newLength];
    int pointer = 0;

    for (int i = 0; i < len; i++) {
        newArray[pointer] = array[i];
        pointer += 1;
    }
    for (int i = 0; i < pcOther.len; i++) {
        newArray[pointer] = pcOther.array[i];
        pointer += 1;
    }

    CTable newCTable(s_name + " + " + pcOther.s_name, newLength);
    newCTable.array = newArray;

    return newCTable;
}

void CTable::vSetName(std::string sName) { s_name = sName; }

bool CTable::bSetNewSize(int iTableLen) {
    if (iTableLen < 0) {
        std::cout << "Negative length." << std::endl;
        return false;
    }
    len = iTableLen;
    int *newArray = new int[len];
    for (int i = 0; i < std::min(len, iTableLen); i++) {
        newArray[i] = array[i];
    }
    array = newArray;

    return true;
}

CTable* CTable::pcClone() {
    return new CTable(*this);
}

void CTable::printSize() {
    std::cout << SIZE_STRING << len << std::endl;
}

void CTable::vPrint() {
    for (int i = 0; i < len; i++) {
        std::cout << array[i] << "\t";
    }
    std::cout << std::endl;
}

void CTable::vSetValueAt(int iOffset, int iNewVal) {
    if (iOffset < 0) {
        std::cout << "Negative Offset" << std::endl;
        return;
    }
    if (iOffset <= len) {
        std::cout << "Offset out of bands" << std::endl;
        return;
    }
    array[iOffset] = iNewVal;
}

int main() {
    double test = 10;
    CMySmartPointer<double> pointer(&test);

    CTable tab1("one", 1);
    CTable tab2("two", 2);
    CTable tab3("three", 3);

    CTable tab4;

//    tab4 = tab2 + tab3;
    tab4 = std::move(tab2 + std::move(tab3));
    tab4.printSize();

    return 0;
}
