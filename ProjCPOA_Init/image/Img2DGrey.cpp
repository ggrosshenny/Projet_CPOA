#include "Img2DGrey.h"
#include <iostream>
#include <iomanip>
#include <fstream>


/*
 PGM file format :

 P2
 # ...                // Can contain multiple lines of comments
 height width
 max_pixel_value
 x00 x01 ... x0n      // matrix(height,width) of the image data
 x10 x11 ... x1n
 .            .
 .            .
 .            .
 xm0 xm1 ... xmn
 */



void Img2DGrey::loadImageFromPGMFile(std::string fileName)
{
    std::string readLineString;
    std::stringstream readLineStringStream;
    std::ifstream pgmFile;
    unsigned int loadedImageHeight = 0;
    unsigned int loadedImageWidth = 0;
    unsigned int actualHeight = 0;
    float pixelValue = 0.0f;
    float maxPixelValue = 0.0f;
    float maxImg2DGreyValue = 255.0f;
    char tempRead = ' ';
    bool continueReading = true;

    pgmFile.open(fileName);

    // --------------------
    // Checking procedures

    // Check if the file was successfully opened
    if(!pgmFile.is_open())
    {
        std::cerr << "File " << fileName << " was not successfully opened" << std::endl;
        exit(1);
    }

    // Check if file is not empty
    if(!std::getline(pgmFile, readLineString))
    {
       std::cerr << "File " << fileName << " is emtpy" << std::endl;
       exit(1);
    }

    // Check if file is a PGM file (i.e check if the magic number is P2)
    if(readLineString.compare("P2") != 0)
    {
        std::cerr << "File " << fileName << " is not int PGM format (the magic number is not P2)" << std::endl;
        exit(1);
    }


    // -------------------------------
    // get values of the image to load

    // Get the height and the width of the image to load
    while((continueReading) && (std::getline(pgmFile, readLineString)))
    {
        readLineStringStream.str(readLineString);
        if((tempRead = readLineStringStream.get()) != '#')
        {
            // Set the offset to the beginning of the line
            readLineStringStream.seekg(0, readLineStringStream.beg);
            // Get height and width
            readLineStringStream >> loadedImageHeight >> loadedImageWidth;
            continueReading = false;
        }
    }

    // Get the maximum value of each pixel in the image to load
    if(!std::getline(pgmFile, readLineString))
    {
       std::cerr << "File " << fileName << " does not have enough lines" << std::endl;
       exit(1);
    }

    // Get the maximum value of a pixel
    readLineStringStream.str(readLineString);

    readLineStringStream.seekg(0, readLineStringStream.beg);
    readLineStringStream >> maxPixelValue;

    // Copy the load image into the new image

    Img2DGrey newImage(loadedImageHeight, loadedImageWidth);
    *this = newImage;

    while((std::getline(pgmFile, readLineString)) && (actualHeight < loadedImageHeight))
    {
        readLineStringStream.str(readLineString);
        readLineStringStream.seekg(0, readLineStringStream.beg);
        for(unsigned int i = 0; i < loadedImageWidth; i++)
        {
            readLineStringStream >> pixelValue;
            float temp = (pixelValue / maxPixelValue) * maxImg2DGreyValue;
            this->data[actualHeight][i] = (unsigned char) temp;

        }
        actualHeight++;
    }

    pgmFile.close();
}


void Img2DGrey::saveImageToPGMFile(std::string fileName)
{

    std::ofstream pgmFile;


    pgmFile.open(fileName);

    // --------------------
    // Checking procedures

    // Check if the file was successfully opened
    if(!pgmFile.is_open())
    {
        std::cerr << "File " << fileName << " was not successfully opened or created" << std::endl;
        exit(1);
    }

    // Create the header of the pgm file
    pgmFile << "P2" << std::endl;
    pgmFile << "# Image auto-saved to PGM format" << std::endl;
    pgmFile << this->height << this->width << std::endl;
    pgmFile << "255" << std::endl;

    // Create the matrix data
    for(unsigned int i = 0; i<this->height; i++)
    {
        for(unsigned int j = 0; j<this->width-1; j++)
        {
            pgmFile << this->data[i][j] << " ";
        }
        pgmFile << this->data[i][this->width-1] << std::endl;
    }
}
