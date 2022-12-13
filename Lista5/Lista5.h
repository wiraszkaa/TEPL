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
    pc_counter->iAdd();
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
#define MOVE_STRING "przenosze: "

class CTable {
public:
    CTable();

    CTable(std::string sName, int iTableLen);

    CTable(CTable &pcOther);

    CTable(CTable &&pcOther);

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

#endif
