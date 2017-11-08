#include "Img2DGrey.h"

int main()
{
    Img2DGrey imgTest;
    Img2DGrey imgLoadTest;
    imgLoadTest.loadImageFromPGMFile("../../../../test.pgm");
    unsigned char temp = imgLoadTest[1][1];

    std::cout << "value de imgLoadTest[1][1] : " << (int)temp << std::endl;
    std::cout << imgLoadTest << std::endl;

    return 0;
}
