#include <iostream>
#include <vector>

class CNodeStatic {
public:
    CNodeStatic() {
        i_val = 0;
        pc_parent_node = NULL;
    }

    ~CNodeStatic() {
//        std::cout << "Destructing static node: " << i_val << std::endl;
        while (!v_children.empty()) {
            v_children.pop_back();
        }
    }

    void vSetValue(int iNewVal) {
        i_val = iNewVal;
    }

    int iGetChildrenNumber() {
        return (v_children.size());
    }

    int iGetValue() {
        return i_val;
    }

    std::vector<CNodeStatic> cpGetChildren() {
        return v_children;
    }

    void vAddNewChild() {
        CNodeStatic child;
        child.pc_parent_node = this;
        v_children.push_back(child);
    }

    void vAddNewChild(CNodeStatic *pcNewChildNode) {
        CNodeStatic child_clone(*pcNewChildNode);
        child_clone.pc_parent_node = this;
        v_children.push_back(child_clone);
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

    void printPathUp(CNodeStatic *node) {
        node->vPrint();
        if (node->pcGetParent() != NULL) {
            printPathUp(node->pcGetParent());
        }
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
        std::cout << std::endl;
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

        pcParentNode->vAddNewChild(pcNewChildNode);
        pcNewChildNode->pcGetParent()->bRemoveChild(pcNewChildNode);
        return true;
    }

    CNodeStatic *pcGetNode(int value) {
        return getNodeHelper(&c_root, value);
    }

private:
    CNodeStatic c_root;

    CNodeStatic *getNodeHelper (CNodeStatic *node, int value) {
        if (node->iGetValue() == value) {
            return node;
        } else {
            for (int i = 0; i < node->iGetChildrenNumber(); i++) {
                return getNodeHelper(&node->cpGetChildren().at(i), value);
            }
        }
    }
};

class CNodeDynamic {
public:
    CNodeDynamic() {
        i_val = 0;
        pc_parent_node = NULL;
    };

