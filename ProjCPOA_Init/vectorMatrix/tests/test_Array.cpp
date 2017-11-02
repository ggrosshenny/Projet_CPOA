#include "Array.hpp"

int main()
{
    Array<int, 3>test = {1, 2, 3};
    Array<int, 3>test2 = {3, 4, 5};
    Array<int, 3>test3 = {4, 5};
    std::cout << "test1 : " << test.toString() << std::endl;
    std::cout << "test2 : " << test2.toString() << std::endl;
    std::cout << "test3 : " << test3.toString() << std::endl;
    bool t1 = test == test;
    bool t2 = test == test2;
    bool t3 = test != test2;
    std::cout << "Valeur de test[0] : " << test[0] << std::endl;
    std::cout << "test == test ? : " << t1 << std::endl;
    std::cout << "test == test2 ? : " << t2 << std::endl;
    std::cout << "test != test2 ? : " << t3 << std::endl;
    std::cout << "Before test = test2 - test : " << test.toString() << " et test2 : " << test2.toString() << std::endl;
    test = test2;
    std::cout << "After test = test2 - test : " << test.toString() << " et test2 : " << test2.toString() << std::endl;

    return 0;
}


