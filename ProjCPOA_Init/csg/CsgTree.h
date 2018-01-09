#ifndef __CSGTREE_H
#define __CSGTREE_H


#include "CsgOperation.h"
#include "CsgDisk.h"
#include "CsgRegularPolygon.h"
#include "../image/Img2DGrey.h"
#include <map>
#include <algorithm>
#include <iomanip>
#include <fstream>


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
    std::map<int, CsgNode*, classComp> nodesList;

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
     * @brief addPrimitive add the primitive of the given primitive type and the given id in the trees list. Only used by load method !
     * @param primType
     */
    int addPrimitive(enum primitiveType primType, int id);


    /**
     * @brief addPrimitive add the primitive of the given primitive type and the given id in the trees list. Only used by load method !
     * @param primType
     */
    int addPrimitive(enum primitiveType primType, int id, int nbOfVertices);


    /**
     * @brief addPrimitive add the given pritive in the trees list
     * @param primitive
     */
    void addPrimitive(CsgNode* primitive);


    /**
     * @brief addPrimitive add the given pritive in the trees list
     * @param primitive
     * @param id
     */
    void addPrimitive(CsgNode* primitive, int id);


    /**
     * @brief addPrimitive overload to make use of the method easier with a disk primitive
     * @param disk
     */
    void addPrimitive(CsgDisk* disk);


    /**
     * @brief addPrimitive overload to make use of the method easier with a disk primitive
     * @param disk
     * @param id
     */
    void addPrimitive(CsgDisk* disk, int id);


    /**
     * @brief addPrimitive overload to make use of the method easier with a regular polygon primitive
     * @param regPoly
     */
    void addPrimitive(CsgRegularPolygon* regPoly);

    /**
     * @brief addPrimitive overload to make use of the method easier with a regular polygon primitive
     * @param regPoly
     * @param id
     */
    void addPrimitive(CsgRegularPolygon* regPoly, int id);


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
     * @brief joinPrimitives join two primitives with a CsgOperation with the given operation type and the given id. Used by load method only !
     * @param firstPrimId primitive identifier
     * @param secondPrimId primitive identifier
     * @param opType
     * @return
     */
    CsgOperation* joinPrimitives(int firstPrimId, int secondPrimId, operation opType, int id);


    /**
     * @brief removeNode remove the given node from the tree and reajust tree if necessary
     * @param node
     */
    void removeNode(CsgNode* node);


    /**
     * @brief removeNode remove the given node from the tree and reajust tree if necessary
     * @param node
     */
    void removeNode(CsgOperation* node);


    /**
     * @brief removeNode remove the given node from the tree and reajust tree if necessary
     * @param node
     */
    void removeNode(CsgDisk* node);


    /**
     * @brief removeNode remove the given node from the tree and reajust tree if necessary
     * @param node
     */
    void removeNode(CsgRegularPolygon* node);


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


    /**
     * @brief drawInImage draw the current tree in the given image with the given shade of grey
     * @param img
     * @param greyScale
     */
    void drawInImage(Img2DGrey &img, int greyShade);

    /**
     * @brief drawInImage draw the current tree starting from the given node in the given image with the given shade of grey
     * @param start
     * @param img
     * @param greyShade
     */
    void drawInImage(CsgNode* start, Img2DGrey &img, int greyShade);


    /**
     * @brief clone clone the current node and its children if necessary
     * @param nodeId
     */
    CsgNode* clone(int nodeId);


    /**
     * @brief cloneAux
     * @param nodeId
     * @param lastMaxId
     * @return
     */
    CsgNode* cloneAux(int nodeId, int lastMaxId);


    /**
     * @brief clear clear the graph and remove all nodes
     */
    void clear();


// Operators overload
public:


    /**
     * @brief operator << load the CSG tree from the given file
     * @param fileName
     */
    void operator<<(std::string fileName);


    /**
     * @brief operator >> save the current CSG tree in the given file
     * @param fileName
     */
    void operator>>(std::string fileName);

};


#endif
