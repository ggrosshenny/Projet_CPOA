#ifndef __CSGTREE_H
#define __CSGTREE_H


#include "CsgOperation.h"
#include "CsgDisk.h"
#include "CsgRegularPolygon.h"
#include "../image/Img2DGrey.h"
#include <map>
#include <algorithm>


enum primitiveType{prim_disk, prim_regPoly};


struct classComp
{
    bool operator() (const int& id1, const int& id2) const
    { return id1<id2; }
};

class CsgTree
{
// Attributes
private:
    int nextId;

public:
    std::map<int, CsgNode*, classComp> treesList;

// Constructors
public:


    /**
     * @brief CsgTree default constructor
     */
    CsgTree();

// Methods
public:


    /**
     * @brief addPrimitive add the primitive of the given primitive type in the trees list
     * @param primType
     */
    int addPrimitive(enum primitiveType primType);


    /**
     * @brief addPrimitive add the given pritive in the trees list
     * @param primitive
     */
    void addPrimitive(CsgNode* primitive);


    /**
     * @brief addPrimitive overload to make use of the method easier with a disk primitive
     * @param disk
     */
    void addPrimitive(CsgDisk* disk);


    /**
     * @brief addPrimitive overload to make use of the method easier with a regular polygon primitive
     * @param regPoly
     */
    void addPrimitive(CsgRegularPolygon* regPoly);


    /**
     * @brief joinPrimitives join two primitives with a CsgOperation with the given operation type
     * @param firstPrimitive primitive pointer
     * @param secondPrimitive primitive pointer
     * @param opType
     * @return
     */
    CsgOperation* joinPrimitives(CsgNode* firstPrimitive, CsgNode* secondPrimitive, operation opType);


    /**
     * @brief joinPrimitives join two primitives with a CsgOperation with the given operation type
     * @param firstPrimitive primitive pointer
     * @param secondPrimitive primitive pointer
     * @param opType
     * @return
     */
    CsgOperation* joinPrimitives(CsgDisk* firstPrimitive, CsgDisk* secondPrimitive, operation opType);

    /**
     * @brief joinPrimitives join two primitives with a CsgOperation with the given operation type
     * @param firstPrimitive primitive pointer
     * @param secondPrimitive primitive pointer
     * @param opType
     * @return
     */
    CsgOperation* joinPrimitives(CsgDisk* firstPrimitive, CsgRegularPolygon* secondPrimitive, operation opType);


    /**
     * @brief joinPrimitives join two primitives with a CsgOperation with the given operation type
     * @param firstPrimitive primitive pointer
     * @param secondPrimitive primitive pointer
     * @param opType
     * @return
     */
    CsgOperation* joinPrimitives(CsgRegularPolygon* firstPrimitive, CsgDisk* secondPrimitive, operation opType);


    /**
     * @brief joinPrimitives join two primitives with a CsgOperation with the given operation type
     * @param firstPrimitive primitive pointer
     * @param secondPrimitive primitive pointer
     * @param opType
     * @return
     */
    CsgOperation* joinPrimitives(CsgRegularPolygon* firstPrimitive, CsgRegularPolygon* secondPrimitive, operation opType);


    /**
     * @brief joinPrimitives join two primitives with a CsgOperation with the given operation type
     * @param firstPrimitive primitive pointer
     * @param secondPrimitive primitive pointer
     * @param opType
     * @return
     */
    CsgOperation* joinPrimitives(CsgRegularPolygon* firstPrimitive, CsgOperation* secondPrimitive, operation opType);


    /**
     * @brief joinPrimitives join two primitives with a CsgOperation with the given operation type
     * @param firstPrimitive primitive pointer
     * @param secondPrimitive primitive pointer
     * @param opType
     * @return
     */
    CsgOperation* joinPrimitives(CsgOperation* firstPrimitive, CsgRegularPolygon* secondPrimitive, operation opType);


    /**
     * @brief joinPrimitives join two primitives with a CsgOperation with the given operation type
     * @param firstPrimitive primitive pointer
     * @param secondPrimitive primitive pointer
     * @param opType
     * @return
     */
    CsgOperation* joinPrimitives(CsgOperation* firstPrimitive, CsgDisk* secondPrimitive, operation opType);


    /**
     * @brief joinPrimitives join two primitives with a CsgOperation with the given operation type
     * @param firstPrimitive primitive pointer
     * @param secondPrimitive primitive pointer
     * @param opType
     * @return
     */
    CsgOperation* joinPrimitives(CsgDisk* firstPrimitive, CsgOperation* secondPrimitive, operation opType);


    /**
     * @brief joinPrimitives join two primitives with a CsgOperation with the given operation type
     * @param firstPrimId primitive identifier
     * @param secondPrimId primitive identifier
     * @param opType
     * @return
     */
    CsgOperation* joinPrimitives(int firstPrimId, int secondPrimId, operation opType);


    /**
     * @brief isPixelIntersectingTree return true if the pixel is intersecting with the tree
     * @param x
     * @param y
     */
    bool isPixelIntersectingTree(double x, double y);


    /**
     * @brief drawInImage draw the current tree in the given image
     * @param img
     */
    void drawInImage(Img2DGrey& img);

};


#endif
