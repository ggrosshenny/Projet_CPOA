#ifndef __IMG2D_HPP_
#define __IMG2D_HPP_

#include "Img2D.h"


// -----------------------------
// Constructors and desctructors


template<typename T>
Img2D<T>::Img2D()
{
    int i = 0;
    int j = 0;

    this->width = 256;
    this->height = 256;
    this->data = new DynamicArray<T>[height];

    for(i = 0; i<height; i++)
    {
        this->data[i] = DynamicArray<T>(width);
    }
}


template<typename T>
Img2D<T>::Img2D(int height0, int width0)
{
    unsigned int i = 0;

    this->width = width0;
    this->height = height0;
    DynamicArray<DynamicArray<T>> t = DynamicArray<DynamicArray<T>>(height0);
    this->data = t;

    for(i = 0; i<height; i++)
    {
        DynamicArray<T> tbis = DynamicArray<T>(width);
        this->data[i] = tbis;
    }
}


template<typename T>
Img2D<T>::~Img2D()
{

}


// -----------------
// Operator overload

template<typename T>
DynamicArray<T> Img2D<T>::operator[](int i) const
{
    return this->data[i];
}

template<typename T>
DynamicArray<T>& Img2D<T>::operator [](int i)
{
    return this->data[i];
}


#endif
