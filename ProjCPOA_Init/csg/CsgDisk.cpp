#include "CsgDisk.h"


// ============
// Constructors

CsgDisk::CsgDisk() : CsgPrimitive()
{
    this->label = "Disk";
    this->BBox = BoundingBox({-1.0, 1.0}, {1.0, -1.0});
    this->radius = 1.0;
}


CsgDisk::CsgDisk(double radius) : CsgPrimitive()
{
    this->label = "Disk";
    this->BBox = BoundingBox({-radius, radius}, {radius, -radius});
    this->radius = radius;
}


CsgDisk::CsgDisk(double x, double y) : CsgPrimitive()
{
    this->label = "Disk";
    this->BBox = BoundingBox({x-1.0, y+1.0}, {x+1.0, y-1.0});
    this->setCenter(x, y);
    this->radius = 1.0;
}


CsgDisk::CsgDisk(double x, double y, double radius) : CsgPrimitive()
{
    this->label = "Disk";
    this->BBox = BoundingBox({x-radius, y+radius}, {x+radius, y-radius});
    this->setCenter(x, y);
    this->radius = radius;
}


void CsgDisk::applyLocalTransformation()
{
    Vec2D pointOnCircle = Vec2D(this->center.x(), (this->center.y() + this->radius) );
    Vec2D newTopCorner = this->BBox.getTopLeftCornerPoint();
    Vec2D newBotCorner = this->BBox.getBottomRightCornerPoint();

    this->center = this->transformationMatrix * this->center;
    pointOnCircle = this->transformationMatrix * pointOnCircle;

    this->radius = std::sqrt( std::pow((pointOnCircle.x() - this->center.x()), 2) + std::pow((pointOnCircle.y() - this->center.y()), 2) ) ;

    newTopCorner = this->transformationMatrix * newTopCorner;
    newBotCorner = this->transformationMatrix * newBotCorner;

    this->BBox.setTopLeftCornerPoint(newTopCorner);
    this->BBox.setBottomRightCornerPoint(newBotCorner);

    if(this->father != NULL)
    {
        if(dynamic_cast<CsgOperation*>(this->father) != NULL)
        {
            dynamic_cast<CsgOperation*>(this->father)->updateBoundingBox();
        }
    }
}


void CsgDisk::applyTransformation(Matrix33D matTransfo)
{
    Vec2D pointOnCircle = Vec2D(this->center.x(), (this->center.y() + this->radius) );
    Vec2D newTopCorner = this->BBox.getTopLeftCornerPoint();
    Vec2D newBotCorner = this->BBox.getBottomRightCornerPoint();

    this->center = matTransfo * this->center;
    pointOnCircle = matTransfo * pointOnCircle;

    this->radius = std::sqrt( std::pow((pointOnCircle.x() - this->center.x()), 2) + std::pow((pointOnCircle.y() - this->center.y()), 2) ) ;

    newTopCorner = matTransfo * newTopCorner;
    newBotCorner = matTransfo * newBotCorner;

    this->BBox.setTopLeftCornerPoint(newTopCorner);
    this->BBox.setBottomRightCornerPoint(newBotCorner);

    if(this->father != NULL)
    {
        if(dynamic_cast<CsgOperation*>(this->father) != NULL)
        {
            dynamic_cast<CsgOperation*>(this->father)->updateBoundingBox();
        }
    }
}


double CsgDisk::getRadius()
{
    return this->radius;
}


bool CsgDisk::intersect(double x, double y)
{
    bool answ = false;

    if(this->intersectBBox(x, y))
    {
        double pointDistance = std::sqrt(std::pow( x - this->center.x() , 2) +  std::pow( y - this->center.y() , 2));
        answ = (pointDistance <= this->radius);
    }

    return answ;
}
