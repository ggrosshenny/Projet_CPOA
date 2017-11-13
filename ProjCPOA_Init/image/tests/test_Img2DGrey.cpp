#include "Img2DGrey.h"
#include <cassert>

int main()
{
    std::cout << " Begin of tests of Img2DGrey" << std::endl;

    // ===========================
    // Image manipulations methods

      // loadImageFromPGMFile
    Img2DGrey imgLoadTest;
    imgLoadTest.loadImageFromPGMFile("../../../TestsRessources/Images/test.pgm");
    unsigned int i = 0;
    unsigned int j = 0;
    for(i=0; i<10; i++)
    {
        for(j=0; j<10; j++)
        {
            if((i == 0) || (i == 9))
            {
                assert(imgLoadTest[i][j] == 255);
            }
            else if((j == 4) || (j==5))
            {
                assert(imgLoadTest[i][j] == 255);
            }
            else
            {
                assert(imgLoadTest[i][j] == 0);
            }
        }
    }
    std::cout << "Test of Img2DGrey::loadFromPGMFile is Ok." << std::endl;

      // saveImageToPGMFile
    imgLoadTest.saveImageToPGMFile("../../../TestsRessources/Images/saveTest.pgm");
    Img2DGrey imgSaveTest;
    imgSaveTest.loadImageFromPGMFile("../../../TestsRessources/Images/saveTest.pgm");
    for(i=0; i<10; i++)
    {
        for(j=0; j<10; j++)
        {
            if((i == 0) || (i == 9))
            {
                assert(imgSaveTest[i][j] == 255);
            }
            else if((j == 4) || (j==5))
            {
                assert(imgSaveTest[i][j] == 255);
            }
            else
            {
                assert(imgSaveTest[i][j] == 0);
            }
        }
    }
    std::cout << "Test of Img2DGrey::saveImageToPGMFile is Ok." << std::endl;

      // tresholding
    Img2DGrey Trshld = {{160, 150, 200},{50, 64, 160}};
    Img2DGrey testTrshld = Trshld.tresholding(150);
    // First row
    assert(testTrshld[0][0] == 255);
    assert(testTrshld[0][1] == 255);
    assert(testTrshld[0][2] == 255);
    // Second row
    assert(testTrshld[1][0] == 0);
    assert(testTrshld[1][1] == 0);
    assert(testTrshld[1][2] == 255);
    std::cout << "Test of Img2DGrey::tresholding is Ok." << std::endl;

      // Smooth
    Img2DGrey smoothTest = imgSaveTest.smooth(1);
    smoothTest.saveImageToPGMFile("../../../TestsRessources/Images/smoothTest.pgm");
    // First and last row
    for(i=0; i<smoothTest.getWidth(); i++)
    {
        if((i == 4) || (i==5))
        {
            assert(smoothTest[0][i] == 26);
            assert(smoothTest[9][i] == 26);
        }
        else
        {
            assert(smoothTest[0][i] == 27);
            assert(smoothTest[9][i] == 27);
        }
    }
    // Second and ninth row
    for(i=0; i<smoothTest.getWidth(); i++)
    {
        if((i > 2) && (i<7))
        {
            assert(smoothTest[1][i] == 27);
            assert(smoothTest[8][i] == 27);
        }
        else
        {
            assert(smoothTest[1][i] == 28);
            assert(smoothTest[8][i] == 28);
        }
    }
    // 3 - 8 rows
    for(i = 2; i < 8; i++)
    {
        for(j=0; j<smoothTest.getWidth(); j++)
        {
            if((j==3) || (j==6))
            {
                assert(smoothTest[i][j] == 28);
            }
            else if ((j==4) || (j==5))
            {
                assert(smoothTest[i][j] == 27);
            }
            else
            {
                assert(smoothTest[i][j] == 0);
            }
        }
    }
    std::cout << "Test of Img2DGrey::smooth is Ok." << std::endl;
    std::cout << "smoothed image has been saved in TestsRessources/Images/ for visual control." << std::endl;

      // subTileImage
    imgLoadTest.loadImageFromPGMFile("../../../TestsRessources/Images/testBigger.pgm");
    Img2DGrey subTileImage = imgLoadTest.subTileImage();
    subTileImage.saveImageToPGMFile("../../../TestsRessources/Images/subTileTest.pgm");
    for(i=0; i<subTileImage.getHeight(); i++)
    {
        for(j=0; j<subTileImage.getWidth(); j++)
        {
            // First and last row
            if((i==0) || (i==11))
            {
                assert(subTileImage[i][j] == 0);
            }
            // Second and 11th row
            else if((i==1) || (i==10))
            {
                assert(subTileImage[i][j] == 255);
            }
            // 3 - 10 rows
            else
            {
                if(j==4)
                {
                    assert(subTileImage[i][j] == 255);
                }
                else if(j==5)
                {
                    assert(subTileImage[i][j] == 127);
                }
                else
                {
                    assert(subTileImage[i][j] == 0);
                }
            }
        }
    }
    std::cout << "Test of Img2DGrey::subTileImage is Ok." << std::endl;
    std::cout << "sub-tile image has been saved in TestsRessources/Images/ for visual control." << std::endl;

    return 0;
}
