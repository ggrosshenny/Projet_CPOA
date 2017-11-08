#include "Array.hpp"
#include <cassert>
#include <type_traits>


int main()
{



    std::cout << "----------------" << std::endl;
    std::cout << "Begin Array test" << std::endl;


    // ----------------
    // Constructor test

    // Default constructor
    Array<int, 3> testDefault;
    assert(testDefault[0]==0);
    assert(testDefault[1]==0);
    assert(testDefault[2]==0);
    std::cout << "Braced-enclosed constructor with right number of arguments is Ok." << std::endl;

    // Braced-enclosed constructor :
      // Right number of arguments
    Array<int, 3>test = {1, 2, 3};
    assert(test[0]==1);
    assert(test[1]==2);
    assert(test[2]==3);
    std::cout << "Braced-enclosed constructor with right number of arguments is Ok." << std::endl;

      // More arguments given than excpected
    Array<int, 3>test2 = {3, 4, 5};
    assert(test2[0]==3);
    assert(test2[1]==4);
    assert(test2[2]==5);
    std::cout << "Braced-enclosed constructor with more arguments than expected is Ok." << std::endl;

      // Less arguments given than expected
    Array<int, 3>test3 = {4, 5};
    assert(test3[0]==4);
    assert(test3[1]==5);
    assert(test3[2]==0);
    std::cout << "Braced-enclosed constructor with less arguments than expected is Ok." << std::endl;


    // --------------
    // Operators test

      // == should be true
    bool t1 = test == test;
    assert(t1);
      // == should be false;
    bool t2 = test == test2;
    assert(!t2);
    std::cout << "Test of operator == is Ok." << std::endl;

      // != should be true
    bool t3 = test != test2;
    assert(t3);
      // != should be false
    bool t4 = test != test;
    assert(!t4);
    std::cout << "Test of operator != is Ok." << std::endl;

      // Test of operator [] (set)
    testDefault[0] = 1;
    assert(testDefault[0]==1);
      // Test of operator [] (get)
    assert(testDefault[1] == 0);
    std::cout << "Test of operator [] is Ok." << std::endl;

      // Test of operator =
    test = test2;
    assert(test==test2);
    std::cout << "Test of operator = is Ok." << std::endl;

      // Test of operator <<
    std::stringstream testOperatorOutput;
    std::stringstream testString;
    testOperatorOutput << test;
    testString << "[" << test[0] << ", " << test[1] << ", " << test[2] << "]";
    assert(testOperatorOutput.str() == testString.str());
    std::cout << "Test of operator << is Ok." << std::endl;


    // Test of auxiliary methods
      // getPtr
    int* tab = test.get_ptr();
    assert(tab[0] == test[0]);
    std::cout << "Test of getPtr() is Ok." << std::endl;

      // swapData
    int test0 = test[0];
    test.swapData(test3);
    assert(test3[0] = test0);
    std::cout << "Test of swapData is Ok." << std::endl;

      // toString


    DynamicArray<double> testda = {2.0, 3.0, 4.0, 5.0};
    DynamicArray<double> testda2 = {0.0, 0.0};
    DynamicArray<unsigned char> testuc = {0, 1, 1, 0};

    testda2 = testda;

    double dbl = testda[0];
    double dbl2 = testda2[0];

    std::cout << "testda : " << testda << std::endl;
    std::cout << "testuc : " << testuc << std::endl;
    std::cout << "testda[0] : " << dbl << std::endl;
    std::cout << "testda2[0] : " << dbl2 << std::endl;

    return 0;
}


