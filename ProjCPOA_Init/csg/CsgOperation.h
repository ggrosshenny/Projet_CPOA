#ifndef __CSGOPERATION_H
#define __CSGOPERATION_H

#include "CsgNode.h"
#include "CsgDisk.h"
#include "CsgRegularPolygon.h"

enum operation{op_union, op_inter, op_diff};

class CsgOperation : public virtual CsgNode
{
private:
    enum operation opType;

public:
    CsgNode* leftChild;
    CsgNode* rightChild;

// Constructors
public:


    /**
     * @brief CsgOperation default constructor with both children NULL and union operation
     */
    CsgOperation();


    /**
     * @brief CsgOperation constructor with both children NULL and given operation
     * @param op0
     */
    CsgOperation(enum operation op0);


    /**
     * @brief CsgOperation constructor with given children and operation
     * @param leftChild0
     * @param rightChild0
     * @param op0
     */
    CsgOperation(CsgNode* leftChild0, CsgNode* rightChild0, enum operation op0);


    ~CsgOperation() {}

// Getters and setters
public:


    /**
     * @brief getoperationType return the current operation type
     * @return
     */
    enum operation getoperationType();


    /**
     * @brief setOperationType change the operation type
     */
    void setOperationType(enum operation opType);


    /**
     * @brief setChildren change children of the node and update the bounding box
     * @param leftChild0
     * @param rightChild0
     */
    void setChildren(CsgNode *leftChild0, CsgNode *rightChild0);


// Methods
public:


    /**
     * @brief applyLocalTransformation apply the transformation matrix on children
     */
    void applyLocalTransformation();


    /**
     * @brief applyTransformation apply the given transformation matrix on children
     * @param matTransfo
     */
    void applyTransformation(Matrix33D matTransfo);


    /**
     * @brief updateBoundingBox update the boundingBox of the node
     */
    void updateBoundingBox();


    /**
     * @brief intersectBBox return true if the point is inside the boundingbox created by the operation
     * @param x x-coordinate of the point
     * @param y y-coordinate of the point
     * @return
     */
    bool intersectBBox(double x, double y);


    /**
     * @brief intersect return true if the point is inside one of the primitive or in one of the operation node in children
     * @return
     */
    bool intersect(double x, double y);

};

#endif
