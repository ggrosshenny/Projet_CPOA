#ifndef __PROJECTVECTOR_HPP_
#define __PROJECTVECTOR_HPP_

#include "ProjectVectors.h"
#include <cmath>


/**
 * ==============================
 *     Class : ProjectVector
 * ==============================
 */


template<typename T, int N>
ProjectVector<T,N>::ProjectVector() : Array<T,N>()
{
}


template<typename T, int N>
ProjectVector<T,N>::ProjectVector(std::initializer_list<T> elems) : Array<T,N>(elems)
{

}


// -------------------
// Methods on a vector


template<typename T, int N>
T& ProjectVector<T,N>::norm()
{
    return std::sqrt(*this * *this);
}


// ---------------------------
// Operations with two vectors


template<typename T, int N>
ProjectVector<T,N>& ProjectVector<T,N>::operator+(const ProjectVector<T,N>& rightHandObj)
{
    ProjectVector<T,N> answ;
    int i = 0;

    for(i=0; i<N; i++)
    {
        answ.data[i] = this->data[i] + rightHandObj[i];
    }

    return answ;
}


template<typename T, int N>
ProjectVector<T,N>& ProjectVector<T,N>::operator-(const ProjectVector<T,N>& rightHandObj)
{
    ProjectVector<T,N> answ;
    int i = 0;

    for(i=0; i<N; i++)
    {
        answ.data[i] = this->data[i] - rightHandObj[i];
    }

    return answ;
}


template<typename T, int N>
ProjectVector<T,N>& ProjectVector<T,N>::operator+=(const ProjectVector<T,N>& rightHandObj)
{
    int i = 0;

    for(i=0; i<N; i++)
    {
        this->data[i] = this->data[i] + rightHandObj[i];
    }

    return *this;
}


template<typename T, int N>
ProjectVector<T,N>& ProjectVector<T,N>::operator-=(const ProjectVector<T,N>& rightHandObj)
{
    int i = 0;

    for(i=0; i<N; i++)
    {
        this->data[i] = this->data[i] - rightHandObj[i];
    }

    return *this;
}


template<typename T, int N>
T ProjectVector<T,N>::operator*(const ProjectVector<T,N>& rightHandObj)
{
    T answ = T(0);
    int i = 0;
    for(i=0; i<N; i++)
    {
        answ += this->data[i] * rightHandObj.data[i];
    }

    return answ;
}


// -------------------------------------
// Operations with a vector and a scalar


// Vector * T
template<typename T, int N>
ProjectVector<T,N> ProjectVector<T,N>::operator*(const T& scalar)
{
    ProjectVector<T,N> answ;
    int i = 0;
    for(i=0; i<N; i++)
    {
        answ[i] = this->data[i] * scalar;
    }

    return answ;
}


// T * Vector
template<typename T, int N>
ProjectVector<T,N> operator*(const T& scalar, const ProjectVector<T,N>& vector)
{
    ProjectVector<T,N> answ;
    int i = 0;
    for(i=0; i<N; i++)
    {
        answ[i] = vector[i] * scalar;
    }

    return answ;
}


template<typename T, int N>
ProjectVector<T,N>& ProjectVector<T,N>::operator/(const T& scalar)
{
    ProjectVector<T,N> answ;
    int i = 0;
    for(i=0; i<N; i++)
    {
        answ[i] = this->data[i] / scalar;
    }

    return answ;
}


template<typename T, int N>
ProjectVector<T,N>& ProjectVector<T,N>::operator*=(const T& scalar)
{
    int i = 0;
    for(i=0; i<N; i++)
    {
        this->data[i] = this->data[i] * scalar;
    }

    return *this;
}


template<typename T, int N>
ProjectVector<T,N>& ProjectVector<T,N>::operator/=(const T& scalar)
{
    int i = 0;
    for(i=0; i<N; i++)
    {
        this->data[i] = this->data[i] / scalar;
    }

    return *this;
}



/**
 * ==============================
 *         Class : Vec2T
 * ==============================
 */


template<typename T>
T Vec2T<T>::cross(Vec2T<T> &other)
{
    T answ = (this->data[0] * other[1]) - (this->data[1] * other[0]);
    return answ;
}


/**
 * ==============================
 *         Class : Vec3T
 * ==============================
 */

template<typename T>
Vec3T<T> Vec3T<T>::cross(const Vec3T<T>& other)
{
    Vec3T<T> answ;

    // x = y1*z2 - z1*y2
    answ[0] = (this->data[1] * other[2]) - (this->data[2] * other[1]);
    // y = z1*x2 - x1*z2
    answ[1] = (this->data[2] * other[0]) - (this->data[0] * other[2]);
    // z = x1*y2 - y1*x2
    answ[2] = (this->data[0] * other[1]) - (this->data[1] * other[0]);

    return answ;
}


#endif
