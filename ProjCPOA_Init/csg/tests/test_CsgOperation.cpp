#include "CsgOperation.h"
#include "CsgDisk.h"
#include "CsgRegularPolygon.h"
#include <cassert>

int main()
{
    CsgDisk disk1;
    disk1.addTransformation(2.5, 0.0, translation);
    CsgRegularPolygon regPoly;

    Vec2D opUnionTop(-1.0, 1.0);
    Vec2D opUnionBot(1.0, -1.0);
    Vec2D opUnionTop2(-0.5, 0.5);
    Vec2D opUnionBot2(0.5, -0.5);
    Vec2D opUnionTopTransl(-0.5, 1.0);
    Vec2D opUnionBotTransl(3.5, -1.0);


    // Test of default constructor
    std::cout << "Test of CsgOperation default constructor" << std::endl;
    CsgOperation opUniondef;
    assert(opUniondef.getoperationType() == op_union);
    assert(opUniondef.BBox.getTopLeftCornerPoint() == opUnionTop);
    assert(opUniondef.BBox.getBottomRightCornerPoint() == opUnionBot);
    std::cout << "Test of CsgOperation default constructor passed" << std::endl;


    // Test of CsgOperation constructor
    std::cout << "Test of CsgOperation constructor" << std::endl;
    CsgOperation opUnion(static_cast<CsgNode*>(&disk1), static_cast<CsgNode*>(&regPoly), op_union);
    assert(opUnion.getoperationType() == op_union);
    assert(opUnion.BBox.getTopLeftCornerPoint() == opUnionTop);
    assert(opUnion.BBox.getBottomRightCornerPoint() == opUnionBot);
    CsgOperation opUnion2(NULL, static_cast<CsgNode*>(&regPoly), op_union);
    assert(opUnion2.getoperationType() == op_union);
    assert(opUnion2.BBox.getTopLeftCornerPoint() == opUnionTop2);
    assert(opUnion2.BBox.getBottomRightCornerPoint() == opUnionBot2);
    std::cout << "Test of CsgOperation constructor passed" << std::endl;

    // Test of the update of the boundingBox when a child Bbox is changed
    std::cout << "Test of CsgOperation updateBoundingBox when a child BBox is changed" << std::endl;
    disk1.applyLocalTransformation();
    assert(opUnion.getoperationType() == op_union);
    assert(opUnion.BBox.getTopLeftCornerPoint() == opUnionTopTransl);
    assert(opUnion.BBox.getBottomRightCornerPoint() == opUnionBotTransl);
    std::cout << "Test of CsgOperation updateBoundingBox when a child BBox is changed passed" << std::endl;


    // Test of intersectBBox
    std::cout << "Test of CsgOperation intersectBBox" << std::endl;
    assert(opUnion.intersectBBox(0,0));
    assert(!opUnion.intersectBBox(-1.5,0));
    std::cout << "Test of CsgOperation intersectBBox passed" << std::endl;

    // Test of intersect
    std::cout << "Test of CsgOperation intersect" << std::endl;
    assert(opUnion.intersect(0,0));
    assert(opUnion.intersect(2.5, 0.5));
    assert(!opUnion.intersect(0.6,0));
    assert(!opUnion.intersect(2.9, 0.95));
    std::cout << "Test of CsgOperation intersect passed" << std::endl;


    return 0;
}
