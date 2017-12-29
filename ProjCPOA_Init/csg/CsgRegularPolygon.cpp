#include "CsgRegularPolygon.h"


// ============
// Constructors

CsgRegularPolygon::CsgRegularPolygon() : CsgPrimitive()
{
    double x = 0.0;
    double y = 0.0;
    this->vertices = new Vec2D[3];

    for(int i = 0; i<3; i++)
    {
        x = (std::cos((2*i*M_PI)/3))/2;
        y = (std::sin((2*i*M_PI)/3))/2;
        this->vertices[i] = Vec2D(x, y);
    }

    this->BBox = BoundingBox({-0.5, 0.5}, {0.5, -0.5});

    this->verticesNumber = 3;
}


CsgRegularPolygon::CsgRegularPolygon(double x, double y) : CsgPrimitive()
{
    double xV = 0.0;
    double yV = 0.0;
    this->vertices = new Vec2D[3];
    this->verticesNumber = 3;
    this->setCenter(x, y);
    this->BBox = BoundingBox({x-0.5, y+0.5}, {x+0.5, y-0.5});

    for(int i = 0; i<3; i++)
    {
        xV = (x + std::cos((2*i*M_PI)/3))/2;
        yV = (y + std::sin((2*i*M_PI)/3))/2;
        this->vertices[i] = Vec2D(xV, yV);
    }
}


CsgRegularPolygon::CsgRegularPolygon(int verticesNumber) : CsgPrimitive()
{
    double xV = 0.0;
    double yV = 0.0;
    this->vertices = new Vec2D[verticesNumber];
    this->verticesNumber = verticesNumber;
    this->BBox = BoundingBox({-0.5, 0.5}, {0.5, -0.5});

    for(int i = 0; i<verticesNumber; i++)
    {
        xV = (std::cos((2*i*M_PI)/verticesNumber))/2;
        yV = (std::sin((2*i*M_PI)/verticesNumber))/2;
        this->vertices[i] = Vec2D(xV, yV);
    }
}


CsgRegularPolygon::CsgRegularPolygon(double x, double y, int verticesNumber) : CsgPrimitive()
{
    double xV = 0.0;
    double yV = 0.0;
    this->vertices = new Vec2D[verticesNumber];
    this->verticesNumber = verticesNumber;
    this->setCenter(x, y);
    this->BBox = BoundingBox({x - 0.5, y + 0.5}, {x + 0.5, y-0.5});

    for(int i = 0; i<verticesNumber; i++)
    {
        xV = (x + std::cos((2*i*M_PI)/verticesNumber))/2;
        yV = (y + std::sin((2*i*M_PI)/verticesNumber))/2;
        this->vertices[i] = Vec2D(xV, yV);
    }
}


// ===================
// Getters and setters

Vec2D* CsgRegularPolygon::getPtr()
{
    return this->vertices;
}


// =======
// Methods


void CsgRegularPolygon::applyLocalTransformation()
{
    Vec2D newTopCorner = this->BBox.getTopLeftCornerPoint();
    Vec2D newBotCorner = this->BBox.getBottomRightCornerPoint();

    for(int i=0; i<this->verticesNumber; i++)
    {
        vertices[i] = this->transformationMatrix * vertices[i];
    }

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


bool CsgRegularPolygon::intersect(double x, double y)
{
    bool answ = false;
    int count = 0;
    double rayStartX = this->BBox.getTopLeftCornerPoint().x() - 0.5;
    double rayStartY = this->BBox.getTopLeftCornerPoint().y()/2;
    double edgeStartX = 0.0;
    double edgeStartY = 0.0;
    double edgeEndX = 0.0;
    double edgeEndY = 0.0;

    if(this->intersectBBox(x, y))
    {
        for(int i = 0; i<this->verticesNumber; i++)
        {
            edgeStartX = this->vertices[i].x();
            edgeStartY = this->vertices[i].y();

            if(i == this->verticesNumber-1)
            {
                edgeEndX = this->vertices[0].x();
                edgeEndY = this->vertices[0].y();
            }
            else
            {
                edgeEndX = this->vertices[i+1].x();
                edgeEndY = this->vertices[i+1].y();
            }

            count += this->RayIntersectEdge(rayStartX, rayStartY, x, y, edgeStartX, edgeStartY, edgeEndX, edgeEndY);
        }
        answ = count%2 == 1;
    }


    return answ;
}


int CsgRegularPolygon::RayIntersectEdge(double rayStartX, double rayStartY, double rayEndX, double rayEndY, double edgeStartX, double edgeStartY, double edgeEndX, double edgeEndY)
{
    float d1, d2;
    float a1, a2, b1, b2, c1, c2;

    // Create the infinite ray
    a1 = rayEndY - rayStartY;
    b1 = rayStartX - rayEndX;
    c1 = (rayEndX * rayStartY) - (rayStartX * rayEndY);

    // Insert begin and end of the edge in the ray equation
    d1 = (a1 * edgeStartX) + (b1 * edgeStartY) + c1;
    d2 = (a1 * edgeEndX) + (b1 * edgeEndY) + c1;

    // If d1 and d2 both have the same sign, they are both on the same side
    // of our line 1 and in that case no intersection is possible
    if (d1 > 0 && d2 > 0) return 0;
    if (d1 < 0 && d2 < 0) return 0;

    // Verify if the edge intersects the finite part of the ray and not before
    // the beginning of the ray of after its end
    a2 = edgeEndY - edgeStartY;
    b2 = edgeStartX - edgeEndX;
    c2 = (edgeEndX * edgeStartY) - (edgeStartX * edgeEndY);

    // Insert begin and end of the ray in the edge equation
    d1 = (a2 * rayStartX) + (b2 * rayStartY) + c2;
    d2 = (a2 * rayEndX) + (b2 * rayEndY) + c2;

    // Again, if both have the same sign, no intersection is possible.
    if (d1 > 0 && d2 > 0) return 0;
    if (d1 < 0 && d2 < 0) return 0;

    // Find if vectors are colinear or not
    if ((a1 * b2) - (a2 * b1) == 0.0f) return 2;

    // If they are not collinear
    return 1;
}


