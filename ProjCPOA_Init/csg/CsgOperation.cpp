#include "CsgOperation.h"


// ============
// Constructors


CsgOperation::CsgOperation()
{
    this->father = NULL;
    this->opType = op_union;
    this->leftChild = NULL;
    this->rightChild = NULL;
}


CsgOperation::CsgOperation(operation op0)
{
    this->opType = op0;
    this->leftChild = NULL;
    this->rightChild = NULL;
}


CsgOperation::CsgOperation(CsgNode *leftChild0, CsgNode *rightChild0, operation op0)
{
    this->opType = op0;
    this->leftChild = leftChild0;
    this->rightChild = rightChild0;
    leftChild0->father = this;
    rightChild0->father = this;
    this->updateBoundingBox();
}


// ===================
// Getters and setters


enum operation CsgOperation::getoperationType()
{
    return this->opType;
}


void CsgOperation::setOperationType(enum operation opType)
{
    this->opType = opType;
}


void CsgOperation::setChildren(CsgNode *leftChild0, CsgNode *rightChild0)
{
    this->leftChild = leftChild0;
    this->rightChild = rightChild0;
    leftChild0->father = this;
    rightChild0->father = this;

    this->updateBoundingBox();
}


// =======
// Methods


void CsgOperation::updateBoundingBox()
{
    if( (this->leftChild != NULL) && (this->rightChild != NULL) )
    {
        switch(this->opType)
        {
            case op_union:
                this->BBox = leftChild->BBox + rightChild->BBox;
                break;

            case op_inter:
                this->BBox = this->leftChild->BBox ^ this->rightChild->BBox;
                break;

            case op_diff:
                this->BBox = this->leftChild->BBox - this->rightChild->BBox;
                break;

            default:
                break;
        }
    }
    else if(this->leftChild != NULL)
    {
        this->BBox = leftChild->BBox;
    }
    else if(this->rightChild != NULL)
    {
        this->BBox = rightChild->BBox;
    }

    if(this->father != NULL)
    {
        if(dynamic_cast<CsgOperation*>(this->father) != NULL)
        {
            dynamic_cast<CsgOperation*>(this->father)->updateBoundingBox();
        }
    }
}


bool CsgOperation::intersectBBox(double x, double y)
{
    bool answ = false;
    Vec2D point(x, y);
    BoundingBox diffBB;

    if( (this->leftChild != NULL) && (this->rightChild != NULL) )
    {
        switch(this->opType)
        {
            case op_union:
                answ = this->leftChild->BBox.isInTheBox(point) || this->rightChild->BBox.isInTheBox(point);
                break;

            case op_inter:
                answ = this->leftChild->BBox.isInTheBox(point) && this->rightChild->BBox.isInTheBox(point);
                break;

            case op_diff:
                diffBB = this->leftChild->BBox - this->rightChild->BBox;
                answ = diffBB.isInTheBox(point);
                break;

            default:
                break;
        }
    }
    else if(this->leftChild != NULL)
    {
        answ = leftChild->BBox.isInTheBox(point);
    }
    else if(this->rightChild != NULL)
    {
        answ = rightChild->BBox.isInTheBox(point);
    }

    return answ;
}


bool CsgOperation::intersect(double x, double y)
{
    bool answ = false;

    // If we are in the bounding box
    if(this->intersectBBox(x, y))
    {
        if( (this->leftChild != NULL) && (this->rightChild != NULL) )
        {
            switch(this->opType)
            {
                case op_union:
                    answ = this->leftChild->intersect(x, y) || this->rightChild->intersect(x, y);
                    break;

                case op_inter:
                    answ = this->leftChild->intersect(x, y) && this->rightChild->intersect(x, y);
                    break;

                case op_diff:
                    answ = this->leftChild->intersect(x, y) || this->rightChild->intersect(x, y);
                    break;

                default:
                    break;
            }
        }
        else if(this->leftChild != NULL)
        {
            answ = leftChild->intersect(x, y);
        }
        else if(this->rightChild != NULL)
        {
            answ = rightChild->intersect(x, y);
        }
    }

    return answ;
}







