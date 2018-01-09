#include "CsgTree.h"


// ===========
// Constructor

CsgTree::CsgTree()
{
    this->nextId = 1;
    this->treesList = std::map<int, CsgNode*, classComp>();
    this->nodesList = std::map<int, CsgNode*, classComp>();
}


// =======
// Methods

void CsgTree::addPrimitive(CsgNode *primitive)
{
    this->treesList[this->nextId] = primitive;
    this->nodesList[this->nextId] = primitive;
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
            this->nodesList[this->nextId] = dynamic_cast<CsgNode*>(newDisk);
            newDisk->setId(this->nextId);
            break;

        case prim_regPoly:
            this->treesList[this->nextId] = dynamic_cast<CsgNode*>(regpoly);
            this->nodesList[this->nextId] = dynamic_cast<CsgNode*>(regpoly);
            regpoly->setId(this->nextId);
            break;

        default:
            break;
    }

    this->nextId++;
    return this->nextId-1;
}


int CsgTree::addPrimitive(enum primitiveType primType, int id)
{
    CsgDisk* newDisk = new CsgDisk();
    CsgRegularPolygon* regpoly = new CsgRegularPolygon();

    switch(primType)
    {
        case prim_disk:
            this->treesList[id] = dynamic_cast<CsgNode*>(newDisk);
            this->nodesList[id] = dynamic_cast<CsgNode*>(newDisk);
            newDisk->setId(id);
            break;

        case prim_regPoly:
            this->treesList[id] = dynamic_cast<CsgNode*>(regpoly);
            this->nodesList[id] = dynamic_cast<CsgNode*>(regpoly);
            regpoly->setId(id);
            break;

        default:
            break;
    }

    this->nextId = std::max(this->nextId, id);
    this->nextId++;
    return id;
}


int CsgTree::addPrimitive(enum primitiveType primType, int id, int nbOfVertices)
{
    CsgDisk* newDisk = new CsgDisk();
    CsgRegularPolygon* regpoly = new CsgRegularPolygon(nbOfVertices);

    switch(primType)
    {
        case prim_disk:
            this->treesList[id] = dynamic_cast<CsgNode*>(newDisk);
            this->nodesList[id] = dynamic_cast<CsgNode*>(newDisk);
            newDisk->setId(id);
            break;

        case prim_regPoly:
            this->treesList[id] = dynamic_cast<CsgNode*>(regpoly);
            this->nodesList[id] = dynamic_cast<CsgNode*>(regpoly);
            regpoly->setId(id);
            break;

        default:
            break;
    }

    this->nextId = std::max(this->nextId, id);
    this->nextId++;
    return id;
}


void CsgTree::addPrimitive(CsgNode* primitive, int id)
{
    this->treesList[id] = primitive;
    this->nodesList[id] = primitive;
    primitive->setId(id);
    this->nextId = std::max(this->nextId, id);
    this->nextId++;
}


void CsgTree::addPrimitive(CsgDisk* disk)
{
    this->addPrimitive(dynamic_cast<CsgNode*>(disk));
}


void CsgTree::addPrimitive(CsgDisk* disk, int id)
{
    this->addPrimitive(dynamic_cast<CsgNode*>(disk), id);
}


void CsgTree::addPrimitive(CsgRegularPolygon* regPoly)
{
    this->addPrimitive(dynamic_cast<CsgNode*>(regPoly));
}

void CsgTree::addPrimitive(CsgRegularPolygon* regPoly, int id)
{
    this->addPrimitive(dynamic_cast<CsgNode*>(regPoly), id);
}


