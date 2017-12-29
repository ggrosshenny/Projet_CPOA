#ifndef __CSGPRIMITIVE_H
#define __CSGPRIMITIVE_H

#include "CsgNode.h"
#include "../vectorMatrix/Matrix33d.h"


enum transformation{rotation, scale, translation};


class CsgPrimitive : public virtual CsgNode
{
protected:
    Matrix33D transformationMatrix;
    Matrix33D transformationInversedMatrix;
    Vec2D center;


// Constructors
public:

    /**
     * @brief CsgPrimitive
     */
    CsgPrimitive();

// Getters and setters
public:

    /**
     * @brief setCenter change the center point coordinates
     * @param x
     * @param y
     */
    void setCenter(double x, double y);


    /**
     * @brief getCenter return the center of the polygon
     * @param x
     * @param y
     * @return
     */
    Vec2D getCenter();


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


// Methods
public:


    /**
     * @brief applyLocalTransformation apply the transformation matrix on all vertices of the primitives
     */
    virtual void applyLocalTransformation() = 0;


    /**
     * @brief intersectBBox return true if the given point is inside the bounding box of the primitive
     * @param x x-coordinate of the point
     * @param y y-coordinate of the point
     * @return
     */
    bool intersectBBox(double x, double y);


    /**
     * @brief addTransformation add the given transformation to the transformation matrix and compute the inverse of the new matrix
     * @param matr
     */
    void addTransformation(Matrix33D matr);


    /**
     * @brief addTransformation create and add the transformation to the transformation matrix
     * @param firstArg
     * @param secondArg
     */
    void addTransformation(double firstArg, double secondArg, enum transformation transfo);


};


#endif
