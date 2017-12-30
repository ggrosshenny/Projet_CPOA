#include "CsgTree.h"


// ===========
// Constructor

CsgTree::CsgTree()
{
    this->nextId = 0;
    this->treesList = std::map<int, CsgNode*, classComp>();
}


// =======
// Methods

void CsgTree::addPrimitive(CsgNode *primitive)
{
    this->treesList[this->nextId] = primitive;
    primitive->setId(this->nextId);
    this->nextId++;
}


void CsgTree::addPrimitive(primitiveType primType)
{
    CsgDisk newDisk;
    CsgRegularPolygon regpoly;

    switch(primType)
    {
        case prim_disk:
            this->treesList[this->nextId] = dynamic_cast<CsgNode*>(&newDisk);
            newDisk.setId(this->nextId);
            break;

        case prim_regPoly:
            this->treesList[this->nextId] = dynamic_cast<CsgNode*>(&regpoly);
            regpoly.setId(this->nextId);
            break;

        default:
            break;
    }

    this->nextId++;
}


void CsgTree::joinPrimitives(CsgNode *firstPrimitive, CsgNode *secondPrimitive, operation opType)
{
    CsgOperation newOp(firstPrimitive, secondPrimitive, opType);
    newOp.setId(this->nextId);

    this->treesList.erase(this->treesList.find(firstPrimitive->getId()));
    this->treesList.erase(this->treesList.find(secondPrimitive->getId()));
    this->treesList[this->nextId] = dynamic_cast<CsgNode*>(&newOp);

    this->nextId++;
}


void CsgTree::joinPrimitives(int firstPrimId, int secondPrimId, operation opType)
{
    CsgNode* firstPrim = dynamic_cast<CsgNode*>(this->treesList[firstPrimId]);
    CsgNode* secondPrim = dynamic_cast<CsgNode*>(this->treesList[secondPrimId]);

    CsgOperation newOp(firstPrim, secondPrim, opType);
    newOp.setId(this->nextId);

    this->treesList.erase(this->treesList.find(firstPrim->getId()));
    this->treesList.erase(this->treesList.find(secondPrim->getId()));
    this->treesList[this->nextId] = dynamic_cast<CsgNode*>(&newOp);

    this->nextId++;
}


bool CsgTree::isPixelIntersectingTree(double x, double y)
{
    bool isIntersecting = false;

    for(auto it = this->treesList.begin(); (it != this->treesList.end()) && !isIntersecting; ++it)
    {
        if(dynamic_cast<CsgDisk*>(it->second) != NULL)
        {
            isIntersecting = dynamic_cast<CsgDisk*>(it->second)->intersect(x, y);
        }
        else if(dynamic_cast<CsgRegularPolygon*>(it->second) != NULL)
        {
            isIntersecting = dynamic_cast<CsgRegularPolygon*>(it->second)->intersect(x, y);
        }
        else if(dynamic_cast<CsgOperation*>(it->second) != NULL)
        {
            isIntersecting = dynamic_cast<CsgOperation*>(it->second)->intersect(x, y);
        }
    }

    return isIntersecting;
}


void CsgTree::drawInImage(Img2DGrey &img)
{

    for(unsigned int i = 0; i<img.getHeight(); i++)
    {
        for(unsigned int j =0; j<img.getWidth(); j++)
        {
            if(this->isPixelIntersectingTree(j, i))
            {
                img[i][j] = (unsigned char)255;
            }
        }
    }
}
















