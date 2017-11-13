#ifndef __IMG2D_H_
#define __IMG2D_H_

#include <iostream>
#include <cstdlib>
#include <cmath>
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
     * @param height0 height of the image
     * @param width0 width of the image
     */
    Img2D(int height0, int width0);


    /**
     * @brief Img2D constructor with brace-enclosed initilization. Initialize data members with given values or T{0} if unknown
     * @param elements
     */
    Img2D(std::initializer_list<std::initializer_list<T>> elements);


    ~Img2D();

// Auxiliary methods
public:

    /**
     * @brief getHeight return the height of the image
     * @return
     */
    unsigned int getHeight()const;


    /**
     * @brief getWidth return the width of the image
     * @return
     */
    unsigned int getWidth() const;


    /**
     * @brief toString return a string version of the image
     * @return
     */
    std::string toString();


    /**
     * @brief reduceRatio return the reduced form of the ratios (where gcd(ratio_height, ratio_width) == 1)
     * @param ratio_height
     * @param ratio_width
     */
    static void reduceRatio(unsigned int *ratio_height, unsigned int *ratio_width);


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


    /**
     * @brief operator = overload of the affectation operator
     * @param other
     * @return
     */
    Img2D<T>& operator=(Img2D<T>& other);


// Image manipulation methods
public:


    /**
     * @brief swapImages swap the data of two images
     * @param other
     * @return
     */
    void swapImages(Img2D<T>& other);


    /**
     * @brief cropping return the croped image with the dimension of the given ratio
     * @param ratio_height
     * @param ratio_width
     * @return
     */
    Img2D<T> cropping(unsigned int ratio_height, unsigned int ratio_width);
};

#include "Img2D.hpp"



#endif
