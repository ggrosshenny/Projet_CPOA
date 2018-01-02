#ifndef __MATRIX33D_H_
#define __MATRIX33D_H_

#include "ProjectVectors.hpp"
#include <sstream>

class Matrix33D
{
// Attributes
protected:
    Vec3D data[3];

// Constructors and destructors
public:

    /**
     * @brief Matrix33D constructor without arguments. Initialize all members to 0.0
     */
    Matrix33D();


    /**
     * @brief Matrix33D constructor with brace-enclosed initilization. Initialize data members with given values or 0.0 if unknown
     * @param elements
     */
    Matrix33D(std::initializer_list<std::initializer_list<double>> elements);

// Auxiliary methods
public:

    /**
     * @brief get_ptr return the data enclosed by the class Matrix33D
     * @return
     */
    Vec3D* get_ptr();


    /**
     * @brief toString return a string representation of the matrix
     * @return
     */
    std::string toString();


// Operator overload
public:

    /**
     * @brief operator [] overload of the accessor (get) operator
     * @param i
     * @return
     */
    Vec3D operator[](int i)const;


    /**
     * @brief operator [] overload of the accessor (set) operator
     * @param i
     * @return
     */
    Vec3D& operator[](int i);


    /**
     * @brief operator * overload for multiplication with two matrices
     * @param rightHandObj
     * @return
     */
    Matrix33D operator*(const Matrix33D& rightHandObj);


    /**
     * @brief operator * overload for multiplication with a scalar
     * @param scalar
     * @return
     */
    Matrix33D operator*(const double& scalar);


    /**
     * @brief operator == overload for the == operator
     * @param other
     * @return
     */
    bool operator==(const Matrix33D& other);


// transformations
public:


    /**
     * @brief identity return the identity matrix
     * @return
     */
    static Matrix33D identity();


    /**
     * @brief inverse return the invert of the Matrix
     * @return
     */
    Matrix33D inverse();


    /**
     * @brief translation create and return the translation matrix
     * @return
     */
    static Matrix33D translation(double tx, double ty);


    /**
     * @brief rotation create and return the rotation matrix
     * @return
     */
    static Matrix33D rotation(double angle);


    /**
     * @brief scale create and return the scale matrix
     * @return
     */
    static Matrix33D scale(double hx, double hy);


    /**
     * @brief translate compose the actual transformation matrix with the given translate matrix
     * @param translateMatrix
     * @return
     */
    Matrix33D& translate(Matrix33D& translateMatrix);


    /**
     * @brief translate create the translation matrix and return the composition of the actual transformation matrix and the created translation matrix
     * @param tx
     * @param ty
     * @return
     */
    Matrix33D& translate(double tx, double ty);


    /**
     * @brief rotate compose the actual transformation matrix with the given rotation matrix
     * @param rotation
     * @return
     */
    Matrix33D& rotate(Matrix33D& rotationMatrix);


    /**
     * @brief rotate create the rotation matrix and return the composition of the actual transformation matrix and the created rotation matrix
     * @param angle
     * @return
     */
    Matrix33D& rotate(double angle);


    /**
     * @brief addScale compose the actual transformation matrix with the given homothetie matrix
     * @param homothetie
     * @return
     */
    Matrix33D& addScale(Matrix33D& scaleMatrix);


    /**
     * @brief addScale create the homothetie matrix and return the composition of the actual transformation matrix and the created homothetie matrix
     * @param hx
     * @param hy
     * @return
     */
    Matrix33D& addScale(double hx, double hy);


// Application of transformations
public:

    Vec3D operator*(Vec3D& vector);

    Vec2D operator*(Vec2D& vector);

    Vec2D applyTransformation(double& x, double& y);
};

// External operator from class

inline std::ostream& operator<<(std::ostream& os, Matrix33D& obj)
{
    os << obj.toString();
    return os;
}

inline Vec2D operator*(Vec2D& vec, Matrix33D& matr)
{
    return matr * vec;
}

#endif
