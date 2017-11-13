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
        else
        {
            return;
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
    T *tempElem;
    int i = 0;

    for(i=0; i<N; i++)
    {
        tempElem = this->get_ptr();
        this->data[i] = other[i];
        other[i] = tempElem[i];
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


// External operator from class Array

template<typename T, int N>
std::ostream& operator<<(std::ostream& os, Array<T,N>& obj)
{
    os << obj.toString();
    return os;
}


template<typename T, int N>
std::istream& operator>>(std::istream& is, Array<T,N>& obj)
{
    obj.toString() >> is;
    return is;
}


// -----------------------------
//      Class DynamicArray


template<typename T>
DynamicArray<T>::DynamicArray()
{
    this->nb_elements = 0;
    this->data = nullptr;
}


template<typename T>
DynamicArray<T>::DynamicArray(const unsigned int size)
{
    unsigned int i = 0;
    this->nb_elements = size;
    this->data = new T[size];

    for(i=0; i<this->nb_elements; i++)
    {
        T elem = T{0};
        this->data[i] = elem;
    }
}


template<typename T>
DynamicArray<T>::DynamicArray(std::initializer_list<T> elements)
{
    int i = 0;
    this->nb_elements = elements.size();
    this->data = new T[this->nb_elements];

    for(auto it = elements.begin(); it != elements.end(); ++it)
    {
        this->data[i] = *it;
        i++;
    }
}


template<typename T>
DynamicArray<T>::~DynamicArray()
{

}


// Methods

template<typename T>
std::string DynamicArray<T>::toString()
{
    std::stringstream strArray;
    unsigned int i = 0;

    strArray << "[";

    for(i=0; i<(this->nb_elements-1); i++)
    {
        bool b2;
        bool b;
        if (( b = std::is_same<T, unsigned char>::value == 1) || (b2 = std::is_same<T, char>::value == 1))
        {
            strArray << (int)this->data[i] << ", ";
        }
        else
        {
            strArray << this->data[i] << ", ";
        }
    }
    if ((std::is_same<T, unsigned char>::value) || (std::is_same<T, char>::value))
    {
        strArray << (int)this->data[this->nb_elements-1] << "]";
    }
    else
    {
        strArray << this->data[this->nb_elements-1] << "]";
    }
    return strArray.str();
}


template<typename T>
unsigned int DynamicArray<T>::size()
{
    return this->nb_elements;
}


template<typename T>
T* DynamicArray<T>::getPtr()
{
    return this->data;
}


// Operator

template<typename T>
T DynamicArray<T>::operator[](int i) const
{
    return this->data[i];
}


template<typename T>
T& DynamicArray<T>::operator[](int i)
{
    return this->data[i];
}


template<typename T>
DynamicArray<T>& DynamicArray<T>::operator=( DynamicArray<T>& other)
{
    if(this != &other)
    {
        if(this->size() != other.size())
        {
            if(this->nb_elements != 0)
            {
                delete[] this->data;
            }
            this->nb_elements = 0;
            this->data = nullptr;
            this->data = new T[other.size()];
            this->nb_elements = other.size();
        }
    }
    std::copy(other.getPtr(), other.getPtr() + other.size(), this->data);

    return *this;
}


// External operator from class Array

template<typename T>
std::ostream& operator<<(std::ostream& os, DynamicArray<T>& obj)
{
    os << obj.toString();
    return os;
}

#endif
