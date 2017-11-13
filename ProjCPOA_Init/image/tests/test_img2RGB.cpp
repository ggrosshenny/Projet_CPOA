#include "Img2RGB.h"

#include <cassert>

int main()
{
    std::cout << "Begin of tests of imgGradient" << std::endl;

    unsigned int i = 0;
    unsigned int j = 0;
    ProjectVector<unsigned char, 3> deTestVec;
    ProjectVector<unsigned char, 3> deTestVec255 = {255, 0, 255};

    // ============
    // Constructors

      // Default
    Img2RGB imgDe;
    for(i=0; i<256; i++)
    {
        for(j=0; j<256; j++)
        {
            assert(imgDe[i][j] == deTestVec);
        }
    }
    std::cout << "Test of default constructor is Ok." << std::endl;

      // Constructor with arguments
    Img2RGB imgArg(25, 25);
    for(i=0; i<25; i++)
    {
        for(j=0; j<25; j++)
        {
            assert(imgDe[i][j] == deTestVec);
        }
    }
    std::cout << "Test of constructor with arguments is Ok." << std::endl;

      // Brace-enclosed constructor
    Img2RGB imgBe = {{deTestVec, deTestVec, deTestVec, deTestVec}, {deTestVec, deTestVec, deTestVec, deTestVec}, {deTestVec, deTestVec, deTestVec, deTestVec}};
    for(i=0; i<3; i++)
    {
        for(j=0; j<4; j++)
        {
            assert(imgBe[i][j] == deTestVec);
        }
    }
    std::cout << "Test of brace-enclosed constructor is Ok." << std::endl;


    // =====================
    // Load and save methods

      // loadImageFromPPMFile
    Img2RGB imgLoadTest;
    imgLoadTest.loadImageFromPPMFile("../../../TestsRessources/Images/test.ppm");
    for(i=0; i<imgLoadTest.getHeight(); i++)
    {
        for(j=0; j<imgLoadTest.getWidth(); j++)
        {
            if((i==0) || (i==imgLoadTest.getHeight()-1))
            {
                assert(imgLoadTest[i][j] == deTestVec);
            }
            else if((i==1) || (i==imgLoadTest.getHeight()-2))
            {
                assert(imgLoadTest[i][j] == deTestVec255);
            }
            else
            {
                if((j==4) || (j==5))
                {
                    assert(imgLoadTest[i][j] == deTestVec255);
                }
                else
                {
                    assert(imgLoadTest[i][j] == deTestVec);
                }
            }
        }
    }
    std::cout << "Test of Img2RGB::loadImageFromPPMFile is Ok." << std::endl;

      // saveImageToPPMFile
    Img2RGB imgSaveTest;
    imgLoadTest.saveImageToPPMFile("../../../TestsRessources/Images/testSave.ppm");
    imgSaveTest.loadImageFromPPMFile("../../../TestsRessources/Images/testSave.ppm");
    for(i=0; i<imgSaveTest.getHeight(); i++)
    {
        for(j=0; j<imgSaveTest.getWidth(); j++)
        {
            if((i==0) || (i==imgSaveTest.getHeight()-1))
            {
                assert(imgSaveTest[i][j] == deTestVec);
            }
            else if((i==1) || (i==imgSaveTest.getHeight()-2))
            {
                assert(imgSaveTest[i][j] == deTestVec255);
            }
            else
            {
                if((j==4) || (j==5))
                {
                    assert(imgSaveTest[i][j] == deTestVec255);
                }
                else
                {
                    assert(imgSaveTest[i][j] == deTestVec);
                }
            }
        }
    }
    std::cout << "Test of Img2RGB::saveImageFromPPMFile is Ok." << std::endl;

    return 0;
}