CsgOperation* CsgTree::joinPrimitives(CsgNode *firstPrimitive, CsgNode *secondPrimitive, operation opType)
{
    CsgOperation* newOp;
    if((firstPrimitive != NULL) && (secondPrimitive != NULL) )
    {
        newOp = new CsgOperation(firstPrimitive, secondPrimitive, opType);
        newOp->setId(this->nextId);

        this->treesList.erase(this->treesList.find(firstPrimitive->getId()));
        this->treesList.erase(this->treesList.find(secondPrimitive->getId()));
        this->treesList[this->nextId] = dynamic_cast<CsgNode*>(newOp);
        this->nodesList[this->nextId] = dynamic_cast<CsgNode*>(newOp);

        this->nextId++;
        return newOp;
    }

    return NULL;
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
    CsgNode* firstPrim;
    CsgNode* secondPrim;

    if(firstPrimId != 0)
    {
        firstPrim = dynamic_cast<CsgNode*>(this->treesList[firstPrimId]);
    }
    else
    {
        firstPrim = NULL;
    }
    if(secondPrimId != 0)
    {
        secondPrim = dynamic_cast<CsgNode*>(this->treesList[secondPrimId]);
    }
    else
    {
        secondPrim = NULL;
    }


    CsgOperation* newOp = new CsgOperation(firstPrim, secondPrim, opType);
    newOp->setId(this->nextId);

    this->treesList.erase(this->treesList.find(firstPrimId));
    this->treesList.erase(this->treesList.find(secondPrimId));
    this->treesList[this->nextId] = dynamic_cast<CsgNode*>(newOp);
    this->nodesList[this->nextId] = dynamic_cast<CsgNode*>(newOp);

    this->nextId++;
    return newOp;
}


CsgOperation* CsgTree::joinPrimitives(int firstPrimId, int secondPrimId, operation opType, int id)
{
    CsgNode* firstPrim;
    CsgNode* secondPrim;

    if(firstPrimId != 0)
    {
        firstPrim = dynamic_cast<CsgNode*>(this->treesList[firstPrimId]);
    }
    else
    {
        firstPrim = NULL;
    }
    if(secondPrimId != 0)
    {
        secondPrim = dynamic_cast<CsgNode*>(this->treesList[secondPrimId]);
    }
    else
    {
        secondPrim = NULL;
    }

    CsgOperation* newOp = new CsgOperation(firstPrim, secondPrim, opType);
    newOp->setId(id);

    this->treesList.erase(this->treesList.find(firstPrimId));
    this->treesList.erase(this->treesList.find(secondPrimId));
    this->treesList[id] = dynamic_cast<CsgNode*>(newOp);
    this->nodesList[id] = dynamic_cast<CsgNode*>(newOp);

    this->nextId = std::max(this->nextId, id);
    this->nextId++;
    return newOp;
}


void CsgTree::removeNode(CsgNode* node)
{
    if(node != NULL)
    {
        // Get father node
        CsgOperation* tempFather = dynamic_cast<CsgOperation*>(node->father);

        if(dynamic_cast<CsgOperation*>(node) != NULL)
        {
            CsgOperation* tempOp = dynamic_cast<CsgOperation*>(node);
            this->treesList[tempOp->leftChild->getId()] = tempOp->leftChild;
            this->treesList[tempOp->rightChild->getId()] = tempOp->rightChild;
        }

        if(tempFather != NULL)
        {
            if(tempFather->leftChild->getId() == node->getId())
            {
                tempFather->leftChild = NULL;
            }
            else if(tempFather->rightChild->getId() == node->getId())
            {
                tempFather->rightChild = NULL;
            }
            tempFather->updateBoundingBox();
        }
        else
        {
            this->treesList.erase(node->getId());
        }

        this->nodesList.erase(node->getId());
        delete(node);
    }

}

void CsgTree::removeNode(CsgOperation* node)
{
    this->removeNode(dynamic_cast<CsgNode*>(node));
}


void CsgTree::removeNode(CsgDisk* node)
{
    this->removeNode(dynamic_cast<CsgNode*>(node));
}


