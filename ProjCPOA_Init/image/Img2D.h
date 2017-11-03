#ifndef __IMG2D_H_
#define __IMG2D_H_

#include <iostream>
#include <cstdlib>
#include "../vectorMatrix/Array.hpp"


template<typename T>
class Img2D
{
protected:
    DynamicArray<DynamicArray<T>> data;
    unsigned int width;
    unsigned int height;

// Constructors and destructors
public:

    /**
     * @brief Img2D constructor without arguments. Dynamic allocation of an image of 256 * 256 pixels
     */
    Img2D();


    /**
     * @brief Img2D constructor with arguments. Dynamic allocation of an image of x * y pixels
     * @param x width of the image
     * @param y height of the image
     */
    Img2D(int height0, int width0);


    /**
     * @brief Img2D
     * @param elements
     */
    Img2D(std::initializer_list<std::initializer_list<T>> elements);


    ~Img2D();

// operator overload
public:

    /**
     * @brief operator [] overload of the accessor (get) operator
     * @param i
     * @return
     */
    DynamicArray<T> operator[](int i) const;


    /**
     * @brief operator [] overload of the accessor (set) operator
     * @param i
     * @return
     */
    DynamicArray<T>& operator[](int i);
};



#endif
