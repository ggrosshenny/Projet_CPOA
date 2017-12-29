#ifndef __CSGREGULARPOLYGON_H
#define __CSGREGULARPOLYGON_H

#include "CsgPrimitive.h"
#include "CsgOperation.h"
#include <cmath>


class CsgRegularPolygon : public virtual CsgPrimitive
{
private:
    Vec2D* vertices;
    int verticesNumber;


// Constructors
public:

    /**
     * @brief CsgRegularPolygon default contructor initialize a regular polygon with 3 vertices centered on (0,0) point
     */
    CsgRegularPolygon();


    /**
     * @brief CsgRegularPolygon initialize a regular polygon with 3 vertices centered on the given point
     * @param x
     * @param y
     */
    CsgRegularPolygon(double x, double y);


    /**
     * @brief CsgRegularPolygon intialize a regular polygon with verticesNumber of vertices centered on (0,0) point
     * @param verticesNumber
     */
    CsgRegularPolygon(int verticesNumber);


    /**
     * @brief CsgRegularPolygon intialize a regular polygon with verticesNumber of vertices centered on the given point
     * @param x
     * @param y
     * @param verticesNumber
     */
    CsgRegularPolygon(double x, double y, int verticesNumber);

// Getters and setters
public:
    Vec2D* getPtr();

// Methods
public:


    /**
     * @brief applyLocalTransformation apply the transformation matrix on all vertices of the primitives
     */
    void applyLocalTransformation();

    /**
     * @brief intersect return if the
     * @return
     */
    bool intersect(double x, double y);


    int RayIntersectEdge(double rayStartX, double rayStartY, double rayEndX, double rayEndY, double edgeStartX, double edgeStartY, double edgeEndX, double edgeEndY);


};


#endif