void CsgTree::removeNode(CsgRegularPolygon* node)
{
    this->removeNode(dynamic_cast<CsgNode*>(node));
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


void CsgTree::drawInImage(Img2DGrey &img, int greyShade)
{
    for(unsigned int i = 0; i<img.getHeight(); i++)
    {
        for(unsigned int j =0; j<img.getWidth(); j++)
        {
            if(this->isPixelIntersectingTree(j, i))
            {
                img[(img.getHeight()-1) - i][j] = (unsigned char)greyShade;
            }
        }
    }

}


void CsgTree::drawInImage(CsgNode* start, Img2DGrey &img, int greyShade)
{
    CsgDisk* disk = dynamic_cast<CsgDisk*>(start);
    CsgRegularPolygon* regPoly = dynamic_cast<CsgRegularPolygon*>(start);
    CsgOperation* op = dynamic_cast<CsgOperation*>(start);

    if(disk != NULL)
    {
        for(unsigned int i = 0; i<img.getHeight(); i++)
        {
            for(unsigned int j =0; j<img.getWidth(); j++)
            {
                if(disk->intersect(j, i))
                {
                    img[(img.getHeight()-1) - i][j] = (unsigned char)greyShade;
                }

            }
        }
    }
    else if(regPoly != NULL)
    {
        for(unsigned int i = 0; i<img.getHeight(); i++)
        {
            for(unsigned int j =0; j<img.getWidth(); j++)
            {
                if(regPoly->intersect(j, i))
                {
                    img[(img.getHeight()-1) - i][j] = (unsigned char)greyShade;
                }

            }
        }
    }
    else if(op != NULL)
    {
        for(unsigned int i = 0; i<img.getHeight(); i++)
        {
            for(unsigned int j =0; j<img.getWidth(); j++)
            {
                if(op->intersect(j, i))
                {
                    img[(img.getHeight()-1) - i][j] = (unsigned char)greyShade;
                }

            }
        }
    }

}


CsgNode* CsgTree::clone(int nodeId)
{
    CsgNode* node;
    if(this->nodesList.find(nodeId) == this->nodesList.end())
    {
        return NULL;
    }
    else
    {
        node = this->nodesList[nodeId];
    }
    CsgDisk* disk;
    CsgRegularPolygon* regPoly;
    CsgOperation* opNode;
    CsgDisk* newDisk;
    CsgRegularPolygon* newRegPoly;
    CsgNode* leftChild;
    CsgNode* rightChild;
    CsgOperation* op;

    if((disk = dynamic_cast<CsgDisk*>(node)) != NULL)
    {
        newDisk = new CsgDisk(disk->getCenter().x(), disk->getCenter().y(), disk->getRadius());
        newDisk->setTransformationMatrix(disk->getTransformationMatrix());

        this->addPrimitive(newDisk);
        node = dynamic_cast<CsgNode*>(newDisk);
        return node;
    }
    else if((regPoly = dynamic_cast<CsgRegularPolygon*>(node)) != NULL)
    {
        newRegPoly = new CsgRegularPolygon(regPoly->getCenter().x(), regPoly->getCenter().y(), regPoly->getVerticesNumber());
        newRegPoly->setTransformationMatrix(regPoly->getTransformationMatrix());
        this->addPrimitive(newRegPoly);
        node = dynamic_cast<CsgNode*>(newRegPoly);
        return node;
    }
    else if((opNode = dynamic_cast<CsgOperation*>(node)) != NULL)
    {
        leftChild = this->clone(opNode->leftChild->getId());
        rightChild = this->clone(opNode->rightChild->getId());

        op = this->joinPrimitives(leftChild->getId(), rightChild->getId(), opNode->getoperationType());
        node = dynamic_cast<CsgNode*>(op);
        return node;
    }
    else
    {
        return NULL;
    }
}



void CsgTree::clear()
{
    for(auto it = this->nodesList.begin(); it != this->nodesList.end(); ++it)
    {
        if(this->treesList.find(it->first) != this->treesList.end())
        {
            this->treesList.erase(it->first);
        }

        if(it->first != 0)
        {
            delete(it->second);
        }
        this->nodesList.erase(it->first);
    }
}


// ==================
// Operators overload


void CsgTree::operator<<(std::string fileName)
{
    int lastMaxId = this->nextId;
    // Used to read file
    std::ifstream loadFile;
    std::string readLineString;
    std::stringstream readLineStringStream;
    // Current node informations
    std::string currentNodeType;
    int currentNodeId = 0;
    int currentNodeNbOfVertices = 0;
    int currentNodeLeftChildId = 0;
    int currentNodeRightChildId = 0;
    // Current node transformation matrix
    double transfMat00 = 0;
    double transfMat01 = 0;
    double transfMat02 = 0;
    double transfMat10 = 0;
    double transfMat11 = 0;
    double transfMat12 = 0;
    double transfMat20 = 0;
    double transfMat21 = 0;
    double transfMat22 = 0;
    // List of operations that could not be created during the file reading
    std::vector<std::string> operations;
    // Temporary variables
    CsgNode* currentNode;


    loadFile.open(fileName);

    // --------------------
    // Checking procedures

    // Check if the file was successfully opened
    if(!loadFile.is_open())
    {
        std::cerr << "File " << fileName << " was not successfully opened" << std::endl;
        exit(1);
    }

    // Check if file is not empty
    if(!std::getline(loadFile, readLineString))
    {
       std::cerr << "File " << fileName << " is emtpy" << std::endl;
       exit(1);
    }

    // Check if file is a PGM file (i.e check if the magic number is P2)
    if(readLineString.compare("CSG_File") != 0)
    {
        std::cerr << "File " << fileName << " is not int PGM format (the magic number is not P2)" << std::endl;
        exit(1);
    }

    // ----------------------------------
    // Get values of the CSG tree to load

    int i = 0;
    while(std::getline(loadFile, readLineString))
    {
        // Get the whole block
        readLineStringStream << readLineString;
        std::getline(loadFile, readLineString);
        readLineStringStream << " " << readLineString;
        std::getline(loadFile, readLineString);
        readLineStringStream << " " << readLineString;
        std::getline(loadFile, readLineString);
        readLineStringStream << " " << readLineString;
        if(i > 0)
        {
            std::getline(loadFile, readLineString);
            readLineStringStream << " " << readLineString;
        }
        i++;

        readLineStringStream >> currentNodeId;
        readLineStringStream >> currentNodeType;

        if((currentNodeType == "Union") || (currentNodeType == "Difference") || (currentNodeType == "Intersection") )
        {
            readLineStringStream >> currentNodeLeftChildId;
            readLineStringStream >> currentNodeRightChildId;

            if((this->nodesList.find(lastMaxId + currentNodeLeftChildId) != this->nodesList.end()) && (this->nodesList.find(lastMaxId + currentNodeRightChildId) != this->nodesList.end()))
            {
                if(currentNodeType == "Union")
                {
                    this->joinPrimitives(lastMaxId + currentNodeLeftChildId, lastMaxId + currentNodeRightChildId, op_union, lastMaxId + currentNodeId);
                }
                else if(currentNodeType == "Difference")
                {
                    this->joinPrimitives(lastMaxId + currentNodeLeftChildId, lastMaxId + currentNodeRightChildId, op_diff, lastMaxId + currentNodeId);
                }
                else if(currentNodeType == "Intersection")
                {
                    this->joinPrimitives(lastMaxId + currentNodeLeftChildId, lastMaxId + currentNodeRightChildId, op_inter, lastMaxId + currentNodeId);
                }
            }
            else
            {
                readLineStringStream.seekg(0, readLineStringStream.beg);
                operations.push_back(readLineStringStream.str());
            }

        }
        else
        {
            if(currentNodeType == "Polygon")
            {
                // Get node's information
                readLineStringStream >> currentNodeNbOfVertices;
            }

            // Get node's transformation matrix
            readLineStringStream >> transfMat00;
            readLineStringStream >> transfMat01;
            readLineStringStream >> transfMat02;
            readLineStringStream >> transfMat10;
            readLineStringStream >> transfMat11;
            readLineStringStream >> transfMat12;
            readLineStringStream >> transfMat20;
            readLineStringStream >> transfMat21;
            readLineStringStream >> transfMat22;

            if(currentNodeType == "Polygon")
            {
                this->addPrimitive(prim_regPoly, lastMaxId + currentNodeId, currentNodeNbOfVertices);
                currentNode = this->nodesList[lastMaxId + currentNodeId];
                dynamic_cast<CsgRegularPolygon*>(currentNode)->setTransformationMatrix(Matrix33D({{transfMat00, transfMat01, transfMat02}, {transfMat10, transfMat11, transfMat12}, {transfMat20, transfMat21, transfMat22}}));
            }
            else if(currentNodeType == "Disk")
            {
                this->addPrimitive(prim_disk, lastMaxId + currentNodeId);
                currentNode = this->nodesList[lastMaxId + currentNodeId];
                dynamic_cast<CsgDisk*>(currentNode)->setTransformationMatrix(Matrix33D({{transfMat00, transfMat01, transfMat02}, {transfMat10, transfMat11, transfMat12}, {transfMat20, transfMat21, transfMat22}}));
            }
        }
        readLineStringStream = std::stringstream();
    }

    // Create operations that could not be created before
    while(operations.size() > 0)
    {
        for(unsigned int i = 0; i < operations.size(); i++)
        {
            readLineStringStream.str(operations[i]);
            readLineStringStream >> currentNodeId;
            readLineStringStream >> currentNodeType;

            readLineStringStream >> currentNodeLeftChildId;
            readLineStringStream >> currentNodeRightChildId;

            if((this->nodesList.find(lastMaxId + currentNodeLeftChildId) != this->nodesList.end()) && (this->nodesList.find(lastMaxId + currentNodeRightChildId) != this->nodesList.end()))
            {
                if(currentNodeType == "Union")
                {
                    this->joinPrimitives(lastMaxId + currentNodeLeftChildId, lastMaxId + currentNodeRightChildId, op_union, lastMaxId + currentNodeId);
                }
                else if(currentNodeType == "Difference")
                {
                    this->joinPrimitives(lastMaxId + currentNodeLeftChildId, lastMaxId + currentNodeRightChildId, op_diff, lastMaxId + currentNodeId);
                }
                else if(currentNodeType == "Intersection")
                {
                    this->joinPrimitives(lastMaxId + currentNodeLeftChildId, lastMaxId + currentNodeRightChildId, op_inter, lastMaxId + currentNodeId);
                }
                operations.erase(operations.begin()+i);
            }
        }
    }
    loadFile.close();
}



void CsgTree::operator>>(std::string fileName)
{
    std::ofstream csgTreeFile;
    CsgOperation* opNode;
    CsgDisk* disk;
    CsgRegularPolygon* regPoly;

    csgTreeFile.open(fileName);

    // --------------------
    // Checking procedures

    // Check if the file was successfully opened
    if(!csgTreeFile.is_open())
    {
        std::cerr << "File " << fileName << " was not successfully opened or created" << std::endl;
        exit(1);
    }

    // Create header
    csgTreeFile << "CSG_File" << std::endl;

    // Write data

    for(auto it = this->nodesList.begin(); it != this->nodesList.end(); ++it)
    {
        if(dynamic_cast<CsgOperation*>(it->second) != NULL)
        {
            opNode = dynamic_cast<CsgOperation*>(it->second);
            csgTreeFile << opNode->getId() << " ";

            switch(opNode->getoperationType())
            {
                case op_union :
                    csgTreeFile << "Union ";
                    break;
                case op_inter :
                    csgTreeFile << "Intersection ";
                    break;
                case op_diff :
                    csgTreeFile << "Difference ";
                    break;
            }

            if(opNode->leftChild != NULL)
            {
                csgTreeFile << opNode->leftChild->getId();
            }
            else
            {
                csgTreeFile << "0";
            }

            if(opNode->rightChild != NULL)
            {
                csgTreeFile << " " << opNode->rightChild->getId() << std::endl;
            }
            else
            {
                csgTreeFile << " 0" << std::endl;
            }

            csgTreeFile << "1 0 0" << std::endl;
            csgTreeFile << "0 1 0" << std::endl;
            csgTreeFile << "0 0 1" << std::endl;
        }

        else if(dynamic_cast<CsgDisk*>(it->second) != NULL)
        {
            disk = dynamic_cast<CsgDisk*>(it->second);
            csgTreeFile << disk->getId() << " Disk" << std::endl;
            csgTreeFile << disk->getTransformationMatrix()[0][0] << " " << disk->getTransformationMatrix()[0][1] << " " << disk->getTransformationMatrix()[0][2] << std::endl;
            csgTreeFile << disk->getTransformationMatrix()[1][0] << " " << disk->getTransformationMatrix()[1][1] << " " << disk->getTransformationMatrix()[1][2] << std::endl;
            csgTreeFile << disk->getTransformationMatrix()[2][0] << " " << disk->getTransformationMatrix()[2][1] << " " << disk->getTransformationMatrix()[2][2] << std::endl;
        }

        else if(dynamic_cast<CsgRegularPolygon*>(it->second) != NULL)
        {
            regPoly = dynamic_cast<CsgRegularPolygon*>(it->second);
            csgTreeFile << regPoly->getId() << " Polygon " << regPoly->getVerticesNumber() << std::endl;
            csgTreeFile << regPoly->getTransformationMatrix()[0][0] << " " << regPoly->getTransformationMatrix()[0][1] << " " << regPoly->getTransformationMatrix()[0][2] << std::endl;
            csgTreeFile << regPoly->getTransformationMatrix()[1][0] << " " << regPoly->getTransformationMatrix()[1][1] << " " << regPoly->getTransformationMatrix()[1][2] << std::endl;
            csgTreeFile << regPoly->getTransformationMatrix()[2][0] << " " << regPoly->getTransformationMatrix()[2][1] << " " << regPoly->getTransformationMatrix()[2][2] << std::endl;
        }

        csgTreeFile << "\n";
    }

    csgTreeFile.close();
}












