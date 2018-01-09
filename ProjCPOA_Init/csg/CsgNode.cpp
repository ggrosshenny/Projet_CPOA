#include "CsgNode.h"


int CsgNode::getId()
{
    return this->id;
}

void CsgNode::setId(int id0)
{
    this->id = id0;
}

std::string CsgNode::getLabel()
{
    return this->label;
}

void CsgNode::setLabel(std::string label0)
{
    this->label = label0;
}


void CsgNode::setTransformationMatrix(Matrix33D matr)
{
    this->transformationMatrix = matr;
    this->transformationInversedMatrix = matr.inverse();
}


Matrix33D CsgNode::getTransformationMatrix()
{
    return this->transformationMatrix;
}


Matrix33D CsgNode::getInversedTransformationMatrix()
{
    return this->transformationInversedMatrix;
}
