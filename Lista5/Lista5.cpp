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

int main() {
    return 0;
}
