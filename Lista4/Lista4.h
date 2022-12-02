#ifndef TEP_LISTA4_H

#include "vector"
#include <iostream>

template<typename T>
class CNodeDynamic {
public:
    CNodeDynamic() {
        pc_parent_node = NULL;
    };

    ~CNodeDynamic() {
//        std::cout << "Destructing dynamic node: " << i_val << std::endl;
        for (int i = 0; i < iGetChildrenNumber(); i++) {
            delete v_children.at(i);
        }
        v_children.clear();
    }

    void vSetValue(T iNewVal);

    int iGetChildrenNumber();

    void vAddNewChild();

    void vAddNewChild(CNodeDynamic *pcNewChildNode);

    bool bRemoveChild(CNodeDynamic *pcChildNode);

    bool bIsRoot();

    CNodeDynamic *pcGetParent();

    CNodeDynamic *pcGetChild(int iChildOffset);

    void vPrint();

    void vPrintAllBelow();

    void vPrintUp();

private:
    std::vector<CNodeDynamic<T> *> v_children;
    CNodeDynamic<T> *pc_parent_node;
    T i_val;

    void printUpHelper(CNodeDynamic *parent) {
        if (parent != NULL) {
            parent->vPrint();
            printUpHelper(parent->pc_parent_node);
        }
    }
};

template<typename T>
void CNodeDynamic<T>::vSetValue(T iNewVal) {
    i_val = iNewVal;
}

template<typename T>
int CNodeDynamic<T>::iGetChildrenNumber() {
    return v_children.size();
}

template<typename T>
void CNodeDynamic<T>::vAddNewChild() {
    CNodeDynamic<T> *child = new CNodeDynamic<T>();
    child->pc_parent_node = this;
    v_children.push_back(child);
}

template<typename T>
void CNodeDynamic<T>::vAddNewChild(CNodeDynamic *pcNewChildNode) {
    pcNewChildNode->pc_parent_node = this;
    v_children.push_back(pcNewChildNode);
}

template<typename T>
bool CNodeDynamic<T>::bRemoveChild(CNodeDynamic<T> *pcChildNode) {
    for (int i = 0; i < iGetChildrenNumber(); i++) {
        if (v_children.at(i) == pcChildNode) {
            pcChildNode->pc_parent_node = NULL;
            v_children.erase(v_children.begin() + i);
            return true;
        }
    }
    return false;
}

template<typename T>
bool CNodeDynamic<T>::bIsRoot() {
    return pc_parent_node == NULL;
}

template<typename T>
CNodeDynamic<T> *CNodeDynamic<T>::pcGetParent() {
    return pc_parent_node;
}

template<typename T>
CNodeDynamic<T> *CNodeDynamic<T>::pcGetChild(int iChildOffset) {
    if (iChildOffset < 0) {
        std::cout << "Negative Offset" << std::endl;
        return NULL;
    }
    if (iChildOffset >= iGetChildrenNumber()) {
        std::cout << "Offset out of bands" << std::endl;
        return NULL;
    }

    return v_children.at(iChildOffset);
}

template<typename T>
void CNodeDynamic<T>::vPrint() {
    std::cout << " " << i_val;
}

template<typename T>
void CNodeDynamic<T>::vPrintAllBelow() {
    for (int i = 0; i < iGetChildrenNumber(); i++) {
        v_children.at(i)->vPrint();
        v_children.at(i)->vPrintAllBelow();
    }
}

template<typename T>
void CNodeDynamic<T>::vPrintUp() {
    vPrint();
    printUpHelper(pc_parent_node);
}


template<typename T>
class CTreeDynamic {
public:
    CTreeDynamic() {
        pc_root = new CNodeDynamic<T>();
    }

    ~CTreeDynamic() {
        delete pc_root;
    }

    CNodeDynamic<T> *pcGetRoot();

    void vPrintTree();

    bool bMoveSubtree(CNodeDynamic<T> *pcParentNode, CNodeDynamic<T> *pcNewChildNode);

private:
    CNodeDynamic<T> *pc_root;
};

template<typename T>
CNodeDynamic<T> *CTreeDynamic<T>::pcGetRoot() {
    return (pc_root);
}

template<typename T>
void CTreeDynamic<T>::vPrintTree() {
    pc_root->vPrint();
    pc_root->vPrintAllBelow();
    std::cout << std::endl;
}

template<typename T>
bool CTreeDynamic<T>::bMoveSubtree(CNodeDynamic<T> *pcParentNode,
                                   CNodeDynamic<T> *pcNewChildNode) {
    if (pcParentNode == NULL || pcNewChildNode == NULL) {
        std::cout << "Null Value" << std::endl;
        return false;
    }
    if (pcNewChildNode->bIsRoot()) {
        std::cout << "New Child cannot be root" << std::endl;
        return false;
    }

    pcNewChildNode->pcGetParent()->bRemoveChild(pcNewChildNode);
    pcParentNode->vAddNewChild(pcNewChildNode);
    return true;
}

#endif