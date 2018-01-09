#ifndef __CSGDISK_H
#define __CSGDISK_H

#include "CsgPrimitive.h"
#include "CsgOperation.h"

class CsgDisk : public virtual CsgPrimitive
{
// Attributes
private:
    double radius;

// Constructors
public:

    /**
     * @brief CsgDisk default constructor, intialize a disk with radius = 1 and centered at (0,0) point
     */
    CsgDisk();


    /**
     * @brief CsgDisk intialize a disk with radius = 1 and centered at (x,y) point
     * @param x
     * @param y
     */
    CsgDisk(double x, double y);


    /**
     * @brief CsgDisk intialize a disk with the given radius and centered at (0,0) point
     * @param radius
     */
    CsgDisk(double radius);


    /**
     * @brief CsgDisk intialize a disk with the given radius and centered at (x,y) point
     * @param x
     * @param y
     * @param radius
     */
    CsgDisk(double x, double y, double radius);

    ~CsgDisk() {}


public:


    /**
     * @brief applyLocalTransformation apply the transformation matrix on the disk
     */
    void applyLocalTransformation();


    /**
     * @brief applyTransformation apply the given transformation matrix on all vertices of the primitives
     * @param matTransfo
     */
    void applyTransformation(Matrix33D matTransfo);


    /**
     * @brief intersect return if the
     * @return
     */
    bool intersect(double x, double y);


    /**
     * @brief getRadius return radius
     * @return
     */
    double getRadius();

};

#endif
