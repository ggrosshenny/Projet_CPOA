#include <iostream>
#include "ProjectVectors.hpp"
#include <cassert>
#include <type_traits>

int main()
{
    // =====
    // ProjectVector

    std::cout << "======================" << std::endl;
    std::cout << "Tests of ProjectVector" << std::endl;

    // -----------------
    // Test Constructors

      // Default constructor
    ProjectVector<int, 2> pv2De;
    assert(pv2De[0]==0);
    assert(pv2De[1]==0);
    std::cout << "Default constructor is Ok." << std::endl;

      // Brace-enclosed
    ProjectVector<int, 2> pv2Be = {0, 5};
    assert(pv2Be[0]==0);
    assert(pv2Be[1]==5);
    std::cout << "Brace-enclosed constructor with right number of arguments is Ok." << std::endl;

      // Brace-enclosed with more arguments and less arguments than needed has already been tested in Array_test


    // -----------------
    // Auxiliary methods

      // Norm
    int nrm = pv2Be.norm();
    assert(nrm == 5);
    std::cout << "Test of the norm method is Ok." << std::endl;

    // --------------------------
    // Operators with two vectors

      // operator +
    ProjectVector<int, 2> v2Add = {1,1};
    ProjectVector<int, 2> plusVector = pv2Be + v2Add;
    std::cout << plusVector << std::endl;
    assert(plusVector[0] == 1);
    assert(plusVector[1] == 6);
    std::cout << "Test of operator + is Ok." << std::endl;

      // operator -
    ProjectVector<int, 2> minusVector = pv2Be - v2Add;
    assert(minusVector[0] == -1);
    assert(minusVector[1] == 4);
    std::cout << "Test of operator - is Ok." << std::endl;

      // operator +=
    ProjectVector<int, 2> plusEglVector;
    plusEglVector += v2Add;
    assert(plusEglVector[0] == 1);
    assert(plusEglVector[1] == 1);
    std::cout << "Test of operator += is Ok." << std::endl;

      // operator -=
    ProjectVector<int, 2> minusEglVector;
    minusEglVector -= v2Add;
    assert(minusEglVector[0] == -1);
    assert(minusEglVector[1] == -1);
    std::cout << "Test of operator -= is Ok." << std::endl;

      // Operator =
    minusEglVector = plusEglVector;
    assert(minusEglVector[0] == plusEglVector[0]);
    assert(minusEglVector[1] == plusEglVector[1]);
    std::cout << "Test of operator = is Ok." << std::endl;

      // Scalar product
    int scalProd = minusEglVector * plusEglVector;
    assert(scalProd == 2);
    std::cout << "Test of the scalar product is Ok." << std::endl;

    // ------------------------------------
    // Operators with a vector and a scalar

      // Vector * scalar
    minusEglVector = minusEglVector * 2;
    assert(minusEglVector[0] == 2);
    assert(minusEglVector[1] == 2);
    std::cout << "Test of vector * scalar is Ok." << std::endl;

      // Scalar * vector
    minusEglVector = 2 * minusEglVector;
    assert(minusEglVector[0] == 4);
    assert(minusEglVector[1] == 4);
    std::cout << "Test of scalar * vector is Ok." << std::endl;

      // vector / scalar
    minusEglVector = minusEglVector / 2;
    assert(minusEglVector[0] == 2);
    assert(minusEglVector[1] == 2);
    std::cout << "Test of vector / scalar is Ok." << std::endl;

      // vector *= scalar
    minusEglVector *= 2;
    assert(minusEglVector[0] == 4);
    assert(minusEglVector[1] == 4);
    std::cout << "Test of scalar *= vector is Ok." << std::endl;

      // vector /= scalar
    minusEglVector /= 2;
    assert(minusEglVector[0] == 2);
    assert(minusEglVector[1] == 2);
    std::cout << "Test of vector /= scalar is Ok." << std::endl;


    // =====
    // Vec2T

    std::cout << "==============" << std::endl;
    std::cout << "Tests of Vec2T" << std::endl;

    // -----------------
    // Test Constructors

      // Default constructor
    Vec2T<int> v2De;
    assert(v2De[0]==0);
    assert(v2De[1]==0);
    std::cout << "Default constructor is Ok." << std::endl;

      // Brace-enclosed
    Vec2T<int> v2Be = {0, 5};
    assert(v2Be[0]==0);
    assert(v2Be[1]==5);
    std::cout << "Braced-enclosed constructor with right number of arguments is Ok." << std::endl;

    // -------
    // Methods

      // cross
    Vec2T<int> tempV2 = {1,5};
    Vec2T<int> temp2V2 = {5,0};
    int crss = temp2V2.cross(tempV2);
    assert(crss == 25);
    std::cout << "Test of the cross product is Ok." << std::endl;


    // =====
    // Vec3T

    std::cout << "==============" << std::endl;
    std::cout << "Tests of Vec3T" << std::endl;

    // -----------------
    // Test Constructors

      // Default constructor
    Vec3T<int> v3De;
    assert(v3De[0]==0);
    assert(v3De[1]==0);
    assert(v3De[2]==0);
    std::cout << "Default constructor is Ok." << std::endl;

      // Brace-enclosed
    Vec3T<int> v3Be = {1, 2, 3};
    assert(v3Be[0]==1);
    assert(v3Be[1]==2);
    assert(v3Be[2]==3);
    std::cout << "Braced-enclosed constructor with right number of arguments is Ok." << std::endl;

    // -------
    // Methods

      // cross
    Vec3T<int> crssVec3 = {3,2,1};
    Vec3T<int> crss3 = crssVec3.cross(v3Be);
    assert(crss3[0] == 4);
    assert(crss3[1] == -8);
    assert(crss3[2] == 4);
    std::cout << "Test of the cross product is Ok." << std::endl;


    // -----
    // Vec4I

    std::cout << "==============" << std::endl;
    std::cout << "Tests of Vec4I" << std::endl;

    Vec4I v4iDe;
    assert(v4iDe[0] == 0);
    assert(v4iDe[1] == 0);
    assert(v4iDe[2] == 0);
    assert(v4iDe[3] == 0);
    std::cout << "Test of default constructor is Ok." << std::endl;

    Vec4I v4i1 = {1, 2, 3, 4};
    assert(v4i1[0] == 1);
    assert(v4i1[1] == 2);
    assert(v4i1[2] == 3);
    assert(v4i1[3] == 4);
    std::cout << "Test of brace-enclosed constructor is Ok." << std::endl;


    // -----
    // Vec4D
    std::cout << "==============" << std::endl;
    std::cout << "Tests of Vec4D" << std::endl;

    Vec4D v4dDe;
    assert(v4dDe[0] == 0);
    assert(v4dDe[1] == 0);
    assert(v4dDe[2] == 0);
    assert(v4dDe[3] == 0);
    std::cout << "Test of default constructor is Ok." << std::endl;

    Vec4D v4d1 = {1.0, 2.0, 3.0, 4.0};
    assert(v4d1[0] == 1.0);
    assert(v4d1[1] == 2.0);
    assert(v4d1[2] == 3.0);
    assert(v4d1[3] == 4.0);
    std::cout << "Test of brace-enclosed constructor is Ok." << std::endl;

	return 0;
}


