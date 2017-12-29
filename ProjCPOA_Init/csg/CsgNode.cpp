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
