
#ifndef __IMG2DGREY_H_
#define __IMG2DGREY_H_

#include <Img2D.hpp>
#include <sstream>
#include <string>
#include <iostream>


class Img2DGrey : public Img2D<unsigned char>
{

// Constructors and destructors
public:

    /**
     * @brief Img2D constructor without arguments. Dynamic allocation of an image of 256 * 256 pixels
     */
    Img2DGrey() : Img2D<unsigned char>() {}


    /**
     * @brief Img2D constructor with arguments. Dynamic allocation of an image of x * y pixels
     * @param x width of the image
     * @param y height of the image
     */
    Img2DGrey(int height0, int width0) : Img2D<unsigned char>(height0, width0) {}


    /**
     * @brief Img2D constructor with brace-enclosed initilization. Initialize data members with given values or T{0} if unknown
     * @param elements
     */
    Img2DGrey(std::initializer_list<std::initializer_list<unsigned char>> elements) : Img2D<unsigned char>(elements) {}


// Auxiliary methods
public:


    /**
     * @brief applySmoothOnPixel Apply the smooth matrix of the given size on the given pixel of the given image
     * @param pi i coordinate of pixel
     * @param pj j coordinate of pixel
     * @param img image of the pixel
     */
    void applySmoothOnPixel(unsigned int pi, unsigned int pj, Img2DGrey& img, unsigned int neighboorSize) const;



// Image transformations methods
public:


    /**
     * @brief loadImageFromPGMFile load the image from PGM format file with the given file name
     * @param fileName file to read
     */
    void loadImageFromPGMFile(std::string fileName);


    /**
     * @brief saveImageToPGMFile save the image to PGM format in the file with the given file name
     * @param fileName file to write into
     */
    void saveImageToPGMFile(std::string fileName) const;


    /**
     * @brief subTileImage return a subtile image
     * @return
     */
    Img2DGrey subTileImage() const;


    /**
     * @brief tresholding apply a treshold on the image
     * @param treshold
     * @return
     */
    Img2DGrey tresholding(unsigned int treshold) const;


    /**
     * @brief smooth do the mean of the (2 * neighboorSize + 1)^2 neighboors of each pixel
     * @param neighboorSize
     * @return
     */
    Img2DGrey smooth(unsigned int neighboorSize) const;

};



// External operator from class

template<typename T>
std::ostream& operator<<(std::ostream& os, Img2DGrey& obj)
{
    os << obj.toString();

    return os;
}




#endif
