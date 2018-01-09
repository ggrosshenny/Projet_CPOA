#include "CsgPrimitive.h"


// ===========
// Constructor

CsgPrimitive::CsgPrimitive()
{
    this->father = NULL;
    this->transformationMatrix = Matrix33D().identity();
    this->transformationInversedMatrix = this->transformationMatrix.inverse();
    this->center = {0,0};
}


// ===================
// Getters and setters

void CsgPrimitive::setCenter(double x, double y)
{
    this->center[0] = x;
    this->center[1] = y;
}


Vec2D CsgPrimitive::getCenter()
{
    return this->center;
}


// =======
// Methods


bool CsgPrimitive::intersectBBox(double x, double y)
{
    Vec2D point(x, y);
    return this->BBox.isInTheBox(point);
}


void CsgPrimitive::addTransformation(Matrix33D matr)
{
    this->transformationMatrix = matr * this->transformationMatrix;
    this->transformationInversedMatrix = this->transformationMatrix.inverse();
}


void CsgPrimitive::addTransformation(double firstArg, double secondArg, enum transformation transfo)
{
    switch(transfo)
    {
        case rotation:
            this->transformationMatrix.rotate(firstArg);
            this->transformationInversedMatrix = this->transformationMatrix.inverse();
            break;
        case scale:
            this->transformationMatrix.addScale(firstArg, secondArg);
            this->transformationInversedMatrix = this->transformationMatrix.inverse();
            break;
        case translation:
            this->transformationMatrix.translate(firstArg, secondArg);
            this->transformationInversedMatrix = this->transformationMatrix.inverse();
            break;
        default :
            break;
    }
}
