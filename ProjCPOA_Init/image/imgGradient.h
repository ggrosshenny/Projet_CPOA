#ifndef __imgGradient_H_
#define __imgGradient_H__

#include <iostream>
#include "Img2DGrey.h"
#include "../vectorMatrix/ProjectVectors.h"

class imgGradient
{
public:
    int Sobel5x[25];
    int Sobel5y[25];

// Constructor
public:
    imgGradient() {}
    imgGradient(int gx[25], int gy[25]);
    imgGradient(std::initializer_list<std::initializer_list<int>> elements);

// Auxiliary methods
public:

    void applyConvolutionOnPixelAux(unsigned int pi, unsigned int pj, int in0, int jn0, const Img2DGrey& img, Vec2D& newPixel, unsigned int neighboorSize) const;


    /**
     * @brief applyConvolutionOnPixel Apply the convolution to the given pixel
     * @param pi Pixel i-coordinate
     * @param pj Pixel j-coordinate
     * @param img Input image
     * @param GradientImage output image
     * @param neighboorSize size of the convolution matrix
     */
    Vec2D applyConvolutionOnPixel(unsigned int pi, unsigned int pj, const Img2DGrey& img, unsigned int neighboorSize) const;

// Gradient methods
public:
    /**
     * @brief gradient33 Apply the sobel filter with a 3x3 convolution matrix
     * @param img_in
     * @return
     */
    Img2D<Vec2D> gradient33(const Img2DGrey& img_in);


    /**
     * @brief gradient55 Apply the sobel filter with a 5x5 convolution matrix
     * @param img_in
     * @return
     */
    Img2D<Vec2D> gradient55(const Img2DGrey& img_in);

};

#endif
