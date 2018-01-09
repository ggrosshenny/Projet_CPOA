#ifndef __CSGNODE_H
#define __CSGNODE_H

#include <string>
#include <iostream>
#include "BoundingBox.h"

class CsgNode
{
// Attributes
protected:
    int id;
    std::string label;
    Matrix33D transformationMatrix;
    Matrix33D transformationInversedMatrix;

public:
    CsgNode* father;
    BoundingBox BBox;


public:

    virtual ~CsgNode() = default;


// Getters and setters
public:

    /**
     * @brief getId
     * @return
     */
    int getId();


    /**
     * @brief setId
     * @param id0
     */
    void setId(int id0);


    /**
     * @brief getLabel
     * @return
     */
    std::string getLabel();


    /**
     * @brief setLabel
     */
    void setLabel(std::string label0);


    /**
     * @brief setTransformationMatrix change the transformation matrix with a new one
     * @param matr
     */
    void setTransformationMatrix(Matrix33D matr);


    /**
     * @brief getTransformationMatrix return the current transformation matrix
     * @return
     */
    Matrix33D getTransformationMatrix();


    /**
     * @brief getInversedTransformationMatrix return the inversed transformation matrix
     * @return
     */
    Matrix33D getInversedTransformationMatrix();


// methods
public:


    /**
     * @brief applyLocalTransformation apply the transformation matrix on all vertices of the primitives
     */
    virtual void applyLocalTransformation() = 0;


    /**
     * @brief applyTransformation apply the given transformation matrix on all vertices of the primitives
     * @param matTransfo
     */
    virtual void applyTransformation(Matrix33D matTransfo) = 0;


    /**
     * @brief intersect return a bool to know if the given pixel can be draw or not
     * @return
     */
    virtual bool intersect(double x, double y) = 0;


    /**
     * @brief intersectBBox Apply the union/intersection/diffrence operation on two bouding boxes
     * @return
     */
    virtual bool intersectBBox(double x, double y) = 0;

};



#endif
