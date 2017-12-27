#include "BoundingBox.h"


// ============
// Constructors


BoundingBox::BoundingBox()
{
    this->topLeftCornerPoint = Vec2D();
    this->bottomRightCornerPoint = Vec2D();
    this->empty = true;
}


BoundingBox::BoundingBox(Vec2D topleft, Vec2D botRight)
{
    this->topLeftCornerPoint = topleft;
    this->bottomRightCornerPoint = botRight;
    this->empty = false;
    this->verifyPointsValidity();
}


BoundingBox::BoundingBox(std::initializer_list<double> elementsTopLeft, std::initializer_list<double> elementsBotRight)
{
    this->topLeftCornerPoint = Vec2D(elementsTopLeft);
    this->bottomRightCornerPoint = Vec2D(elementsBotRight);
    this->empty = false;
    this->verifyPointsValidity();
}


// ===================
// Getters and setters


Vec2D BoundingBox::getTopLeftCornerPoint() const
{
    return topLeftCornerPoint;
}


Vec2D BoundingBox::getBottomRightCornerPoint() const
{
    return bottomRightCornerPoint;
}


void BoundingBox::setTopLeftCornerPoint(Vec2D& newPoint)
{
    this->topLeftCornerPoint = newPoint;
    this->verifyPointsValidity();
}


void BoundingBox::setTopLeftCornerPoint(std::initializer_list<double> elementsNewVector)
{
    this->topLeftCornerPoint = Vec2D(elementsNewVector);
    this->verifyPointsValidity();
}


void BoundingBox::setBottomRightCornerPoint(Vec2D& newPoint)
{
    this->bottomRightCornerPoint = newPoint;
    this->verifyPointsValidity();
}


void BoundingBox::setBottomRightCornerPoint(std::initializer_list<double> elementsNewVector)
{
    this->bottomRightCornerPoint = Vec2D(elementsNewVector);
    this->verifyPointsValidity();
}


void BoundingBox::setIsEmpty(bool empty0)
{
    this->empty = empty0;
}


// ==================
// Operators overload


BoundingBox BoundingBox::operator +(const BoundingBox &other) const
{
    Vec2D thisTopLeftCornerPoint = this->topLeftCornerPoint;
    Vec2D thisBottomRightCornerPoint = this->bottomRightCornerPoint;

    Vec2D newTopLeftCornerPoint;
    newTopLeftCornerPoint[0] = std::min(thisTopLeftCornerPoint.x(), other.topLeftCornerPoint.x());
    newTopLeftCornerPoint[1] = std::min(thisTopLeftCornerPoint.y(), other.topLeftCornerPoint.y()); // min because (0,0) in QT is the top left point

    Vec2D newBottomRightCornerPoint;
    newBottomRightCornerPoint[0] = std::max(thisBottomRightCornerPoint.x(), other.bottomRightCornerPoint.x());
    newBottomRightCornerPoint[1] = std::max(thisBottomRightCornerPoint.y(), other.bottomRightCornerPoint.y()); // max because (0,0) in

    BoundingBox unionBoundingBox(newTopLeftCornerPoint, newBottomRightCornerPoint);

    return unionBoundingBox;
}


BoundingBox BoundingBox::operator -(const BoundingBox &other)
{
    Vec2D newTopCorner;
    Vec2D newBotCorner;

    int maxXDistance = std::max(std::abs(other.topLeftCornerPoint.x() - this->topLeftCornerPoint.x()), std::abs(other.bottomRightCornerPoint.x() - this->bottomRightCornerPoint.x()));
    int maxYDistance = std::max(std::abs(other.topLeftCornerPoint.y() - this->topLeftCornerPoint.y()), std::abs(other.bottomRightCornerPoint.y() - this->bottomRightCornerPoint.y()));

    if(maxXDistance >= maxYDistance)
    {
        if((std::abs(other.topLeftCornerPoint.x() - this->topLeftCornerPoint.x())) <= (std::abs(other.bottomRightCornerPoint.x() - this->bottomRightCornerPoint.x())))
        {
            newTopCorner = Vec2D(other.bottomRightCornerPoint.x(), this->topLeftCornerPoint.y());
            newBotCorner = this->bottomRightCornerPoint;
        }
        else
        {
            newTopCorner = this->topLeftCornerPoint;
            newBotCorner = Vec2D(other.topLeftCornerPoint.x(), this->bottomRightCornerPoint.y());
        }
    }
    else
    {
        if((std::abs(other.topLeftCornerPoint.y() - this->topLeftCornerPoint.y())) <= (std::abs(other.bottomRightCornerPoint.y() - this->bottomRightCornerPoint.y())))
        {
            newTopCorner = Vec2D(this->topLeftCornerPoint.x(), other.bottomRightCornerPoint.y());
            newBotCorner = this->bottomRightCornerPoint;
        }
        else
        {
            newTopCorner = this->topLeftCornerPoint;
            newBotCorner = Vec2D(this->bottomRightCornerPoint.x(), other.topLeftCornerPoint.y());
        }
    }

    BoundingBox differenceBoundingBox(newTopCorner, newBotCorner);

    return differenceBoundingBox;
}


