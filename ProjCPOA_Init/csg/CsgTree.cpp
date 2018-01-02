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


int CsgTree::addPrimitive(primitiveType primType)
{
    CsgDisk* newDisk = new CsgDisk();
    CsgRegularPolygon* regpoly = new CsgRegularPolygon();

    switch(primType)
    {
        case prim_disk:
            this->treesList[this->nextId] = dynamic_cast<CsgNode*>(newDisk);
            newDisk->setId(this->nextId);
            break;

        case prim_regPoly:
            this->treesList[this->nextId] = dynamic_cast<CsgNode*>(regpoly);
            regpoly->setId(this->nextId);
            break;

        default:
            break;
    }

    this->nextId++;
    return this->nextId-1;
}


void CsgTree::addPrimitive(CsgDisk* disk)
{
    this->addPrimitive(dynamic_cast<CsgNode*>(disk));
}


void CsgTree::addPrimitive(CsgRegularPolygon* regPoly)
{
    this->addPrimitive(dynamic_cast<CsgNode*>(regPoly));
}


CsgOperation* CsgTree::joinPrimitives(CsgNode *firstPrimitive, CsgNode *secondPrimitive, operation opType)
{
    CsgOperation* newOp = new CsgOperation(firstPrimitive, secondPrimitive, opType);
    newOp->setId(this->nextId);

    this->treesList.erase(this->treesList.find(firstPrimitive->getId()));
    this->treesList.erase(this->treesList.find(secondPrimitive->getId()));
    this->treesList[this->nextId] = dynamic_cast<CsgNode*>(newOp);

    this->nextId++;
    return newOp;
}


CsgOperation* CsgTree::joinPrimitives(CsgDisk* firstPrimitive, CsgDisk* secondPrimitive, operation opType)
{
    return this->joinPrimitives(dynamic_cast<CsgNode*>(firstPrimitive), dynamic_cast<CsgNode*>(secondPrimitive), opType);
}


CsgOperation* CsgTree::joinPrimitives(CsgDisk* firstPrimitive, CsgRegularPolygon* secondPrimitive, operation opType)
{
    return this->joinPrimitives(dynamic_cast<CsgNode*>(firstPrimitive), dynamic_cast<CsgNode*>(secondPrimitive), opType);
}


CsgOperation* CsgTree::joinPrimitives(CsgRegularPolygon* firstPrimitive, CsgDisk* secondPrimitive, operation opType)
{
    return this->joinPrimitives(dynamic_cast<CsgNode*>(firstPrimitive), dynamic_cast<CsgNode*>(secondPrimitive), opType);
}


CsgOperation* CsgTree::joinPrimitives(CsgRegularPolygon* firstPrimitive, CsgRegularPolygon* secondPrimitive, operation opType)
{
    return this->joinPrimitives(dynamic_cast<CsgNode*>(firstPrimitive), dynamic_cast<CsgNode*>(secondPrimitive), opType);
}

CsgOperation* CsgTree::joinPrimitives(CsgRegularPolygon* firstPrimitive, CsgOperation* secondPrimitive, operation opType)
{
    return this->joinPrimitives(dynamic_cast<CsgNode*>(firstPrimitive), dynamic_cast<CsgNode*>(secondPrimitive), opType);
}


CsgOperation* CsgTree::joinPrimitives(CsgOperation* firstPrimitive, CsgRegularPolygon* secondPrimitive, operation opType)
{
    return this->joinPrimitives(dynamic_cast<CsgNode*>(firstPrimitive), dynamic_cast<CsgNode*>(secondPrimitive), opType);
}


CsgOperation* CsgTree::joinPrimitives(CsgOperation* firstPrimitive, CsgDisk* secondPrimitive, operation opType)
{
    return this->joinPrimitives(dynamic_cast<CsgNode*>(firstPrimitive), dynamic_cast<CsgNode*>(secondPrimitive), opType);
}


CsgOperation* CsgTree::joinPrimitives(CsgDisk* firstPrimitive, CsgOperation* secondPrimitive, operation opType)
{
    return this->joinPrimitives(dynamic_cast<CsgNode*>(firstPrimitive), dynamic_cast<CsgNode*>(secondPrimitive), opType);
}


CsgOperation* CsgTree::joinPrimitives(int firstPrimId, int secondPrimId, operation opType)
{
    CsgNode* firstPrim = dynamic_cast<CsgNode*>(this->treesList[firstPrimId]);
    CsgNode* secondPrim = dynamic_cast<CsgNode*>(this->treesList[secondPrimId]);

    CsgOperation* newOp = new CsgOperation(firstPrim, secondPrim, opType);
    newOp->setId(this->nextId);

    this->treesList.erase(this->treesList.find(firstPrim->getId()));
    this->treesList.erase(this->treesList.find(secondPrim->getId()));
    this->treesList[this->nextId] = dynamic_cast<CsgNode*>(newOp);

    this->nextId++;
    return newOp;
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
                img[(img.getHeight()-1) - i][j] = (unsigned char)255;
            }
        }
    }
}
















