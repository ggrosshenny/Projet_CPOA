#ifndef __ARRAY_HPP_
#define __ARRAY_HPP_

#include "Array.h"

template<typename T, int N>
Array<T, N>::Array()
{
    for(int i=0; i<N; i++)
    {
        this->data[i] = T(0);
    }
}


template<typename T, int N>
Array<T,N>::Array(std::initializer_list<T> il)
{
    for(int i=0; i<N; i++)
    {
        this->data[i] = T(0);
    }

    for(auto it = il.begin(); it != il.end(); ++it)
    {
        if(nb_elements < N)
        {
            data[nb_elements] = *it;
            nb_elements++;
        }
    }
}


template<typename T, int N>
T Array<T, N>::operator[](int i) const
{
    return this->data[i];
}


template<typename T, int N>
T& Array<T, N>::operator [](int i)
{
    return this->data[i];
}


template<typename T, int N>
T* Array<T,N>::get_ptr()
{
    return this->data;
}


template<typename T, int N>
void Array<T,N>::swapData(Array<T,N>& other)
{
    T tempElem;
    int i = 0;

    for(i=0; i<N; i++)
    {
        tempElem = *this[i];
        *this[i] = other[i];
        other[i] = tempElem;
    }
}


template<typename T, int N>
std::string Array<T,N>::toString()
{
    std::stringstream strArray;
    int i = 0;

    strArray << "[";

    for(i=0; i<(N-1); i++)
    {
        strArray << this->data[i] << ", ";
    }
    strArray << this->data[N-1] << "]";
    return strArray.str();
}


template<typename T, int N>
bool Array<T,N>::operator==(const Array<T,N>& rightHandElement)
{
    int i = 0;
    for(i=0; i<N; i++)
    {
        if(this->operator [](i) != rightHandElement[i])
        {
            return false;
        }
    }
    return true;
}


template<typename T, int N>
bool Array<T,N>::operator!=(const Array<T,N>& rightHandElement)
{
    return !(*this == rightHandElement);
}


template<typename T, int N>
Array<T,N>& Array<T,N>::operator=(const Array<T,N>& other)
{
    int i=0;
    if((*this != other))
    {
        for(i=0; i<N; i++)
        {
            this->data[i] = other.data[i];
        }
    }
    return *this;
}


// External operator from class

template<typename T, int N>
std::ostream& operator<<(std::ostream& os, Array<T,N>& obj)
{
    os << obj.toString();
    return os;
}

#endif
