#include "Lista4.h"

int main() {
    CTreeDynamic<int> c_treed1;
    c_treed1.pcGetRoot()->vAddNewChild();
    c_treed1.pcGetRoot()->vAddNewChild();
    c_treed1.pcGetRoot()->pcGetChild(0)->vSetValue(101);
    c_treed1.pcGetRoot()->pcGetChild(1)->vSetValue(102);

    c_treed1.pcGetRoot()->pcGetChild(0)->vAddNewChild();
    c_treed1.pcGetRoot()->pcGetChild(0)->vAddNewChild();
    c_treed1.pcGetRoot()->pcGetChild(0)->pcGetChild(0)->vSetValue(1011);
    c_treed1.pcGetRoot()->pcGetChild(0)->pcGetChild(1)->vSetValue(1012);

    c_treed1.pcGetRoot()->pcGetChild(1)->vAddNewChild();
    c_treed1.pcGetRoot()->pcGetChild(1)->vAddNewChild();
    c_treed1.pcGetRoot()->pcGetChild(1)->pcGetChild(0)->vSetValue(1021);
    c_treed1.pcGetRoot()->pcGetChild(1)->pcGetChild(1)->vSetValue(1022);

    c_treed1.vPrintTree();

    CTreeDynamic<int> c_treed2;
    c_treed2.pcGetRoot()->vAddNewChild();
    c_treed2.pcGetRoot()->vAddNewChild();
    c_treed2.pcGetRoot()->pcGetChild(0)->vSetValue(201);
    c_treed2.pcGetRoot()->pcGetChild(1)->vSetValue(202);

    c_treed2.pcGetRoot()->pcGetChild(0)->vAddNewChild();
    c_treed2.pcGetRoot()->pcGetChild(0)->vAddNewChild();
    c_treed2.pcGetRoot()->pcGetChild(0)->pcGetChild(0)->vSetValue(2011);
    c_treed2.pcGetRoot()->pcGetChild(0)->pcGetChild(1)->vSetValue(2012);

    c_treed2.pcGetRoot()->pcGetChild(1)->vAddNewChild();
    c_treed2.pcGetRoot()->pcGetChild(1)->vAddNewChild();
    c_treed2.pcGetRoot()->pcGetChild(1)->pcGetChild(0)->vSetValue(2021);
    c_treed2.pcGetRoot()->pcGetChild(1)->pcGetChild(1)->vSetValue(2022);

    c_treed2.vPrintTree();

    c_treed1.bMoveSubtree(c_treed1.pcGetRoot(), c_treed2.pcGetRoot()->pcGetChild(0));
    c_treed1.vPrintTree();
    c_treed2.vPrintTree();
}