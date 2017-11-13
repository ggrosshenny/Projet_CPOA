#include "Img2RGB.h"
#include <iostream>
#include <iomanip>
#include <fstream>


void Img2RGB::loadImageFromPPMFile(std::string fileName)
{
    std::string readLineString;
    std::stringstream readLineStringStream;
    std::ifstream ppmFile;
    unsigned int loadedImageHeight = 0;
    unsigned int loadedImageWidth = 0;
    unsigned int actualHeight = 0;
    float pixelValue = 0.0f;
    float maxPixelValue = 0.0f;
    float maxImg2DGreyValue = 255.0f;
    char tempRead = ' ';
    bool continueReading = true;

    ppmFile.open(fileName);

    // --------------------
    // Checking procedures

    // Check if the file was successfully opened
    if(!ppmFile.is_open())
    {
        std::cerr << "File " << fileName << " was not successfully opened" << std::endl;
        exit(1);
    }

    // Check if file is not empty
    if(!std::getline(ppmFile, readLineString))
    {
       std::cerr << "File " << fileName << " is emtpy" << std::endl;
       exit(1);
    }

    // Check if file is a PGM file (i.e check if the magic number is P2)
    if(readLineString.compare("P3") != 0)
    {
        std::cerr << "File " << fileName << " is not int PGM format (the magic number is not P2)" << std::endl;
        exit(1);
    }


    // -------------------------------
    // get values of the image to load

    // Get the height and the width of the image to load
    while((continueReading) && (std::getline(ppmFile, readLineString)))
    {
        readLineStringStream.str(readLineString);
        if((tempRead = readLineStringStream.get()) != '#')
        {
            // Set the offset to the beginning of the line
            readLineStringStream.seekg(0, readLineStringStream.beg);
            // Get height and width
            readLineStringStream >> loadedImageWidth >> loadedImageHeight;
            continueReading = false;
        }
    }

    // Get the maximum value of each pixel in the image to load
    if(!std::getline(ppmFile, readLineString))
    {
       std::cerr << "File " << fileName << " does not have enough lines" << std::endl;
       exit(1);
    }

    // Get the maximum value of a pixel
    readLineStringStream.str(readLineString);

    readLineStringStream.seekg(0, readLineStringStream.beg);
    readLineStringStream >> maxPixelValue;

    // Copy the load image into the new image

    Img2RGB newImage(loadedImageHeight, loadedImageWidth);
    *this = newImage;

    while((std::getline(ppmFile, readLineString)) && (actualHeight < loadedImageHeight))
    {
        readLineStringStream.str(readLineString);
        readLineStringStream.seekg(0, readLineStringStream.beg);
        for(unsigned int i = 0; i < loadedImageWidth; i++)
        {
            for(unsigned int k = 0; k < 3; k++)
            {
                readLineStringStream >> pixelValue;
                float temp = (pixelValue / maxPixelValue) * maxImg2DGreyValue;
                this->data[actualHeight][i][k] = (unsigned char) temp;
            }
        }
        actualHeight++;
    }

    ppmFile.close();
}



void Img2RGB::saveImageToPPMFile(std::string fileName) const
{

    std::ofstream ppmFile;


    ppmFile.open(fileName);

    // --------------------
    // Checking procedures

    // Check if the file was successfully opened
    if(!ppmFile.is_open())
    {
        std::cerr << "File " << fileName << " was not successfully opened or created" << std::endl;
        exit(1);
    }

    // Create the header of the pgm file
    ppmFile << "P3" << std::endl;
    ppmFile << "# Image auto-saved to PGM format" << std::endl;
    ppmFile << this->width << " " << this->height << std::endl;
    ppmFile << "255" << std::endl;

    // Create the matrix data
    for(unsigned int i = 0; i<this->height; i++)
    {
        for(unsigned int j = 0; j<this->width-1; j++)
        {
            ppmFile << (unsigned int)this->data[i][j][0] << " " << (unsigned int)this->data[i][j][1] << " " << (unsigned int)this->data[i][j][2] << "  ";
        }
        ppmFile << (unsigned int)this->data[i][this->width-1][0] << " " << (unsigned int)this->data[i][this->width-1][1] << " " << (unsigned int)this->data[i][this->width-1][2] << std::endl;
    }
}
