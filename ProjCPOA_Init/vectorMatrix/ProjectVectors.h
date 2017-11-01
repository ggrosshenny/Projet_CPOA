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
     T operator*(const ProjectVector<T,N>& rightHandObj);


    // Operators with a vector and a scalar (*, /, *=, /=)

    /**
     * @brief operator * overload for multiplication with one vector and one scalar
     * @param scalar
     * @return
     */
    ProjectVector<T,N> operator*(const T& scalar);


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
ProjectVector<T,N> operator*(const T& scalar, const ProjectVector<T,N>& vector);


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
     * @brief Vec2I Constructor for cast from Vec2T<int> to Vec2I (used for usage of mother class methods)
     * @param vec
     */
    Vec2I(Vec2T<int> vec) : Vec2T<int>()
    {
        data[0] = vec[0];
        data[1] = vec[1];
    }

    /**
     * @brief Vec2I Constructor for cast from ProjectVector<int, 2> to Vec2I (used for usage of mother class methods)
     * @param vec
     */
    Vec2I(ProjectVector<int, 2> vec) : Vec2T<int>()
    {
        data[0] = vec[0];
        data[1] = vec[1];
    }


    /**
     * @brief Vec2I constructor with brace-enclosed initilization. Initialize data members with given values or 0 if unknown
     * @param elements
     */
    Vec2I(std::initializer_list<int> elements) : Vec2T<int>(elements) {}
};


/**
 * @brief The Vec2D class
 */
class Vec2D : public Vec2T<double>
{
public:
    /**
     * @brief Vec2D constructor without arguments. Initialize all data members to 0.0f
     */
    Vec2D() : Vec2T() {}


    /**
     * @brief Vec2D Constructor for cast from Vec2T<double> to Vec2D (used for usage of mother class methods)
     * @param vec
     */
    Vec2D(Vec2T<double> vec) : Vec2T<double>()
    {
        data[0] = vec[0];
        data[1] = vec[1];
    }

    /**
     * @brief Vec2D Constructor for cast from ProjectVector<double, 2> to Vec2D (used for usage of mother class methods)
     * @param vec
     */
    Vec2D(ProjectVector<double, 2> vec) : Vec2T<double>()
    {
        data[0] = vec[0];
        data[1] = vec[1];
    }


    /**
     * @brief Vec2D constructor with brace-enclosed initilization. Initialize data members with given values or 0.0f if unknown
     * @param elements
     */
    Vec2D(std::initializer_list<double> elements) : Vec2T<double>(elements) {}
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
     * @brief Vec3I Constructor for cast from Vec3T<int> to Vec3I (used for usage of mother class methods)
     * @param vec
     */
    Vec3I(Vec3T<int> vec) : Vec3T<int>()
    {
        data[0] = vec[0];
        data[1] = vec[1];
        data[2] = vec[2];
    }

    /**
     * @brief Vec3I Constructor for cast from ProjectVector<int, 3> to Vec3I (used for usage of mother class methods)
     * @param vec
     */
    Vec3I(ProjectVector<int, 3> vec) : Vec3T<int>()
    {
        data[0] = vec[0];
        data[1] = vec[1];
        data[2] = vec[2];
    }


    /**
     * @brief Vec3I constructor with brace-enclosed initilization. Initialize data members with given values or 0 if unknown
     * @param elements
     */
    Vec3I(std::initializer_list<int> elements) : Vec3T<int>(elements) {}
};


/**
 * @brief The Vec3D class
 */
class Vec3D : public Vec3T<double>
{
public:
    /**
     * @brief Vec3D constructor without arguments. Initialize all data members to 0.0f
     */
    Vec3D() : Vec3T<double>() {}

    /**
     * @brief Vec3D Constructor for cast from Vec3T<double> to Vec3D (used for usage of mother class methods)
     * @param vec
     */
    Vec3D(Vec3T<double> vec) : Vec3T<double>()
    {
        data[0] = vec[0];
        data[1] = vec[1];
        data[2] = vec[2];
    }

    /**
     * @brief Vec3D Constructor for cast from ProjectVector<double, 3> to Vec3D (used for usage of mother class methods)
     * @param vec
     */
    Vec3D(ProjectVector<double, 3> vec) : Vec3T<double>()
    {
        data[0] = vec[0];
        data[1] = vec[1];
        data[2] = vec[2];
    }


    /**
     * @brief Vec3D constructor with brace-enclosed initilization. Initialize data members with given values or 0.0f if unknown
     * @param elements
     */
    Vec3D(std::initializer_list<double> elements) : Vec3T<double>(elements) {}

public:

    Vec3D cross(const Vec3D &other);
};


/**
 * @brief The Vec4I class
 */
class Vec4I : public ProjectVector<int,4>
{
public:
    /**
     * @brief Vec4I constructor without arguments. Initialize all data members to 0
     */
    Vec4I() : ProjectVector<int,4>() {}


    /**
     * @brief Vec4I Constructor for cast from ProjectVector<int, 4> to Vec4I (used for usage of mother class methods)
     * @param vec
     */
    Vec4I(ProjectVector<int, 4> vec) : ProjectVector<int, 4>()
    {
        data[0] = vec[0];
        data[1] = vec[1];
        data[2] = vec[2];
        data[3] = vec[3];
    }


    /**
     * @brief Vec4I constructor with brace-enclosed initilization. Initialize data members with given values or 0 if unknown
     * @param elements
     */
    Vec4I(std::initializer_list<int> elements) : ProjectVector<int,4>(elements) {}
};


/**
 * @brief The Vec4D class
 */
class Vec4D : public ProjectVector<double,4>
{
public:
    /**
     * @brief Vec4D constructor without arguments. Initialize all data members to 0.0f
     */
    Vec4D() : ProjectVector<double,4>() {}


    /**
     * @brief Vec4D Constructor for cast from ProjectVector<double, 4> to Vec4D (used for usage of mother class methods)
     * @param vec
     */
    Vec4D(ProjectVector<double, 4> vec) : ProjectVector<double, 4>()
    {
        data[0] = vec[0];
        data[1] = vec[1];
        data[2] = vec[2];
        data[3] = vec[3];
    }


    /**
     * @brief Vec4D constructor with brace-enclosed initilization. Initialize data members with given values or 0.0f if unknown
     * @param elements
     */
    Vec4D(std::initializer_list<double> elements) : ProjectVector<double,4>(elements) {}
};

#endif
