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
            readLineStringStream >> loadedImageWidth >> loadedImageHeight;
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


void Img2DGrey::saveImageToPGMFile(std::string fileName) const
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
    pgmFile << this->width << " " << this->height << std::endl;
    pgmFile << "255" << std::endl;

    // Create the matrix data
    for(unsigned int i = 0; i<this->height; i++)
    {
        for(unsigned int j = 0; j<this->width-1; j++)
        {
            pgmFile << (unsigned int)this->data[i][j] << " ";
        }
        pgmFile << (unsigned int)this->data[i][this->width-1] << std::endl;
    }
}


Img2DGrey Img2DGrey::tresholding(unsigned int treshold) const
{
    unsigned int i = 0;
    unsigned int j = 0;

    Img2DGrey answ(this->height, this->width);

    for(i=0; i<this->height; i++)
    {
        for(j=0; j<this->width; j++)
        {
            if((unsigned int)this->data[i][j] < treshold)
            {
                answ[i][j] = 0;
            }
            else
            {
                answ[i][j] = 255;
            }
        }
    }

    return answ;
}


void Img2DGrey::applySmoothOnPixel(unsigned int pi, unsigned int pj, Img2DGrey& img, unsigned int neighboorSize) const
{
    int tempiInf = 0;
    int tempjInf = 0;
    unsigned int tempiSup = 0;
    unsigned int tempjSup = 0;

    for(unsigned int i=0; i<=neighboorSize; i++)
    {
        for(unsigned int j=0; j<=neighboorSize; j++)
        {
            tempiInf = pi - i;
            tempjInf = pj - i;
            tempiSup = pi + i;
            tempjSup = pj + j;
            // If the neighboor is on the top side out of the image
            if(tempiInf < 0)
            {
                // If the neighboor is on the left side out of the image
                if(tempjInf < 0)
                {
                    img[pi][pj] += this->data[pi+i][pj+j] * 4;
                }
                // If the neighboor is on the right side out of the image
                else if(tempjSup >= this->width)
                {
                    img[pi][pj] += this->data[pi+i][pj-j] * 4;
                }
                // If the neighboor is inside the image on horizontal coordinate
                else
                {
                    img[pi][pj] += this->data[pi+i][pj+j] * 2;
                    img[pi][pj] += this->data[pi+i][pj-j] * 2;
                }
            }
            // If the neighboor is on the bottom side out of the image
            else if(tempiSup >= this->height)
            {
                // If the neighboor is on the left side out of the image
                if(tempjInf < 0)
                {
                    img[pi][pj] += this->data[pi-i][pj+j] * 4;
                }
                // If the neighboor is on the right side out of the image
                else if(tempjSup >= this->width)
                {
                    img[pi][pj] += this->data[pi-i][pj-j] * 4;
                }
                // If the neighboor is inside the image on horizontal coordinate
                else
                {
                    img[pi][pj] += this->data[pi-i][pj+j] * 2;
                    img[pi][pj] += this->data[pi-i][pj-j] * 2;
                }
            }
            // If the neighboor is inside the image on vertical coordinate
            else
            {
                // If the neighboor is on the left side out of the image
                if(tempjInf < 0)
                {
                    img[pi][pj] += this->data[pi+i][pj+j] * 2;
                    img[pi][pj] += this->data[pi-i][pj+j] * 2;
                }
                // If the neighboor is on the right side out of the image
                else if(tempjSup >= this->width)
                {
                    img[pi][pj] += this->data[pi+i][pj-j] * 2;
                    img[pi][pj] += this->data[pi-i][pj-j] * 2;
                }
                // If the neighboor is inside the image
                else
                {
                    img[pi][pj] += this->data[pi+i][pj+j];
                    img[pi][pj] += this->data[pi+i][pj-j];
                    img[pi][pj] += this->data[pi-i][pj+j];
                    img[pi][pj] += this->data[pi-i][pj-j];
                }
            }
        }
    }
    img[pi][pj] = (int)img[pi][pj] / std::pow((2*neighboorSize + 1),2);
    //std::cout << "Img[" << pi << "][" << pj << "] = " << (int)img[pi][pj] << std::endl;
}


Img2DGrey Img2DGrey::smooth(unsigned int neighboorSize) const
{
    Img2DGrey answ(this->height, this->width);
    for(unsigned int i = 0; i<this->height; i++)
    {
        for(unsigned int j = 0; j<this->width; j++)
        {
            applySmoothOnPixel(i, j, answ, neighboorSize);
        }
    }
    return answ;
}


Img2DGrey Img2DGrey::subTileImage() const
{
    int newPixelValue = 0;
    unsigned int newHeight = this->height/2;
    unsigned int newWidth = this->width/2;
    unsigned int i_shift = 0;
    unsigned int j_shift = 0;

    Img2DGrey answ(newHeight, newWidth);

    for(unsigned int i = 0; i<newHeight; i++)
    {
        for(unsigned int j = 0; j<newWidth; j++)
        {
            // Compute the mean of the group of pixels that compose the sub-tile image pixel
            // (i.e : newImage[i][j] = (2*2) pixels in image)
            newPixelValue = this->data[i_shift][j_shift];
            newPixelValue += this->data[i_shift][j_shift+1];
            newPixelValue += this->data[i_shift+1][j_shift];
            newPixelValue += this->data[i_shift+1][j_shift+1];

            answ[i][j] = newPixelValue / 4;

            j_shift += 2;
        }
        i_shift += 2;
        j_shift = 0;
    }

    return answ;
}













