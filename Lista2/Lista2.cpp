#include <iostream>
#include "Lista2.h"

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

    CTable(CTable &pcOther) {
        s_name = pcOther.s_name + "_copy";
        len = pcOther.len;
        array = new int[len];
        for (int i = 0; i < len; i++) {
            array[i] = pcOther.array[i];
        }
        std::cout << COPY_STRING << s_name << std::endl;
    }

//    ~CTable() {
//        delete array;
//        std::cout << DELETE_STRING << s_name << std::endl;
//    }

    void operator=(const CTable &pcOther) {
        array = pcOther.array;
        len = pcOther.len;
    }

    CTable operator+(const CTable &pcOther) {
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

    void vSetName(std::string sName) {
        s_name = sName;
    }

    bool bSetNewSize(int iTableLen) {
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

    CTable *pcClone() {
        return new CTable(*this);
    }

    void printSize() {
        std::cout << SIZE_STRING << len << std::endl;
    }

    void vPrint() {
        for (int i = 0; i < len; i++) {
            std::cout << array[i] << "\t";
        }
        std::cout << std::endl;
    }

    void vSetValueAt(int iOffset, int iNewVal) {
        if (iOffset < 0) {
            std::cout << "Negative Offset" << std::endl;
            return;
        }
        array[iOffset] = iNewVal;
    }

private:
    std::string s_name;
    int len;
    int *array;
};

class Matrix {
public:
    Matrix() {
        array = new int *[3];
        for (int i = 0; i < 3; i++) {
            array[i] = new int[3];
        }
        width = 3;
        height = 3;
    }

    Matrix(int iWidth, int iHeight) {
        array = new int *[iHeight];
        for (int i = 0; i < iHeight; i++) {
            array[i] = new int[iWidth];
        }
        width = iWidth;
        height = iHeight;
    }

    Matrix(int **iArray, int iWidth, int iHeight) {
        array = new int *[iHeight];
        for (int i = 0; i < iHeight; i++) {
            array[i] = new int[iWidth];
        }
        width = iWidth;
        height = iHeight;

        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                array[i][j] = iArray[i][j];
            }
        }
    }

    Matrix operator+(Matrix &pcOther) {
        Matrix resultMatrix = Matrix(width, height);

        if (width == pcOther.width && height == pcOther.height) {
            for (int i = 0; i < height; i++) {
                for (int j = 0; j < width; j++) {
                    resultMatrix.array[i][j] = array[i][j] + pcOther.array[i][j];
                }
            }
        } else {
            std::cout << "Wrong matrix sizes" << std::endl;
        }

        return resultMatrix;
    }

    void print() {
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                std::cout << array[i][j] << "\t";
            }
            std::cout << std::endl;
        }
    }

private:
    int **array;
    int width;
    int height;
};


int main() {
    //ZAD1
    std::cout << "\nZAD1" << std::endl;

    CTable c_tab_0, c_tab_1;
    c_tab_0.bSetNewSize(6);
    c_tab_1.bSetNewSize(4);
    c_tab_0 = c_tab_1;
    c_tab_0.printSize();
    c_tab_1.printSize();

    //ZAD2
    std::cout << "\nZAD2" << std::endl;

    //ZAD3
    std::cout << "\nZAD3" << std::endl;

    c_tab_1.vSetValueAt(2, 123);
    c_tab_0.vPrint();
    c_tab_1.vPrint();

    //ZAD4
    std::cout << "\nZAD4" << std::endl;

    c_tab_0.vSetValueAt(0, 0);
    c_tab_0.vSetValueAt(1, 1);
    c_tab_0.vSetValueAt(3, 3);

    CTable c_tab_2;
    c_tab_2 = c_tab_0 + c_tab_1;
    c_tab_2.vPrint();

    //MODYFIKACJA
    int width = 4;
    int height = 5;

    int **array = new int *[height];
    for (int i = 0; i < height; i++) {
        array[i] = new int[width];
    }

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            array[i][j] = i + j + 1;
        }
    }

    Matrix matrix1 = Matrix(array, width, height);
    Matrix matrix2 = Matrix(array, width, height);
    Matrix matrix3 = matrix1 + matrix2;
    matrix1.print();
    std::cout << std::endl;
    matrix2.print();
    std::cout << std::endl;
    matrix3.print();

    return 0;
}
