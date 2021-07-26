#include <iostream>

#include "matrix/denseMatrix.hpp"

int main() {
    try {
        DenseMatrix m1(2, 3);
        m1[0][0] = 1;
        *(*(m1 + 0) + 1) = 2;
        m1[0][2] = 3;
        m1[1][0] = 4;
        m1[1][1] = 5;
        m1[1][2] = 6;
        DenseMatrix m2(3, 3);
        m2.set(0, 0, 1);
        m2.set(0, 1, 2);
        m2.set(0, 2, 3);
        m2.set(1, 0, 4);
        m2.set(1, 1, 5);
        m2.set(1, 2, 6);
        m2.set(2, 0, 7);
        m2.set(2, 1, 8);
        m2.set(2, 2, 9);

        std::cout << m1 << m2;
        DenseMatrix mult = m1 * m2;
        mult.set(0, 1, 0);
        std::cout << mult;
        // mult.printCSR();
        *(*mult + 1) = 1000;
        std::cout << mult << "*(*(mult+1)) = " << *(*(mult+1)) << std::endl;
    } catch (std::exception &ex) {
        std::cout << ex.what() << std::endl;
    }
    return 0;
}