#include <cassert>
#include "../BoundingBox.h"


int main()
{
    // Work space initialization
    BoundingBox b1({0,10}, {10,0});
    BoundingBox b2({5,12}, {12,5});
    BoundingBox b3 = BoundingBox ({11, 12}, {12, 11});

    // Test od union
    std::cout << "Test of union operation" << std::endl;
    BoundingBox unionBB = b1 + b2;
    assert(unionBB.getTopLeftCornerPoint().x() == 0);
    assert(unionBB.getTopLeftCornerPoint().y() == 12);
    assert(unionBB.getBottomRightCornerPoint().x() == 12);
    assert(unionBB.getBottomRightCornerPoint().y() == 0);
    std::cout << "Test of union operation passed" << std::endl;

    // Test of difference
    std::cout << "Test of difference operation" << std::endl;
    BoundingBox diffBB = b1 - b2;
    assert(diffBB.getTopLeftCornerPoint().x() == 0);
    assert(diffBB.getTopLeftCornerPoint().y() == 10);
    assert(diffBB.getBottomRightCornerPoint().x() == 5);
    assert(diffBB.getBottomRightCornerPoint().y() == 0);
    std::cout << "Test of difference operation passed" << std::endl;

    // Test of intersection
    std::cout << "Test of intersection operation" << std::endl;
    BoundingBox interBB = b1 ^ b2;
    assert(interBB.getTopLeftCornerPoint().x() == 5);
    assert(interBB.getTopLeftCornerPoint().y() == 10);
    assert(interBB.getBottomRightCornerPoint().x() == 10);
    assert(interBB.getBottomRightCornerPoint().y() == 5);
    assert(interBB.isEmpty() != true);
    std::cout << "Test of intersection operation passed" << std::endl;

    // Test of isEmpty after a void intersection result
    std::cout << "Test of empty bounding box after intersection operation" << std::endl;
    interBB = b1 ^ b3;
    assert(interBB.isEmpty() == true);
    std::cout << "Test of empty bounding box after intersection operation passed" << std::endl;

    // Test of the method isInTheBox
    std::cout << "Test of method isInTheBox" << std::endl;
    Vec2D p1 = {2,2};
    assert(b1.isInTheBox(p1) == true);
    assert(b2.isInTheBox(p1) == false);
    std::cout << "Test of method isInTheBox passed" << std::endl;

    // Test of the method getCenter
    std::cout << "Test of method getCenter" << std::endl;
    Vec2D p2 = b1.getCenter();
    assert(p2.x() == 5);
    assert(p2.y() == 5);
    std::cout << "Test of method getCenter passed" << std::endl;

    // Test of the method addPoint
    std::cout << "Test of method addpoint" << std::endl;
    b2.addPoint(p1);
    assert(b2.getTopLeftCornerPoint().x() == 2);
    assert(b2.getTopLeftCornerPoint().y() == 12);
    assert(b2.getBottomRightCornerPoint().x() == 12);
    assert(b2.getBottomRightCornerPoint().y() == 2);
    std::cout << "Test of method addPoint passed" << std::endl;


    return 0;
}