BoundingBox BoundingBox::operator ^(const BoundingBox &other)
{
    bool firstBoxIsNotIntersectingSecondOne = false;
    bool secondBoxIsNotIntersectingFirstOne = false;

    Vec2D newTopLeftCornerPoint;
    newTopLeftCornerPoint[0] = std::max(this->topLeftCornerPoint.x(), other.topLeftCornerPoint.x());
    newTopLeftCornerPoint[1] = std::max(this->topLeftCornerPoint.y(), other.topLeftCornerPoint.y()); // max because (0,0) in QT is the top left point

    Vec2D newBottomRightCornerPoint;
    newBottomRightCornerPoint[0] = std::min(this->bottomRightCornerPoint.x(), other.bottomRightCornerPoint.x());
    newBottomRightCornerPoint[1] = std::min(this->bottomRightCornerPoint.y(), other.bottomRightCornerPoint.y()); // min because (0,0) in

    BoundingBox intersectionBoundingBox(newTopLeftCornerPoint, newBottomRightCornerPoint);

    firstBoxIsNotIntersectingSecondOne = !((other.topLeftCornerPoint.x() < this->bottomRightCornerPoint.x()) &&
                                           (other.topLeftCornerPoint.y() < this->bottomRightCornerPoint.y()) &&
                                           (other.bottomRightCornerPoint.x() > this->topLeftCornerPoint.x()) &&
                                           (other.bottomRightCornerPoint.y() > this->topLeftCornerPoint.y()) );

    secondBoxIsNotIntersectingFirstOne = !((this->topLeftCornerPoint.x() < other.bottomRightCornerPoint.x()) &&
                                           (this->topLeftCornerPoint.y() < other.bottomRightCornerPoint.y()) &&
                                           (this->bottomRightCornerPoint.x() > other.topLeftCornerPoint.x()) &&
                                           (this->bottomRightCornerPoint.y() > other.topLeftCornerPoint.y()) );

    if( firstBoxIsNotIntersectingSecondOne || secondBoxIsNotIntersectingFirstOne )
    {
        intersectionBoundingBox.setIsEmpty(true);
    }

    return intersectionBoundingBox;
}



// ====================
// Verification methods


void BoundingBox::verifyPointsValidity()
{
    Vec2D temp;

    if( (this->topLeftCornerPoint.x() > this->bottomRightCornerPoint.x()) && (this->topLeftCornerPoint.y() < this->bottomRightCornerPoint.y()) )
    {
        temp = this->topLeftCornerPoint;
        this->topLeftCornerPoint = this->bottomRightCornerPoint;
        this->bottomRightCornerPoint = temp;
    }
}


bool BoundingBox::isEmpty() const
{
    return this->empty;
}


bool BoundingBox::isInTheBox(Vec2D point) const
{
    return ( (point.x() >= this->topLeftCornerPoint.x())
             && (point.x() <= this->bottomRightCornerPoint.x())
             && (point.y() >= this->topLeftCornerPoint.y())
             && (point.y() <= this->bottomRightCornerPoint.y())
           );
}


Vec2D BoundingBox::getCenter() const
{
    int centerX = this->topLeftCornerPoint.x() + (this->bottomRightCornerPoint.x() - this->topLeftCornerPoint.x())/2;
    int centerY = this->topLeftCornerPoint.y() + (this->bottomRightCornerPoint.y() - this->topLeftCornerPoint.y())/2;
    Vec2D center(centerX, centerY);

    return center;
}


void BoundingBox::addPoint(Vec2D point)
{
    if(!this->isInTheBox(point))
    {
        this->topLeftCornerPoint[0] = std::min(this->topLeftCornerPoint.x(), point.x());
        this->topLeftCornerPoint[1] = std::min(this->topLeftCornerPoint.y(), point.y());
        this->bottomRightCornerPoint[0] = std::max(this->bottomRightCornerPoint.x(), point.x());
        this->bottomRightCornerPoint[1] = std::max(this->bottomRightCornerPoint.y(), point.y());
    }
}










