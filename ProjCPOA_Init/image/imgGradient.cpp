#include "imgGradient.h"


// Constructors


imgGradient::imgGradient(int gx[25], int gy[25])
{
    unsigned int i = 0;

    for(i=0; i<25; i++)
    {
        this->Sobel5x[i] = gx[i];
        this->Sobel5y[i] = gy[i];
    }
}


imgGradient::imgGradient(std::initializer_list<std::initializer_list<int>> elements)
{
    int i = 0;
    int j = 0;

    for(auto it = elements.begin(); it != elements.end(); ++it)
    {
        if(i <2)
        {
            for(auto subIt = it->begin(); subIt != it->end(); ++subIt)
            {
                if(j<25)
                {
                    if(i == 0)
                    {
                        this->Sobel5x[j] = *subIt;
                    }
                    if(i == 1)
                    {
                        this->Sobel5y[j] = *subIt;
                    }
                }
                j++;
            }
            if(j<24)
            {
                std::cerr << "[Warning] Not enough arguments to create the gradient of the imgGradientObject" << std::endl;
            }
            i++;
            j=0;
        }
    }
}



// Auxiliary methods


void imgGradient::applyConvolutionOnPixelAux(unsigned int pi, unsigned int pj, int in0, int jn0, const Img2DGrey& img, Vec2D& pixel, unsigned int neighboorSize) const
{
    Vec2D newPixel;
    // Verify the position of the pixel
    if(pi<0 || pi <0) // protection contre les débordements des bords gauche et haut
    {
        newPixel[0] = img[std::abs(pi)][std::abs(pj)];
        newPixel[1] = img[std::abs(pi)][std::abs(pj)];
    }
    else if(pi>=img.getHeight()) // protection contre les débordements du bord bas
    {
        unsigned int i_shift = (img.getHeight() + pi) % img.getHeight();
        newPixel[0] = img[img.getHeight()-i_shift][pj];
        newPixel[1] = img[img.getHeight()-i_shift][pj];
    }
    else if (pi >= img.getWidth()) // protection contre les débrodements du bord droit
    {
        unsigned int j_shift = (img.getWidth() + pi) % img.getWidth();
        newPixel[0] = img[pi][img.getWidth()-j_shift];
        newPixel[1] = img[pi][img.getWidth()-j_shift];
    }
    else if(pi>=img.getHeight() && pi >= img.getWidth()) // protection contre les débordements du coin bas-droit
    {
        unsigned int i_shift = (img.getHeight() + pi) % img.getHeight();
        unsigned int j_shift = (img.getWidth() + pi) % img.getWidth();
        newPixel[0] = img[img.getHeight()-i_shift][img.getWidth()-j_shift];
        newPixel[1] = img[img.getHeight()-i_shift][img.getWidth()-j_shift];
    }
    else // pour les autres pixels
    {
        newPixel[0] = img[pi][pj];
        newPixel[1] = img[pi][pj];
    }

    // Apply x and y convolution and store it in newPixel
    if(neighboorSize == 3)
    {
        if((in0 > 2) || (jn0 > 2))
        {
            std::cerr << "Invalid index for application of gradient 3x3" << std::endl;
            exit(1);
        }
        newPixel[0] *= this->Sobel5x[(in0+1)*3 + (jn0 + 1)];
        newPixel[1] *= this->Sobel5y[(in0+1)*3 + (jn0 + 1)];
    }
    if(neighboorSize == 5)
    {
        newPixel[0] *= this->Sobel5x[in0*5 + jn0];
        newPixel[1] *= this->Sobel5y[in0*5 + jn0];
    }

    pixel += newPixel;
}


Vec2D imgGradient::applyConvolutionOnPixel(unsigned int pi, unsigned int pj, const Img2DGrey& img, unsigned int neighboorSize) const
{
    Vec2D newPixel;

    if((neighboorSize != 3) && (neighboorSize != 5))
    {
        std::cerr << "Warning, cannot handle convolution with convolution matrix of size different than 3x3 or 5x5 !" << std::endl;
        exit(1);
    }

    for(unsigned int i=0; i<neighboorSize; i++)
    {
        for(unsigned int j=0; j<neighboorSize; j++)
        {
            applyConvolutionOnPixelAux(pi, pj, i, j, img, newPixel, neighboorSize);
        }
    }

    newPixel /= std::pow(neighboorSize, 2);

    return newPixel;
}


Img2D<Vec2D> imgGradient::gradient33(const Img2DGrey& img_in)
{
    unsigned int i = 0;
    unsigned int j = 0;

    //Vec2D test;

    Img2D<Vec2D> GradientImage(img_in.getHeight(), img_in.getWidth());

    for(i=0; i<img_in.getHeight(); i++)
    {
        for(j=0; j<img_in.getWidth(); j++)
        {
            GradientImage[i][j] = applyConvolutionOnPixel(i, j, img_in, 3);
        }
    }

    return GradientImage;
}


Img2D<Vec2D> imgGradient::gradient55(const Img2DGrey& img_in)
{
    unsigned int i = 0;
    unsigned int j = 0;

    Img2D<Vec2D> GradientImage;

    for(i=0; i<img_in.getHeight(); i++)
    {
        for(j=0; j<img_in.getWidth(); j++)
        {
            GradientImage[i][j] = applyConvolutionOnPixel(i, j, img_in, 5);
        }
    }

    return GradientImage;
}


