#ifndef __PROJECTVECTORS_H_
#define __PROJECTVECTORS_H_

#include "Array.hpp"

/**
 * @brief The ProjectVector class
 */
template<typename T, int N>
class ProjectVector : public Array<T, N>
{
// Constructor and destructor
public:
    /**
     * @brief ProjectVector constructor without arguments. Initialize all data members to T{0}
     */
    ProjectVector();


    /**
     * @brief ProjectVector constructor with brace-enclosed initilization. Initialize data members with given values or T{0} if unknown
     * @param elements
     */
    ProjectVector(std::initializer_list<T> elements);

// Methods
public:

    /**
     * @brief norm return the norm of the vector
     * @return
     */
    T& norm();


// Operators overload
public:
    // Operators with two vectors (+, -, +=, -=)

    /**
     * @brief operator + overload of the addition operator with two vectors
     * @param leftHandObj left hand object of the operation
     * @param rightHandObj right hand object of the operation
     * @return
     */
    ProjectVector<T,N>& operator+(const ProjectVector<T,N>& rightHandObj);


    /**
     * @brief operator - overload of the substraction operator with two vectors
     * @param leftHandObj left hand object of the operation
     * @param rightHandObj right hand object of the operation
     * @return
     */
    ProjectVector<T,N>& operator-(const ProjectVector<T,N>& rightHandObj);


    /**
     * @brief operator += overload of the += operator with two vectors
     * @param rightHandObj right hand object of the operation
     * @return
     */
    ProjectVector<T,N>& operator+=(const ProjectVector<T,N>& rightHandObj);


    /**
     * @brief operator -= overload of the -= operator with two vectors
     * @param rightHandObj right hand object of the operation
     * @return
     */
    ProjectVector<T,N>& operator-=(const ProjectVector<T,N>& rightHandObj);


    // Scalar product (*)

    /**
     * @brief operator * overload for scalar product
     * @param leftHandObj left hand object of the operation
     * @param rightHandObj right hand object of the operation
     * @return
     */
     T& operator*(const ProjectVector<T,N>& rightHandObj);


    // Operators with a vector and a scalar (*, /, *=, /=)

    /**
     * @brief operator * overload for multiplication with one vector and one scalar
     * @param scalar
     * @return
     */
    ProjectVector<T,N>& operator*(const T& scalar);


    /**
     * @brief operator / overload for division with one vector and one scalar
     * @param scalar
     * @return
     */
    ProjectVector<T,N>& operator/(const T& scalar);


    /**
     * @brief operator *= overload for *= with one vector and one scalar
     * @param scalar
     * @return
     */
    ProjectVector<T,N>& operator*=(const T& scalar);


    /**
     * @brief operator /= overload for /= with one vector and one scalar
     * @param scalar
     * @return
     */
    ProjectVector<T,N>& operator/=(const T& scalar);

};


// Overload of the multiplication operator for the case T * ProjectVector<T,N>
/**
 * @brief operator * overload of the multiplication operator for the case T * ProjectVector<T,N>
 * @return
 */
template<typename T, int N>
ProjectVector<T,N>& operator*(const T& scalar, const ProjectVector<T,N>& vector);


/**
 * @brief The Vec2T class
 */
template<typename T>
class Vec2T : public ProjectVector<T, 2>
{
public:
    /**
     * @brief Vec2T constructor without arguments. Initialize all data members to T{0}
     */
    Vec2T() : ProjectVector<T,2>() {}

    /**
     * @brief Vec2T constructor with brace-enclosed initilization. Initialize data members with given values or T{0} if unknown
     * @param elements
     */
    Vec2T(std::initializer_list<T> elements) : ProjectVector<T,2>(elements) {}

public:
    /**
     * @brief cross return the cross product with the given vector
     * @param other
     * @return
     */
    T& cross(const Vec2T<T>& other);
};


/**
 * @brief The Vec3T class
 */
template<typename T>
class Vec3T : public ProjectVector<T, 3>
{
public:
    /**
     * @brief Vec3T constructor without arguments. Initialize all data members to T{0}
     */
    Vec3T() : ProjectVector<T,3>() {}


    /**
     * @brief Vec3T constructor with brace-enclosed initilization. Initialize data members with given values or T{0} if unknown
     * @param elements
     */
    Vec3T(std::initializer_list<T> elements) : ProjectVector<T,3>(elements) {}

public:
    /**
     * @brief norm return the norm of the vector
     * @return
     */
    T& norm();


    /**
     * @brief cross return the cross product with the given vector
     * @param other
     * @return
     */
    Vec3T<T> cross(const Vec3T<T>& other);
};


/**
 * @brief The Vec2I class
 */
class Vec2I : public Vec2T<int>
{
public:
    /**
     * @brief Vec2I constructor without arguments. Initialize all data members to 0
     */
    Vec2I() : Vec2T() {}


    /**
     * @brief Vec2I constructor with brace-enclosed initilization. Initialize data members with given values or 0 if unknown
     * @param elements
     */
    Vec2I(std::initializer_list<int> elements) : Vec2T<int>(elements) {}
};


/**
 * @brief The Vec2F class
 */
class Vec2F : public Vec2T<float>
{
public:
    /**
     * @brief Vec2F constructor without arguments. Initialize all data members to 0.0f
     */
    Vec2F() : Vec2T() {}


    /**
     * @brief Vec2F constructor with brace-enclosed initilization. Initialize data members with given values or 0.0f if unknown
     * @param elements
     */
    Vec2F(std::initializer_list<float> elements) : Vec2T<float>(elements) {}
};


/**
 * @brief The Vec3I class
 */
class Vec3I : public Vec3T<int>
{
public:
    /**
     * @brief Vec3I constructor without arguments. Initialize all data members to 0
     */
    Vec3I() : Vec3T() {}


    /**
     * @brief Vec3I constructor with brace-enclosed initilization. Initialize data members with given values or 0 if unknown
     * @param elements
     */
    Vec3I(std::initializer_list<int> elements) : Vec3T<int>(elements) {}
};


/**
 * @brief The Vec3F class
 */
class Vec3F : public Vec3T<float>
{
public:
    /**
     * @brief Vec3F constructor without arguments. Initialize all data members to 0.0f
     */
    Vec3F() : Vec3T<float>() {}


    /**
     * @brief Vec3F constructor with brace-enclosed initilization. Initialize data members with given values or 0.0f if unknown
     * @param elements
     */
    Vec3F(std::initializer_list<float> elements) : Vec3T<float>(elements) {}
};


/**
 * @brief The Vec4I class
 */
class Vec4I : public ProjectVector<int,4>
{
public:
    /**
     * @brief Vec3F constructor without arguments. Initialize all data members to 0
     */
    Vec4I() : ProjectVector<int,4>() {}


    /**
     * @brief Vec3F constructor with brace-enclosed initilization. Initialize data members with given values or 0 if unknown
     * @param elements
     */
    Vec4I(std::initializer_list<int> elements) : ProjectVector<int,4>(elements) {}
};


/**
 * @brief The Vec4F class
 */
class Vec4F : public ProjectVector<float,4>
{
public:
    /**
     * @brief Vec3F constructor without arguments. Initialize all data members to 0.0f
     */
    Vec4F() : ProjectVector<float,4>() {}


    /**
     * @brief Vec3F constructor with brace-enclosed initilization. Initialize data members with given values or 0.0f if unknown
     * @param elements
     */
    Vec4F(std::initializer_list<float> elements) : ProjectVector<float,4>(elements) {}
};

#endif
