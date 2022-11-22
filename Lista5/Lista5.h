#ifndef TEP_LISTA5_H

#include <iostream>

class CRefCounter {
public:
    CRefCounter() { i_count; }

    int iAdd();

    int iDec();

    int iGet();

private:
    int i_count;
};

template<typename T>
class CMySmartPointer {
public:
    CMySmartPointer(T *pcPointer) {
        pc_pointer = pcPointer;
        pc_counter = new CRefCounter();
        pc_counter->iAdd();
    }

    CMySmartPointer(const CMySmartPointer &pcOther) {
        pc_pointer = pcOther.pc_pointer;
        pc_counter = pcOther.pc_counter;
        pc_counter->iAdd();
    }

    ~CMySmartPointer() {
        if (pc_counter->iDec() == 0) {
            delete pc_pointer;
            delete pc_counter;
        }
    }

    T &operator*();

    T *operator->();

    void operator=(const CMySmartPointer<T> &pcOther);

private:
    CRefCounter *pc_counter;
    T *pc_pointer;
};

template<typename T>
T &CMySmartPointer<T>::operator*() {
    return (*pc_pointer);
}

template<typename T>
T *CMySmartPointer<T>::operator->() {
    return (pc_pointer);
}

template<typename T>
void CMySmartPointer<T>::operator=(const CMySmartPointer<T> &pcOther) {
    if (pc_pointer != NULL) {
        if (pc_counter->iDec() == 0) {
            delete pc_pointer;
            delete pc_counter;
        }
    }
    pc_pointer = pcOther.pc_pointer;
    pc_counter = pcOther.pc_counter;
}


#define DEF_TAB_SIZE 10

class CTab {
public:
    CTab() {
        pi_tab = new int[DEF_TAB_SIZE];
        i_size = DEF_TAB_SIZE;
    }

    CTab(const CTab &cOther);

    CTab(CTab &&cOther);

    CTab operator=(const CTab &cOther);

    CTab operator=(CTab &&cOther);

    ~CTab();

    bool bSetSize(int iNewSize);

    int iGetSize();

private:
    void v_copy(const CTab &cOther);

    int *pi_tab;
    int i_size;
};


#define DEFAULT_LEN 5;
#define DEFAULT_S_NAME "default"
#define DEFAULT_STRING "bezp: "
#define PARAMETER_STRING "parametr: "
#define COPY_STRING "kopiuj: "
#define DELETE_STRING "usuwam: "
#define SIZE_STRING "Size: "

class CTable {
public:
    CTable();

    CTable(std::string sName, int iTableLen);

    CTable(CTable &pcOther);

//    ~CTable() {
//        delete array;
//        std::cout << DELETE_STRING << s_name << std::endl;
//    }

    void operator=(const CTable &pcOther);

    void operator=(CTable &&pcOther);

    CTable operator+(const CTable &pcOther);

    CTable operator+(CTable &&pcOther);

    void vSetName(std::string sName);

    bool bSetNewSize(int iTableLen);

    CTable *pcClone();

    void printSize();

    void vPrint();

    void vSetValueAt(int iOffset, int iNewVal);

private:
    std::string s_name;
    int len;
    int *array;
};

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

void CTable::operator=(const CTable &pcOther) {
    array = pcOther.array;
    len = pcOther.len;
}

void CTable::operator=(CTable &&pcOther) {
    array = pcOther.array;
    len = pcOther.len;
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

    CTable *newCTable = new CTable(s_name, newLength);
    newCTable->array = newArray;

    return *newCTable;
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

    CTable newCTable(s_name, newLength);
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

#endif
