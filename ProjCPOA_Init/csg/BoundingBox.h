#ifndef __BOUNDINGBOX_H_
#define __BOUNDINGBOX_H_

#include <iostream>
#include "../vectorMatrix/ProjectVectors.h"


class BoundingBox
{
private:
    Vec2D topLeftCornerPoint;       // Point of the top left corner of the bounding box
    Vec2D bottomRightCornerPoint;   // Point of the bottom right corner of the bounding box
    bool empty;                     // Bool to know if the bounding box is empty or not

// Constructors
public:

    /**
     * @brief BoundingBox Default constructor of the bounding box.
     */
    BoundingBox();


    /**
     * @brief BoundingBox Constructor with given points
     * @param botleft
     * @param topRight
     */
    BoundingBox(Vec2D topleft, Vec2D botRight);


    /**
     * @brief BoundingBox Constructor with initial
     * @param elementsBotLeft
     * @param elementsTopRight
     */
    BoundingBox(std::initializer_list<double> elementsTopLeft, std::initializer_list<double> elementsBotRight);



// getter and setter
public:

    /**
     * @brief getTopLeftCornerPoint return the top left corner point
     * @return
     */
    Vec2D getTopLeftCornerPoint() const;


    /**
     * @brief getBottomRightCornerPoint return the bottom right corner point
     * @return
     */
    Vec2D getBottomRightCornerPoint() const;


    /**
     * @brief setTopLeftCornerPoint change the value of the top left corner point
     * @param newPoint
     * @return
     */
    void setTopLeftCornerPoint(Vec2D &newPoint);


    /**
     * @brief setTopLeftCornerPoint change the value of the top left corner point with initializer list
     * @param elementsNewVector
     * @return
     */
    void setTopLeftCornerPoint(std::initializer_list<double> elementsNewVector);


    /**
     * @brief setBottomRightCornerPoint change the value of the bottom right corner point
     * @param newPoint
     */
    void setBottomRightCornerPoint(Vec2D &newPoint);


    /**
     * @brief setBottomRightCornerPoint change the value of the bottom right corner point with initializer list
     * @param elementsNewVector
     */
    void setBottomRightCornerPoint(std::initializer_list<double> elementsNewVector);


    /**
     * @brief setIsEmpty change the value of the empty bool
     * @param empty0
     */
    void setIsEmpty(bool empty0);


// Operators overload
public:

    /**
     * @brief operator + return the union of two bounding boxes
     * @param other
     * @return
     */
    BoundingBox operator+(const BoundingBox &other) const;


    /**
     * @brief operator - return the difference of two bounding boxes
     * @param other
     * @return
     */
    BoundingBox operator-(const BoundingBox &other);


    /**
     * @brief operator ^ return the intersection of two bounding boxes
     * @param other
     * @return
     */
    BoundingBox operator^(const BoundingBox &other);


// verification methods
public:


    /**
     * @brief verifyPointsValidity Verify if the top left point is higher and on the left than the bottom Right point. Change points if needed.
     */
    void verifyPointsValidity();


    /**
     * @brief isEmpty return true if the bounding box is empty
     * @return
     */
    bool isEmpty() const;


    /**
     * @brief isInTheBox return true if the point is in the bounding box
     * @param point
     * @return
     */
    bool isInTheBox(Vec2D point) const;


// Manipulation methods
public:

    /**
     * @brief getCenter compute and return the center point of the bounding box
     * @return
     */
    Vec2D getCenter() const;


    /**
     * @brief addPoint resize the box to take the point inside
     * @return
     */
    void addPoint(Vec2D point);


};


#endif
