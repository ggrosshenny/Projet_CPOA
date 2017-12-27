#include "../imgGradient.h"

#include <cassert>

int main()
{
    std::cout << "Begin of tests of imgGradient" << std::endl;

    unsigned int i = 0;

    // ============
    // Constructors

      // Constructor with arguments
    int gx[25] = {1, 2, 0, -2, -1, 4, 8, 0, -8, -4, 6, 12, 0, -12, -6, 4, 8, 0, -8, -4, 1, 2, 0, -2, -1};
    int gy[25] = {1, 4, 6, 4, 1, 2, 8, 12, 8, 2, 0, 0, 0, 0, 0, -2, -8, -12, -8, -2, -1, -4, -6, -4, -1};
    imgGradient imgGradeCstr(gx, gy);
    for(i=0; i<25; i++)
    {
        assert(imgGradeCstr.Sobel5x[i] == gx[i]);
        assert(imgGradeCstr.Sobel5y[i] == gy[i]);
    }
    std::cout << "Test of constructor with arguments is Ok." << std::endl;

      // Brace-enclosed initializer
    imgGradient imgGradBe = {{1, 2, 0, -2, -1, 4, 8, 0, -8, -4, 6, 12, 0, -12, -6, 4, 8, 0, -8, -4, 1, 2, 0, -2, -1},
                             {1, 4, 6, 4, 1, 2, 8, 12, 8, 2, 0, 0, 0, 0, 0, -2, -8, -12, -8, -2, -1, -4, -6, -4, -1}};
    for(i=0; i<25; i++)
    {
        assert(imgGradBe.Sobel5x[i] == gx[i]);
        assert(imgGradBe.Sobel5y[i] == gy[i]);
    }
    std::cout << "Test of brace-enclosed constructor is Ok." << std::endl;


    // =================
    // Auxiliary methods

      // applyConvolutionOnPixelAux
    // 5x5
    Img2DGrey testImg;
    testImg.loadImageFromPGMFile("../../../TestsRessources/Images/test.pgm");
    Vec2D testConvolutionPixel;
    imgGradBe.applyConvolutionOnPixelAux(0, 0, 0, 0, testImg, testConvolutionPixel, 5);
    assert(testConvolutionPixel[0] == 255);
    assert(testConvolutionPixel[1] == 255);
    // 3x3
    testConvolutionPixel = Vec2D();
    imgGradBe.applyConvolutionOnPixelAux(0, 0, 0, 0, testImg, testConvolutionPixel, 3);
    assert(testConvolutionPixel[0] == -255);
    assert(testConvolutionPixel[1] == 255);
    std::cout << "Test of imgGradient::applyConvolutionOnPixelAux is Ok." << std::endl;

      // applyConvolutionOnPixel
    testConvolutionPixel = imgGradBe.applyConvolutionOnPixel(3, 1, testImg, 5);
    assert(testConvolutionPixel[0] == 0);
    assert(testConvolutionPixel[1] == 0);
    testConvolutionPixel = imgGradBe.applyConvolutionOnPixel(0, 0, testImg, 3);
    assert((testConvolutionPixel[0] >= 481) && (testConvolutionPixel[0] < 482));
    assert(testConvolutionPixel[1] == 935);
    std::cout << "Test of imgGradient::applyConvolutionOnPixel is Ok." << std::endl;

    // ================
    // gradient methods

      // gradient33
    Img2D<Vec2D> testGradient33 = imgGradBe.gradient33(testImg);

      // gradient55
    Vec2D assertTest;
    Img2D<Vec2D> testGradient55 = imgGradBe.gradient55(testImg);
    unsigned int j = 0;
    for(i=0; i<testGradient55.getHeight(); i++)
    {
        for(j=0; j<testGradient55.getWidth(); j++)
        {
            assert(testGradient55[i][j] == assertTest);
        }
    }
    std::cout << "Test of imgGradient::gradient55 is Ok." << std::endl;


    return 0;
}
