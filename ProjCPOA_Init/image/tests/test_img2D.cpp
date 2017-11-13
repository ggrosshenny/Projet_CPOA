#include "Img2D.h"
#include "Img2RGB.h"
#include <cassert>

int main()
{
    // ============
    // Constructors

      // Default constructor
    int imgDeHeight = 10;
    int imgDeWidth = 10;
    Img2D<double> imgDe(imgDeHeight, imgDeWidth);
    bool constrOk = true;

    for(int i=0; i<imgDeHeight; i++)
    {
        for(int j=0; j<imgDeWidth; j++)
        {
            constrOk = constrOk && (imgDe[i][j] == 0.0);
        }
    }
    assert(constrOk);
    std::cout << "Test of default constructor is Ok." << std::endl;

      // Brace-enclosed constructor with all elements defined
    Img2D<double> imgBe = {{1.0, 1.0, 1.0, 1.0},{0.0, 1.0, 0.0, 0.0},{1.0, 1.0, 1.0, 1.0}};
    // First row
    assert(imgBe[0][0] == 1.0);
    assert(imgBe[0][1] == 1.0);
    assert(imgBe[0][2] == 1.0);
    assert(imgBe[0][3] == 1.0);
    // Second row
    assert(imgBe[1][0] == 0.0);
    assert(imgBe[1][1] == 1.0);
    assert(imgBe[1][2] == 0.0);
    assert(imgBe[1][3] == 0.0);
    // Third row
    assert(imgBe[2][0] == 1.0);
    assert(imgBe[2][1] == 1.0);
    assert(imgBe[2][2] == 1.0);
    assert(imgBe[2][3] == 1.0);
    std::cout << "Test of brace-enclosed constructor with all elements defined is Ok." << std::endl;

      // Brace-enclosed constructor with some elements not defined
    Img2D<double> imgBe2 = {{1.0},{0.0, 1.0},{1.0, 1.0, 1.0, 1.0}};
    // First row
    assert(imgBe2[0][0] == 1.0);
    assert(imgBe2[0][1] == 0.0);
    assert(imgBe2[0][2] == 0.0);
    assert(imgBe2[0][3] == 0.0);
    // Second row
    assert(imgBe2[1][0] == 0.0);
    assert(imgBe2[1][1] == 1.0);
    assert(imgBe2[1][2] == 0.0);
    assert(imgBe2[1][3] == 0.0);
    // Third row
    assert(imgBe2[2][0] == 1.0);
    assert(imgBe2[2][1] == 1.0);
    assert(imgBe2[2][2] == 1.0);
    assert(imgBe2[2][3] == 1.0);
    std::cout << "Test of brace-enclosed constructor with some elements not defined is Ok." << std::endl;


    // =================
    // Auxiliary methods

      // getHeight
    unsigned int heightBe = imgBe2.getHeight();
    assert(heightBe == 3);
    std::cout << "Test of getHeight is Ok." << std::endl;

      // getWidth
    unsigned int widthBe = imgBe2.getWidth();
    assert(widthBe == 4);
    std::cout << "Test of getWidth is Ok." << std::endl;

      // toString
    std::string imgBe2_str = imgBe2.toString();
    std::stringstream str_ctrl;
    str_ctrl << "Image : " << std::endl;
    str_ctrl << "\t[1, 0, 0, 0]," << std::endl;
    str_ctrl << "\t[0, 1, 0, 0]," << std::endl;
    str_ctrl << "\t[1, 1, 1, 1]" << std::endl;
    assert(imgBe2_str == str_ctrl.str());
    std::cout << "Test of toString is Ok." << std::endl;

      // reduceRatio
    unsigned int ratioHeight = 16;
    unsigned int ratioWidth = 12;
    Img2D<double>::reduceRatio(&ratioHeight, &ratioWidth);
    assert(ratioHeight == 4);
    assert(ratioWidth == 3);
    std::cout << "Test of reduceRatio is Ok." << std::endl;


    // =================
    // Operator iverload

      // Operator [] (get)
    DynamicArray<double> testArray;
    testArray = imgBe2[0]; // = {1.0, 0.0, 0.0, 0.0}
    assert(testArray[0] == 1.0);
    assert(testArray[1] == 0.0);
    assert(testArray[2] == 0.0);
    assert(testArray[3] == 0.0);
      // Operator [] (set)
    DynamicArray<double> testArray2 = {1.0, 1.0, 1.0, 1.0};
    imgBe2[0] = testArray2;
    assert(imgBe2[0][0] == 1.0);
    assert(imgBe2[0][1] == 1.0);
    assert(imgBe2[0][2] == 1.0);
    assert(imgBe2[0][3] == 1.0);
    std::cout << "Test of operator [] is Ok." << std::endl;

      // Operator =
    Img2D<double> testEgl;
    testEgl = imgBe2;
    // First row
    assert(imgBe2[0][0] == testEgl[0][0]);
    assert(imgBe2[0][1] == testEgl[0][1]);
    assert(imgBe2[0][2] == testEgl[0][2]);
    assert(imgBe2[0][3] == testEgl[0][3]);
    // Second row
    assert(imgBe2[1][0] == testEgl[1][0]);
    assert(imgBe2[1][1] == testEgl[1][1]);
    assert(imgBe2[1][2] == testEgl[1][2]);
    assert(imgBe2[1][3] == testEgl[1][3]);
    // Third row
    assert(imgBe2[2][0] == testEgl[2][0]);
    assert(imgBe2[2][1] == testEgl[2][1]);
    assert(imgBe2[2][2] == testEgl[2][2]);
    assert(imgBe2[2][3] == testEgl[2][3]);
    std::cout << "Test of operator = is Ok." << std::endl;


    // =================
    // Operator iverload

      // swapImages
    Img2D<double> imgBe3 = {{1.0},{0.0, 1.0},{1.0, 1.0, 1.0, 1.0}};
    imgBe2.swapImages(imgBe3);
    // imgBe2 :
    // First row
    assert(imgBe2[0][0] == 1.0);
    assert(imgBe2[0][1] == 0.0);
    assert(imgBe2[0][2] == 0.0);
    assert(imgBe2[0][3] == 0.0);
    // Second row
    assert(imgBe2[1][0] == 0.0);
    assert(imgBe2[1][1] == 1.0);
    assert(imgBe2[1][2] == 0.0);
    assert(imgBe2[1][3] == 0.0);
    // Third row
    assert(imgBe2[2][0] == 1.0);
    assert(imgBe2[2][1] == 1.0);
    assert(imgBe2[2][2] == 1.0);
    assert(imgBe2[2][3] == 1.0);
    // imgBe3:
    // First row
    assert(imgBe3[0][0] == 1.0);
    assert(imgBe3[0][1] == 1.0);
    assert(imgBe3[0][2] == 1.0);
    assert(imgBe3[0][3] == 1.0);
    // Second row
    assert(imgBe3[1][0] == 0.0);
    assert(imgBe3[1][1] == 1.0);
    assert(imgBe3[1][2] == 0.0);
    assert(imgBe3[1][3] == 0.0);
    // Third row
    assert(imgBe3[2][0] == 1.0);
    assert(imgBe3[2][1] == 1.0);
    assert(imgBe3[2][2] == 1.0);
    assert(imgBe3[2][3] == 1.0);
    std::cout << "Test of Img2D::swapImages is Ok." << std::endl;

      // cropping
    Img2D<double> croppedImgBe3 = imgBe3.cropping(2, 3);
    // First row
    assert(croppedImgBe3[0][0] == 1.0);
    assert(croppedImgBe3[0][1] == 1.0);
    assert(croppedImgBe3[0][2] == 1.0);
    // Second row
    assert(croppedImgBe3[1][0] == 1.0);
    assert(croppedImgBe3[1][1] == 0.0);
    assert(croppedImgBe3[1][2] == 0.0);
    std::cout << "Test of Img2D::cropping is Ok." << std::endl;

    return 0;
}
