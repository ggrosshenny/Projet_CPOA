#ifndef __IMG2RGB_H_
#define __IMG2RGB_H_

#include "Img2D.h"
#include "../vectorMatrix/ProjectVectors.h"

#define Vec3UC ProjectVector<unsigned char, 3>

class Img2RGB : public Img2D<Vec3UC>
{
// Constructors
public:
    /**
     * @brief Img2RGB constructor without arguments. Dynamic allocation of an image of 256 * 256 pixels
     */
    Img2RGB() : Img2D<Vec3UC>() {}


    /**
     * @brief Img2RGB constructor with arguments. Dynamic allocation of an image of x * y pixels
     * @param height0
     * @param width0
     */
    Img2RGB(int height0, int width0) : Img2D<Vec3UC>(height0, width0) {}


    /**
     * @brief Img2RGB constructor with brace-enclosed initilization. Initialize data members with given values or [0, 0, 0] if unknown
     * @param elements
     */
    Img2RGB(std::initializer_list<std::initializer_list<Vec3UC>> elements) : Img2D<Vec3UC>(elements) {}

// Load and savec methods
public:
    /**
     * @brief loadImageFromPPMFile load a PPM file and create a new image with the loaded data
     * @param fileName File to read
     */
    void loadImageFromPPMFile(std::string fileName);


    /**
     * @brief saveImageToPPMFile Save the image to the PPM format in the file with the given file name
     * @param fileName
     */
    void saveImageToPPMFile(std::string fileName) const;
};


#endif