    ~CNodeDynamic() {
        std::cout << "Destructing dynamic node: " << i_val << std::endl;
        for (int i = 0; i < iGetChildrenNumber(); i++) {
            delete v_children.at(i);
        }
        v_children.clear();
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

    void vAddNewChild(CNodeDynamic *pcNewChildNode) {
        pcNewChildNode->pc_parent_node = this;
        v_children.push_back(pcNewChildNode);
    }

    bool bRemoveChild(CNodeDynamic *pcChildNode) {
        for (int i = 0; i < iGetChildrenNumber(); i++) {
            if (v_children.at(i) == pcChildNode) {
                v_children.at(i)->pc_parent_node = NULL;
                v_children.erase(v_children.begin() + i);
                return true;
            }
        }
        return false;
    }

    bool bIsRoot() {
        return pc_parent_node == NULL;
    }

    CNodeDynamic *pcGetParent() {
        return pc_parent_node;
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

    void vPrintUp() {
        vPrint();
        printUpHelper(pc_parent_node);
    }

private:
    std::vector<CNodeDynamic *> v_children;
    CNodeDynamic *pc_parent_node;
    int i_val;

    void printUpHelper(CNodeDynamic *parent) {
        if (parent != NULL) {
            parent->vPrint();
            printUpHelper(parent->pc_parent_node);
        }
    }
};

class CTreeDynamic {
public:
    CTreeDynamic() {
        pc_root = new CNodeDynamic();
    }

    ~CTreeDynamic() {
        delete pc_root;
    }

    CNodeDynamic *pcGetRoot() {
        return (pc_root);
    }

    void vPrintTree() {
        pc_root->vPrint();
        pc_root->vPrintAllBelow();
        std::cout << std::endl;
    }

    bool bMoveSubtree(CNodeDynamic *pcParentNode, CNodeDynamic *pcNewChildNode) {
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
    CNodeDynamic *pc_root;
};

void zad23() {
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

//    c_root.pcGetChild(0)->pcGetChild(0)->vAddNewChild();
//    c_root.pcGetChild(0)->pcGetChild(0)->pcGetChild(0)->vSetValue(111);

    c_root.pcGetChild(1)->vAddNewChild();
    c_root.pcGetChild(1)->vAddNewChild();
    c_root.pcGetChild(1)->pcGetChild(0)->vSetValue(21);
    c_root.pcGetChild(1)->pcGetChild(1)->vSetValue(22);

    c_root.vPrintAllBelow();

    std::cout << "\nZAD3" << std::endl;
    c_root.pcGetChild(0)->pcGetChild(0)->vPrintUp();
}

void zad6() {
    std::cout << "\nZAD6" << std::endl;
    std::cout << "Static" << std::endl;
    CTreeStatic c_tree1;
    c_tree1.pcGetRoot()->vAddNewChild();
    c_tree1.pcGetRoot()->vAddNewChild();
    c_tree1.pcGetRoot()->pcGetChild(0)->vSetValue(101);
    c_tree1.pcGetRoot()->pcGetChild(1)->vSetValue(102);

    c_tree1.pcGetRoot()->pcGetChild(0)->vAddNewChild();
    c_tree1.pcGetRoot()->pcGetChild(0)->vAddNewChild();
    c_tree1.pcGetRoot()->pcGetChild(0)->pcGetChild(0)->vSetValue(1011);
    c_tree1.pcGetRoot()->pcGetChild(0)->pcGetChild(1)->vSetValue(1012);

//    c_tree1.pcGetRoot()->pcGetChild(0)->pcGetChild(0)->vAddNewChild();
//    c_tree1.pcGetRoot()->pcGetChild(0)->pcGetChild(0)->pcGetChild(0)->vSetValue(10111);

    c_tree1.pcGetRoot()->pcGetChild(1)->vAddNewChild();
    c_tree1.pcGetRoot()->pcGetChild(1)->vAddNewChild();
    c_tree1.pcGetRoot()->pcGetChild(1)->pcGetChild(0)->vSetValue(1021);
    c_tree1.pcGetRoot()->pcGetChild(1)->pcGetChild(1)->vSetValue(1022);

    c_tree1.vPrintTree();

    CTreeStatic c_tree2;
    c_tree2.pcGetRoot()->vAddNewChild();
    c_tree2.pcGetRoot()->vAddNewChild();
    c_tree2.pcGetRoot()->pcGetChild(0)->vSetValue(201);
    c_tree2.pcGetRoot()->pcGetChild(1)->vSetValue(202);

    c_tree2.pcGetRoot()->pcGetChild(0)->vAddNewChild();
    c_tree2.pcGetRoot()->pcGetChild(0)->vAddNewChild();
    c_tree2.pcGetRoot()->pcGetChild(0)->pcGetChild(0)->vSetValue(2011);
    c_tree2.pcGetRoot()->pcGetChild(0)->pcGetChild(1)->vSetValue(2012);

//    c_tree2.pcGetRoot()->pcGetChild(0)->pcGetChild(0)->vAddNewChild();
//    c_tree2.pcGetRoot()->pcGetChild(0)->pcGetChild(0)->pcGetChild(0)->vSetValue(20111);

    c_tree2.pcGetRoot()->pcGetChild(1)->vAddNewChild();
    c_tree2.pcGetRoot()->pcGetChild(1)->vAddNewChild();
    c_tree2.pcGetRoot()->pcGetChild(1)->pcGetChild(0)->vSetValue(2021);
    c_tree2.pcGetRoot()->pcGetChild(1)->pcGetChild(1)->vSetValue(2022);

    c_tree2.vPrintTree();

    c_tree1.bMoveSubtree(c_tree1.pcGetRoot(), c_tree2.pcGetRoot()->pcGetChild(0));
    c_tree1.vPrintTree();
    c_tree2.vPrintTree();

    std::cout << "\nDynamic" << std::endl;

    CTreeDynamic c_treed1;
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

    CTreeDynamic c_treed2;
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

void mod() {
    std::cout << "MODIFICATION" << std::endl;
    CTreeStatic c_tree1;
    c_tree1.pcGetRoot()->vAddNewChild();
    c_tree1.pcGetRoot()->vAddNewChild();
    c_tree1.pcGetRoot()->pcGetChild(0)->vSetValue(101);
    c_tree1.pcGetRoot()->pcGetChild(1)->vSetValue(102);

    c_tree1.pcGetRoot()->pcGetChild(0)->vAddNewChild();
    c_tree1.pcGetRoot()->pcGetChild(0)->vAddNewChild();
    c_tree1.pcGetRoot()->pcGetChild(0)->pcGetChild(0)->vSetValue(1011);
    c_tree1.pcGetRoot()->pcGetChild(0)->pcGetChild(1)->vSetValue(1012);

    c_tree1.pcGetRoot()->pcGetChild(0)->pcGetChild(0)->vAddNewChild();
    c_tree1.pcGetRoot()->pcGetChild(0)->pcGetChild(0)->pcGetChild(0)->vSetValue(10111);

    c_tree1.pcGetRoot()->pcGetChild(1)->vAddNewChild();
    c_tree1.pcGetRoot()->pcGetChild(1)->vAddNewChild();
    c_tree1.pcGetRoot()->pcGetChild(1)->pcGetChild(0)->vSetValue(1021);
    c_tree1.pcGetRoot()->pcGetChild(1)->pcGetChild(1)->vSetValue(1022);

    c_tree1.pcGetRoot()->printPathUp(c_tree1.pcGetNode(10111));

//    c_root.printPathUp(c_root.pcGetChild(0)->pcGetChild(0)->pcGetChild(0));
}

int main() {
//    zad23();
//    zad6();
    mod();

    std::cout << std::endl;
    return 0;
}
