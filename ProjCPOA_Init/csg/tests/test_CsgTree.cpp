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
    assert(tree.nodesList.size() == 1);
    tree.addPrimitive(regpoly);
    assert(tree.treesList.size() == 2);
    assert(tree.nodesList.size() == 2);
    tree.addPrimitive(disk2);
    assert(tree.treesList.size() == 3);
    assert(tree.nodesList.size() == 3);
    std::cout << "Test of addPrimitive passed" << std::endl;

    // Test of joinPrimitive
    std::cout << "Test of joinPrimitives" << std::endl;
    CsgOperation* opUnion1 = tree.joinPrimitives(disk1, regpoly, op_union);
    assert(tree.treesList.size() == 2);
    assert(tree.nodesList.size() == 4);
    CsgOperation* opUnion2 = tree.joinPrimitives(opUnion1, disk2, op_union);
    assert(tree.treesList.size() == 1);
    assert(tree.nodesList.size() == 5);
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
    std::cout << "Test of drawInImage passed" << std::endl;

    std::cout << "Test of drawInImage starting with a given node" << std::endl;
    Img2DGrey newImg2(20, 20);
    tree.drawInImage(opUnion1->leftChild, newImg2, 125);
    tree.drawInImage(opUnion1->rightChild, newImg2, 255);
    std::cout << newImg2 << std::endl;
    std::cout << "Test of drawInImage passed" << std::endl;

    // Test of applyTransformation in a operation node
    std::cout << "Test of transformation application resistance" << std::endl;
    opUnion2->setTransformationMatrix(Matrix33D::translation(4, 4));
    opUnion2->applyLocalTransformation();
    assert(tree.isPixelIntersectingTree(5,5));
    assert(!tree.isPixelIntersectingTree(3,3));
    opUnion2->setTransformationMatrix(Matrix33D::translation(-4, -4));
    opUnion2->applyLocalTransformation();
    std::cout << "Test of transformation application resistance passed" << std::endl;

    std::cout << "Test of removeNode" << std::endl;
    tree.removeNode(opUnion2);
    assert(tree.treesList.size() == 2);
    assert(tree.nodesList.size() == 4);
    tree.removeNode(regpoly);
    assert(opUnion1->BBox.getTopLeftCornerPoint().x() == 8);
    assert(opUnion1->BBox.getTopLeftCornerPoint().y() == 12);
    assert(opUnion1->BBox.getBottomRightCornerPoint().x() == 12);
    assert(opUnion1->BBox.getBottomRightCornerPoint().y() == 8);
    assert(tree.nodesList.size() == 3);
    std::cout << "Test of removeNode passed" << std::endl;

    // Test of load tree
    std::cout << "Test of loading a CSG tree from a file" << std::endl;
    CsgTree newTree;
    newTree << "../../../TestsRessources/CsgTrees/test_loadTree.txt";
    assert(newTree.nodesList.size() == 5);
    assert(newTree.treesList.size() == 1);
    std::cout << "Test of loading a CSG tree from a file passed" << std::endl;

    // Test of save image
    std::cout << "Test of saving a CSG tree from a file" << std::endl;
    newTree >> "../../../TestsRessources/CsgTrees/test_saveTree.txt";
    std::cout << "Test of saving a CSG tree from a file passed" << std::endl;

    // Test of clone
    std::cout << "Test of clone" << std::endl;
    newTree.clone(4);
    assert(newTree.nodesList.size() == 8);
    assert(newTree.treesList.size() == 2);
    std::cout << "Test of clone end" << std::endl;

    // Test of clear
    std::cout << "Test of clear" << std::endl;
    newTree.clear();
    assert(newTree.nodesList.size() == 0);
    assert(newTree.treesList.size() == 0);
    std::cout << "Test of clear passed" << std::endl;

    return 0;
}
