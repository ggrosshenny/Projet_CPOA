#include <cassert>
#include "CsgTree.h"


int main()
{
    CsgDisk* disk1 = new CsgDisk();
    disk1->setLabel("disk1");
    CsgRegularPolygon* regpoly = new CsgRegularPolygon();
    regpoly->setLabel("regPoly");
    CsgDisk* disk2 = new CsgDisk();
    disk2->setLabel("disk2");


    CsgTree tree;


    // Test of addPrimitive
    std::cout << "Test of addPrimitive" << std::endl;
    tree.addPrimitive(disk1);
    assert(tree.treesList.size() == 1);
    tree.addPrimitive(regpoly);
    assert(tree.treesList.size() == 2);
    tree.addPrimitive(disk2);
    assert(tree.treesList.size() == 3);
    std::cout << "Test of addPrimitive passed" << std::endl;

    // Test of joinPrimitive
    std::cout << "Test of joinPrimitives" << std::endl;
    CsgOperation* opUnion1 = tree.joinPrimitives(disk1, regpoly, op_union);
    assert(tree.treesList.size() == 2);
    tree.joinPrimitives(opUnion1, disk2, op_union);
    assert(tree.treesList.size() == 1);
    std::cout << "Test od joinPrimitives passed" << std::endl;

    // Test of isPixelIntersectingTree
    std::cout << "Test of isPixelIntersectingTree" << std::endl;
    disk1->addTransformation(2, 2, scale);
    disk1->addTransformation(10, 10, translation);
    disk1->applyLocalTransformation();
    disk2->addTransformation(10, 3, translation);
    disk2->applyLocalTransformation();
    regpoly->addTransformation(10, 10, scale);
    regpoly->addTransformation(3, 3, translation);
    regpoly->applyLocalTransformation();

    assert(tree.isPixelIntersectingTree(3,3));
    assert(tree.isPixelIntersectingTree(10, 3.5));
    assert(!tree.isPixelIntersectingTree(0,8));
    assert(!tree.isPixelIntersectingTree(10,7));
    std::cout << "Test of isPixelIntersectingTree passed" << std::endl;

    std::cout << "Test of drawInImage" << std::endl;
    Img2DGrey newImg(20, 20);
    tree.drawInImage(newImg);
    std::cout << newImg << std::endl;


    return 0;
}
