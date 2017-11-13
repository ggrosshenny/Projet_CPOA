#include <iostream>
#include "Matrix33d.h"
#include <cassert>
#include <cmath>


int main()
{

    // --------------
    // Test of Matrix

    std::cout << "==============" << std::endl;
    std::cout << "Tests of Vec3T" << std::endl;


    // ============
    // Constructors

      // Default constructor
    Matrix33D mDe;

    assert(mDe[0][0] == 0.0);
    assert(mDe[0][1] == 0.0);
    assert(mDe[0][2] == 0.0);
    // Second row
    assert(mDe[1][0] == 0.0);
    assert(mDe[1][1] == 0.0);
    assert(mDe[1][2] == 0.0);
    // Third row
    assert(mDe[2][0] == 0.0);
    assert(mDe[2][1] == 0.0);
    assert(mDe[2][2] == 1.0);
    std::cout << "Test of default constructor is Ok." << std::endl;

      // Brace-enclosed constructor
    Matrix33D mBe = {{1.0, 0.0, 0.0},{0.0, 1.0, 0.0},{0.0, 0.0, 1.0}};
    // First row
    assert(mBe[0][0] == 1.0);
    assert(mBe[0][1] == 0.0);
    assert(mBe[0][2] == 0.0);
    // Second row
    assert(mBe[1][0] == 0.0);
    assert(mBe[1][1] == 1.0);
    assert(mBe[1][2] == 0.0);
    // Third row
    assert(mBe[2][0] == 0.0);
    assert(mBe[2][1] == 0.0);
    assert(mBe[2][2] == 1.0);
    std::cout << "Test of brace-enclosed constructor is Ok." << std::endl;

      // Brace-enclosed constructor with more argument than expected
    Matrix33D mBe2 = {{1.0, 0.0, 0.0},{0.0, 1.0, 0.0,1.0,2.0},{0.0, 0.0, 1.0},{0.0,1.0,1.0,1.0}};
    // First row
    assert(mBe2[0][0] == 1.0);
    assert(mBe2[0][1] == 0.0);
    assert(mBe2[0][2] == 0.0);
    // Second row
    assert(mBe2[1][0] == 0.0);
    assert(mBe2[1][1] == 1.0);
    assert(mBe2[1][2] == 0.0);
    // Third row
    assert(mBe2[2][0] == 0.0);
    assert(mBe2[2][1] == 0.0);
    assert(mBe2[2][2] == 1.0);
    std::cout << "Test of brace-enclosed constructor with more argument than needed is Ok." << std::endl;

      // Brace-enclosed constructor with less arguments than expected
    Matrix33D mBe3 = {{1.0, 0.0, 0.0},{0.0, 1.0}};
    // First row
    assert(mBe3[0][0] == 1.0);
    assert(mBe3[0][1] == 0.0);
    assert(mBe3[0][2] == 0.0);
    // Second row
    assert(mBe3[1][0] == 0.0);
    assert(mBe3[1][1] == 1.0);
    assert(mBe3[1][2] == 0.0);
    // Third row
    assert(mBe3[2][0] == 0.0);
    assert(mBe3[2][1] == 0.0);
    assert(mBe3[2][2] == 1.0);
    std::cout << "Test of brace-enclosed constructor with less arguments than needed is Ok." << std::endl;


    // =================
    // Auxiliary methods

      // get_ptr
    Vec3D* tab = mBe.get_ptr();
    // First row
    assert(mBe[0][0] == tab[0][0]);
    assert(mBe[0][1] == tab[0][1]);
    assert(mBe[0][2] == tab[0][2]);
    // Second row
    assert(mBe[1][0] == tab[1][0]);
    assert(mBe[1][1] == tab[1][1]);
    assert(mBe[1][2] == tab[1][2]);
    // Third row
    assert(mBe[2][0] == tab[2][0]);
    assert(mBe[2][1] == tab[2][1]);
    assert(mBe[2][2] == tab[2][2]);
    std::cout << "Test of getPtr() is Ok." << std::endl;

      // toString
    std::string mBe_str = mBe.toString();
    std::stringstream str_ctrl;
    str_ctrl << "Matrix : " << std::endl;
    str_ctrl << "\t[1, 0, 0]," << std::endl;
    str_ctrl << "\t[0, 1, 0]," << std::endl;
    str_ctrl << "\t[0, 0, 1]" << std::endl;
    assert(mBe_str == str_ctrl.str());

    // ==================
    // Operators overload

      // Test of operator [] (set)
    Vec3D tempArray = {1.0, 1.0, 1.0};
    Vec3D tempArray2 = {0.0, 0.0, 0.0};
    mDe[0] = tempArray;
    assert(mDe[0]==tempArray);
      // Test of operator [] (get)
    assert(mDe[1] == tempArray2);
    std::cout << "Test of operator [] is Ok." << std::endl;

      // Test of operator * with two matrices
    Matrix33D mMultTest = {{2.0, 2.0, 0.0}, {2.0, 2.0, 0.0}, {0.0, 0.0, 1.0}};
    mMultTest = mBe * mMultTest;
    // First row
    assert(mMultTest[0][0] == 2.0);
    assert(mMultTest[0][1] == 2.0);
    assert(mMultTest[0][2] == 0.0);
    // Second row
    assert(mMultTest[1][0] == 2.0);
    assert(mMultTest[1][1] == 2.0);
    assert(mMultTest[1][2] == 0.0);
    // Third row
    assert(mMultTest[2][0] == 0.0);
    assert(mMultTest[2][1] == 0.0);
    assert(mMultTest[2][2] == 1.0);
    std::cout << "Test of operator * with two matrices is Ok." << std::endl;

      // Test of operator * with a matrix and a Vec3D (i.e application of the matrix to a Vec3D)
    Vec3D vecMult = {2.0, 2.0, 1.0};
    mMultTest = {{2.0, 0.0, 0.0}, {0.0, 2.0, 0.0}, {0.0, 0.0, 1.0}};
    vecMult = mMultTest * vecMult;
    assert(vecMult[0] == 4);
    assert(vecMult[1] == 4);
    assert(vecMult[2] == 1);
    std::cout << "Test of operator * with a matrice and a vector 3D is Ok." << std::endl;

      // Test of operator * with a matrix and a Vec2D (i.e application of the matrix to a Vec2D)
    Vec2D vecMult2 = {2.0, 2.0};
    mMultTest = {{2.0, 0.0, 0.0}, {0.0, 2.0, 0.0}, {0.0, 0.0, 1.0}};
    vecMult2 = mMultTest * vecMult2;
    assert(vecMult2[0] == 4);
    assert(vecMult2[1] == 4);
    std::cout << "Test of operator * with a matrice and a vector 2D is Ok." << std::endl;

      // Test of operator * with a matrix and a scalar
    double scalar = 2.0;
    mMultTest = {{2.0, 2.0, 0.0}, {2.0, 2.0, 0.0}, {0.0, 0.0, 1.0}};
    mMultTest = mMultTest * scalar;
    assert(mMultTest[0][0] == 4.0);
    assert(mMultTest[0][1] == 4.0);
    assert(mMultTest[0][2] == 0.0);
    // Second row
    assert(mMultTest[1][0] == 4.0);
    assert(mMultTest[1][1] == 4.0);
    assert(mMultTest[1][2] == 0.0);
    // Third row
    assert(mMultTest[2][0] == 0.0);
    assert(mMultTest[2][1] == 0.0);
    assert(mMultTest[2][2] == 2.0);
    std::cout << "Test of operator * with a matrice and a scalar is Ok." << std::endl;


    // =======================
    // Matrix creation methods

      // identity
    Matrix33D miD = Matrix33D::identity();
    // First row
    assert(miD[0][0] == 1.0);
    assert(miD[0][1] == 0.0);
    assert(miD[0][2] == 0.0);
    // Second row
    assert(miD[1][0] == 0.0);
    assert(miD[1][1] == 1.0);
    assert(miD[1][2] == 0.0);
    // Third row
    assert(miD[2][0] == 0.0);
    assert(miD[2][1] == 0.0);
    assert(miD[2][2] == 1.0);
    std::cout << "Test of Matrix33D::identity is Ok." << std::endl;

      // inverse
    Matrix33D mInv = {{1.0, 2.0, 3.0}, {1.0, 1.0, 0.0}, {3.0, 2.0, 1.0}};
    Matrix33D mInv2 = mInv.inverse();
    Matrix33D temp = mInv * mInv2;
    // First row
    assert(miD[0][0] == temp[0][0]);
    assert(miD[0][1] == temp[0][1]);
    assert(miD[0][2] == temp[0][2]);
    // Second row
    assert(miD[1][0] == temp[1][0]);
    assert(miD[1][1] == temp[1][1]);
    assert(miD[1][2] == temp[1][2]);
    // Third row
    assert(miD[2][0] == temp[2][0]);
    assert(miD[2][1] == temp[2][1]);
    assert(miD[2][2] == temp[2][2]);
    std::cout << "Test of Matrix33D::inverse is Ok." << std::endl;

      // translation
    Matrix33D matTrans = Matrix33D::translation(2.0, 2.0);
    // First row
    assert(matTrans[0][0] == 1.0);
    assert(matTrans[0][1] == 0.0);
    assert(matTrans[0][2] == 2.0);
    // Second row
    assert(matTrans[1][0] == 0.0);
    assert(matTrans[1][1] == 1.0);
    assert(matTrans[1][2] == 2.0);
    // Third row
    assert(matTrans[2][0] == 0.0);
    assert(matTrans[2][1] == 0.0);
    assert(matTrans[2][2] == 1.0);
    std::cout << "Test of Matrix33D::translation is Ok." << std::endl;

      // Rotation
    Matrix33D matRot = Matrix33D::rotation(35.0);
    double cosAlpha = std::cos(35.0);
    double sinAlpha = std::sin(35.0);
    // First row
    assert(matRot[0][0] == cosAlpha);
    assert(matRot[0][1] == -sinAlpha);
    assert(matRot[0][2] == 0.0);
    // Second row
    assert(matRot[1][0] == sinAlpha);
    assert(matRot[1][1] == cosAlpha);
    assert(matRot[1][2] == 0.0);
    // Third row
    assert(matRot[2][0] == 0.0);
    assert(matRot[2][1] == 0.0);
    assert(matRot[2][2] == 1.0);
    std::cout << "Test of Matrix33D::rotation is Ok." << std::endl;

      // scale
    Matrix33D matScl = Matrix33D::scale(10.0, 5.0);
    // First row
    assert(matScl[0][0] == 10.0);
    assert(matScl[0][1] == 0.0);
    assert(matScl[0][2] == 0.0);
    // Second row
    assert(matScl[1][0] == 0.0);
    assert(matScl[1][1] == 5.0);
    assert(matScl[1][2] == 0.0);
    // Third row
    assert(matScl[2][0] == 0.0);
    assert(matScl[2][1] == 0.0);
    assert(matScl[2][2] == 1.0);
    std::cout << "Test of Matrix33D::scale is Ok." << std::endl;

    // ==========================
    // Matrix composition methods

      // translate (with a translate matrix given)
    Matrix33D matTranslate = Matrix33D::identity();
    matTranslate.translate(matTrans);
    // First row
    assert(matTranslate[0][0] == matTrans[0][0]);
    assert(matTranslate[0][1] == matTrans[0][1]);
    assert(matTranslate[0][2] == matTrans[0][2]);
    // Second row
    assert(matTranslate[1][0] == matTrans[1][0]);
    assert(matTranslate[1][1] == matTrans[1][1]);
    assert(matTranslate[1][2] == matTrans[1][2]);
    // Third row
    assert(matTranslate[2][0] == matTrans[2][0]);
    assert(matTranslate[2][1] == matTrans[2][1]);
    assert(matTranslate[2][2] == matTrans[2][2]);
      // translate (with the creation of the matrix)
    matTranslate = Matrix33D::identity();
    matTranslate.translate(2.0, 2.0);
    // First row
    assert(matTranslate[0][0] == 1.0);
    assert(matTranslate[0][1] == 0.0);
    assert(matTranslate[0][2] == 2.0);
    // Second row
    assert(matTranslate[1][0] == 0.0);
    assert(matTranslate[1][1] == 1.0);
    assert(matTranslate[1][2] == 2.0);
    // Third row
    assert(matTranslate[2][0] == 0.0);
    assert(matTranslate[2][1] == 0.0);
    assert(matTranslate[2][2] == 1.0);
    std::cout << "Test of Matrix33D::translate is Ok." << std::endl;

      // rotate (with a rotation matrix given)
    Matrix33D matrotate = Matrix33D::identity();
    matrotate.rotate(matRot);
    // First row
    assert(matrotate[0][0] == matRot[0][0]);
    assert(matrotate[0][1] == matRot[0][1]);
    assert(matrotate[0][2] == matRot[0][2]);
    // Second row
    assert(matrotate[1][0] == matRot[1][0]);
    assert(matrotate[1][1] == matRot[1][1]);
    assert(matrotate[1][2] == matRot[1][2]);
    // Third row
    assert(matrotate[2][0] == matRot[2][0]);
    assert(matrotate[2][1] == matRot[2][1]);
    assert(matrotate[2][2] == matRot[2][2]);
      // translate (with the creation of the matrix)
    matrotate = Matrix33D::identity();
    matrotate.rotate(35.0);
    // First row
    assert(matrotate[0][0] == cosAlpha);
    assert(matrotate[0][1] == -sinAlpha);
    assert(matrotate[0][2] == 0.0);
    // Second row
    assert(matrotate[1][0] == sinAlpha);
    assert(matrotate[1][1] == cosAlpha);
    assert(matrotate[1][2] == 0.0);
    // Third row
    assert(matrotate[2][0] == 0.0);
    assert(matrotate[2][1] == 0.0);
    assert(matrotate[2][2] == 1.0);
    std::cout << "Test of Matrix33D::rotate is Ok." << std::endl;

      // addScale (with a given scale matrix)
    Matrix33D matScale = Matrix33D::identity();
    matScale.rotate(matScl);
    // First row
    assert(matScl[0][0] == matScale[0][0]);
    assert(matScl[0][1] == matScale[0][1]);
    assert(matScl[0][2] == matScale[0][2]);
    // Second row
    assert(matScl[1][0] == matScale[1][0]);
    assert(matScl[1][1] == matScale[1][1]);
    assert(matScl[1][2] == matScale[1][2]);
    // Third row
    assert(matScl[2][0] == matScale[2][0]);
    assert(matScl[2][1] == matScale[2][1]);
    assert(matScl[2][2] == matScale[2][2]);
      // translate (with the creation of the matrix)
    matScale = Matrix33D::identity();
    matScale.addScale(10.0, 5.0);
    // First row
    assert(matScale[0][0] == 10.0);
    assert(matScale[0][1] == 0.0);
    assert(matScale[0][2] == 0.0);
    // Second row
    assert(matScale[1][0] == 0.0);
    assert(matScale[1][1] == 5.0);
    assert(matScale[1][2] == 0.0);
    // Third row
    assert(matScale[2][0] == 0.0);
    assert(matScale[2][1] == 0.0);
    assert(matScale[2][2] == 1.0);
    std::cout << "Test of Matrix33D::addScale is Ok." << std::endl;

    // =============
    // Apply methods

      // applyTransformation
    vecMult2 = {2.0, 2.0};
    mMultTest = {{2.0, 0.0, 0.0}, {0.0, 2.0, 0.0}, {0.0, 0.0, 1.0}};
    Vec2D vecMult3 = mMultTest.applyTransformation(vecMult2[0], vecMult2[1]);
    assert(vecMult2[0] == 4);
    assert(vecMult2[1] == 4);
    assert(vecMult3[0] == 4);
    assert(vecMult3[1] == 4);
    std::cout << "Test of matrix33D::applyTransformation is Ok." << std::endl;

	return 0;
}
