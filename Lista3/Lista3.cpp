#include <iostream>
#include <vector>
#include "Lista3.h"

class CNodeStatic {
public:
    CNodeStatic() {
        i_val = 0;
        pc_parent_node = NULL;
    }

    ~CNodeStatic() {
        std::cout << "BUM: " << i_val << std::endl;

        if (pc_parent_node != NULL) {
            delete pc_parent_node;
        }
    }

    void vSetValue(int iNewVal) {
        i_val = iNewVal;
    }

    int iGetChildrenNumber() {
        return (v_children.size());
    }

    void vAddNewChild() {
        CNodeStatic child;
        child.pc_parent_node = this;
        v_children.push_back(child);
    }

    void vAddNewChild(CNodeStatic *pcNewChildNode) {
        pcNewChildNode->pc_parent_node = this;
        v_children.push_back(*pcNewChildNode);
    }

    bool bRemoveChild(CNodeStatic *pcChildNode) {
        for (int i = 0; i < iGetChildrenNumber(); i++) {
            if (&v_children.at(i) == pcChildNode) {
                v_children.at(i).pc_parent_node = NULL;
                v_children.erase(v_children.begin() + i);
                return true;
            }
        }
        return false;
    }

    bool bIsRoot() {
        return pc_parent_node == NULL;
    }

    CNodeStatic *pcGetParent() {
        return pc_parent_node;
    }

    CNodeStatic *pcGetChild(int iChildOffset) {
        if (iChildOffset < 0) {
            std::cout << "Negative Offset" << std::endl;
            return NULL;
        }
        if (iChildOffset >= iGetChildrenNumber()) {
            std::cout << "Offset out of bands" << std::endl;
            return NULL;
        }

        return &v_children.at(iChildOffset);
    }

    void vPrint() {
        std::cout << " " << i_val;
    }

    void vPrintAllBelow() {
        for (int i = 0; i < iGetChildrenNumber(); i++) {
            v_children.at(i).vPrint();
            v_children.at(i).vPrintAllBelow();
        }
    }

    void vPrintUp() {
        vPrint();
        printUpHelper(pc_parent_node);
    }

private:
    std::vector<CNodeStatic> v_children;
    CNodeStatic *pc_parent_node;
    int i_val;

    void printUpHelper(CNodeStatic *parent) {
        if (parent != NULL) {
            parent->vPrint();
            printUpHelper(parent->pc_parent_node);
        }
    }
};

class CTreeStatic {
public:
    CNodeStatic *pcGetRoot() {
        return (&c_root);
    }

    void vPrintTree() {
        c_root.vPrint();
        c_root.vPrintAllBelow();
    }

    bool bMoveSubtree(CNodeStatic *pcParentNode, CNodeStatic *pcNewChildNode) {
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

private:
    CNodeStatic c_root;
};

class CNodeDynamic {
public:
    CNodeDynamic() {
        i_val = 0;
        pc_parent_node = NULL;
    };

    ~CNodeDynamic() {
        if (pc_parent_node != NULL) {
            delete pc_parent_node;
        }
        while(!v_children.empty()) {
            v_children.pop_back();
        }
    }

    void vSetValue(int iNewVal) {
        i_val = iNewVal;
    }

    int iGetChildrenNumber() {
        return v_children.size();
    }

    void vAddNewChild() {
        CNodeDynamic *child = new CNodeDynamic();
        child->pc_parent_node = this;
        v_children.push_back(child);
    }

    CNodeDynamic *pcGetChild(int iChildOffset) {
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

    void vPrint() {
        std::cout << " " << i_val;
    }

    void vPrintAllBelow() {
        for (int i = 0; i < iGetChildrenNumber(); i++) {
            v_children.at(i)->vPrint();
            v_children.at(i)->vPrintAllBelow();
        }
    }

private:
    std::vector<CNodeDynamic *> v_children;
    CNodeDynamic *pc_parent_node;
    int i_val;
};

class CTreeDynamic {
public:
    ~CTreeDynamic() {
        delete pc_root;
    }

    CNodeDynamic *pcGetRoot() {
        return (pc_root);
    }

    void vPrintTree() {
        pc_root->vPrint();
        pc_root->vPrintAllBelow();
    }

private:
    CNodeDynamic *pc_root;
};

int main() {
    std::cout << "ZAD2" << std::endl;
    CNodeStatic c_root;

    c_root.vAddNewChild();
    c_root.vAddNewChild();
    c_root.pcGetChild(0)->vSetValue(1);
    c_root.pcGetChild(1)->vSetValue(2);

    c_root.pcGetChild(0)->vAddNewChild();
    c_root.pcGetChild(0)->vAddNewChild();
    c_root.pcGetChild(0)->pcGetChild(0)->vSetValue(11);
    c_root.pcGetChild(0)->pcGetChild(1)->vSetValue(12);

    c_root.pcGetChild(0)->pcGetChild(0)->vAddNewChild();
    c_root.pcGetChild(0)->pcGetChild(0)->pcGetChild(0)->vSetValue(111);

    c_root.pcGetChild(1)->vAddNewChild();
    c_root.pcGetChild(1)->vAddNewChild();
    c_root.pcGetChild(1)->pcGetChild(0)->vSetValue(21);
    c_root.pcGetChild(1)->pcGetChild(1)->vSetValue(22);

    c_root.vPrintAllBelow();

    std::cout << "ZAD3" << std::endl;
    c_root.pcGetChild(0)->pcGetChild(0)->pcGetChild(0)->vPrintUp();

    std::cout << std::endl;
    return 0;
}
