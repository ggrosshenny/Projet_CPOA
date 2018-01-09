#ifndef __IMG2D_HPP_
#define __IMG2D_HPP_

#include "Img2D.h"


// -----------------------------
// Constructors and desctructors


template<typename T>
Img2D<T>::Img2D()
{
    unsigned int i = 0;

    this->height = 256;
    this->width = 256;

    DynamicArray<DynamicArray<T>> t = DynamicArray<DynamicArray<T>>(this->height);
    this->data = t;

    for(i = 0; i<height; i++)
    {
        DynamicArray<T> tbis = DynamicArray<T>(this->width);
        this->data[i] = tbis;
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
        DynamicArray<T> tbis = DynamicArray<T>(this->width);
        this->data[i] = tbis;
    }
}


template<typename T>
Img2D<T>::Img2D(std::initializer_list<std::initializer_list<T>> elements)
{
    unsigned int i = 0;
    unsigned int j = 0;

    this->height = elements.size();
    this->width = 0;

    DynamicArray<DynamicArray<T>> t = DynamicArray<DynamicArray<T>>(this->height);
    this->data = t;

    for(auto it0 = elements.begin(); it0 != elements.end(); ++it0)
    {
        if(this->width < it0->size())
        {
            this->width = it0->size();
        }
    }

    for(auto it = elements.begin(); it != elements.end(); ++it)
    {

        DynamicArray<T> tbis = DynamicArray<T>(this->width);
        this->data[i] = tbis;

        for(auto subIt = it->begin(); subIt != it->end(); ++subIt)
        {
            if(j<this->width)
            {
                this->data[i][j] = *subIt;
            }
            j++;
        }
        i++;
        j = 0;
    }
}



template<typename T>
Img2D<T>::~Img2D()
{

}


// -------------------
//  Auxiliary methods


template<typename T>
unsigned int Img2D<T>::getHeight() const
{
    return this->height;
}


template<typename T>
unsigned int Img2D<T>::getWidth() const
{
    return this->width;
}


template<typename T>
std::string Img2D<T>::toString()
{
    std::stringstream strImage;

    strImage << "Image : " << std::endl;
    for(unsigned int i=0; i<this->height-1; i++)
    {
        strImage << "\t" << this->data[i] << "," << std::endl;
    }
    strImage << "\t" << this->data[this->height-1] << std::endl;

    return strImage.str();
}


template<typename T>
void Img2D<T>::reduceRatio(unsigned int *ratio_height, unsigned int *ratio_width)
{
    bool continueComputation = true;
    unsigned int gcd = std::min(*ratio_height, *ratio_width);

    while((gcd != 1) && (continueComputation))
    {
        if(((*ratio_height % gcd) == 0) && ((*ratio_width % gcd) == 0))
        {
            *ratio_height = *ratio_height / gcd;
            *ratio_width = *ratio_width / gcd;
            gcd =std::min(*ratio_height, *ratio_width);
            continueComputation = false;
        }
        else
        {
            gcd--;
        }
    }
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


template<typename T>
Img2D<T> Img2D<T>::operator=(Img2D<T>& other)
{
    if(this != &other)
    {
        this->height = other.getHeight();
        this->width = other.getWidth();
        DynamicArray<DynamicArray<T>> t = DynamicArray<DynamicArray<T>>(other.getHeight());
        this->data = t;

        for(unsigned int i=0; i<other.height; i++)
        {
            this->data[i] = other[i];
        }
    }

    return *this;
}


// ------------------------------
//   Image modification methods


template<typename T>
void Img2D<T>::swapImages(Img2D<T> &other)
{
    Img2D<T> temp;
    temp = other;
    other = *this;
    *this = temp;
}


template<typename T>
Img2D<T> Img2D<T>::cropping(unsigned int ratio_height, unsigned int ratio_width)
{
    unsigned int i = 0;
    unsigned int j = 0;
    unsigned int i_cropped = 0;
    unsigned int j_cropped = 0;
    unsigned int heightShift = 0;
    unsigned int widthShift = 0;
    unsigned int factor_height = 0;
    unsigned int factor_width = 0;
    unsigned int cropFactor = 0;
    unsigned int croppedImage_height = 0;
    unsigned int croppedImage_width = 0;
    unsigned int begin_shift_height = 0;
    unsigned int begin_shift_width = 0;


    // transform ratio to its reduced form
    reduceRatio(&ratio_height, &ratio_width);

    // find the minimal factor of ratio
    factor_height = std::floor(this->height/ratio_height);
    factor_width = std::floor(this->width/ratio_width);
    cropFactor = std::min(factor_height, factor_width);

    Img2D<T> croppedImg;

    if(cropFactor == 0)
    {
        croppedImg = *this;
    }
    else
    {
        // Compute the height and width of the cropped image
        croppedImage_height = cropFactor * ratio_height;
        croppedImage_width = cropFactor * ratio_width;

        // Compute shift between image size and cropped image size
        heightShift = std::abs(this->height - croppedImage_height);
        widthShift = std::abs(this->width - croppedImage_width);

        begin_shift_height = heightShift/2;
        if(widthShift % 2 == 1)
        {
            begin_shift_width = (widthShift/2) + 1;
        }

        // Create the cropped image

        Img2D<T> imgBis = Img2D<double>(croppedImage_height, croppedImage_width);
        croppedImg = imgBis;

        i = begin_shift_height;
        j = begin_shift_width;
        for(i_cropped = 0; i_cropped<croppedImage_height; i_cropped++)
        {
            for(j_cropped = 0; j_cropped<croppedImage_width; j_cropped++)
            {
                croppedImg[i_cropped][j_cropped] = this->data[i][j];
                j++;
            }
            i++;
            j = begin_shift_width;
        }
    }



    return croppedImg;
}


// External operator from class

template<typename T>
std::ostream& operator<<(std::ostream& os, Img2D<T>& obj)
{
    os << obj.toString();
    return os;
}


#endif
