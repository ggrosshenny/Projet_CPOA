#include "Img2D.hpp"

int main()
{
    Img2D<double> img(10, 10);

    double dbl = img[1][1];

    std::cout << dbl << std::endl;

    return 0;
}
