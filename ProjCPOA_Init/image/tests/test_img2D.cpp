#include "Img2D.hpp"

int main()
{
    Img2D<double> img(10, 10);
    Img2D<double> img2 = {{1.0, 1.0, 1.0, 1.0},{0.0, 1.0, 0.0},{1.0}, {1.0, 1.0, 1.0, 1.0}};
    Img2D<double> img3(10,10);

    img3 = img2;

    double dbl2 = img2[1][1];
    double dbl = img[1][1];
    double dbl3 = img3[1][1];

    img3.swapImages(img);

    Img2D<double> imgCropped = img2.cropping(16, 12);

    double dblswp1 = img[1][1];
    double dblswp2 = img3[1][1];

    std::cout << "valeur de img[1][1] : " << dbl << std::endl;
    std::cout << "valeur de img2[1][1] : " << dbl2 << std::endl;
    std::cout << "valeur de img3[1][1] : " << dbl3 << std::endl;
    std::cout << "Après swap de img et img3, img[1][1] =  " << dblswp1 << " et img3[1][1] = " << dblswp2 << std::endl;
    std::cout << "img2 : " << img2 << std::endl;
    std::cout << "cropped img2 : " << imgCropped << std::endl;

    return 0;
}
