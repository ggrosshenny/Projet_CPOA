#include "Matrix33d.h"
#include <cmath>


// ------------
// Constructors

Matrix33D::Matrix33D()
{
    int i = 0;
    int j = 0;

    for(i=0; i<3; i++)
    {
        for(j=0; j<3; j++)
        {
            this->data[i][j] = 0.0;
        }
    }

    this->data[2][2] = 1.0;
}


Matrix33D::Matrix33D(std::initializer_list<std::initializer_list<double>> elements)
{
    int i = 0;
    int j = 0;

    for(i=0; i<3; i++)
    {
        for(j=0; j<3; j++)
        {
            this->data[i][j] = 0.0;
        }
    }

    this->data[2][2] = 1.0;

    i=0;
    j=0;

    for(auto it = elements.begin(); it != elements.end(); ++it)
    {
        if(i < 3)
        {
            for(auto subIt = it->begin(); subIt != it->end(); ++subIt)
            {
                if(j<3)
                {
                    data[i][j] = *subIt;
                }
                j++;
            }
        }
        i++;
        j = 0;
    }
}


// -----------------
// Auxiliary methods

Vec3D* Matrix33D::get_ptr()
{
    return this->data;
}


std::string Matrix33D::toString()
{
    std::stringstream strMatrix;

    strMatrix << "Matrix : " << std::endl;
    for(int i=0; i<2; i++)
    {
        strMatrix << "\t" << this->data[i] << "," << std::endl;
    }
    strMatrix << "\t" << this->data[2] << std::endl;

    return strMatrix.str();
}


// ------------------
// Operators overload


Vec3D Matrix33D::operator[](int i)const
{
    return this->data[i];
}


Vec3D& Matrix33D::operator [](int i)
{
    return this->data[i];
}


Matrix33D Matrix33D::operator*(const Matrix33D& rightHandObj)
{
    int i = 0;
    int j = 0;
    int k = 0;

    Matrix33D answ;

    for(i=0; i<3; i++)
    {
        for(j=0; j<3; j++)
        {
            for(k=0; k<3; k++)
            {
                answ[i][j] += this->data[i][k] * rightHandObj[k][j];
            }
        }
    }

    answ[2][2] = 1;

    return answ;
}


Matrix33D Matrix33D::operator*(const double& scalar)
{
    Matrix33D answ;

    answ[0] = this->data[0] * scalar;
    answ[1] = this->data[1] * scalar;
    answ[2] = this->data[2] * scalar;

    return answ;
}


bool Matrix33D::operator==(const Matrix33D& other)
{
    return ((this->data[0] == other[0]) && (this->data[1] == other[1]) && (this->data[2] == other[2]));
}


// ---------------
// transformations


Matrix33D Matrix33D::identity()
{
    Matrix33D identity;
    identity[0][0] = 1;
    identity[1][1] = 1;

    return identity;
}


Matrix33D Matrix33D::inverse()
{

    Matrix33D answ;
    double det = this->data[0][0] * this->data[1][1] * this->data[2][2]
               + this->data[0][1] * this->data[1][2] * this->data[2][0]
               + this->data[0][2] * this->data[1][0] * this->data[2][1]
               - this->data[0][2] * this->data[1][1] * this->data[2][0]
               - this->data[0][0] * this->data[1][2] * this->data[2][1]
               - this->data[0][1] * this->data[1][0] * this->data[2][2];

    if(det == 0.0)
    {
        std::cerr << "WARNING: det = " << det << " ! Cannot invert matrix" << std::endl;
        return Matrix33D::identity();
    }
    else
    {   
        answ[0][0] = (this->data[1][1]*this->data[2][2] - this->data[1][2]*this->data[2][1])/det;
        answ[1][0] = (this->data[2][0]*this->data[1][2] - this->data[1][0]*this->data[2][2])/det;
        answ[2][0] = (this->data[1][0]*this->data[2][1] - this->data[2][0]*this->data[1][1])/det;

        answ[0][1] = (this->data[2][1]*this->data[0][2] - this->data[0][1]*this->data[2][2])/det;
        answ[1][1] = (this->data[0][0]*this->data[2][2] - this->data[2][0]*this->data[0][2])/det;
        answ[2][1] = (this->data[2][0]*this->data[0][1] - this->data[0][0]*this->data[2][1])/det;

        answ[0][2] = (this->data[0][1]*this->data[1][2] - this->data[1][1]*this->data[0][2])/det;
        answ[1][2] = (this->data[1][0]*this->data[0][2] - this->data[0][0]*this->data[1][2])/det;
        answ[2][2] = (this->data[0][0]*this->data[1][1] - this->data[1][0]*this->data[0][1])/det;
    }

    return answ;
}



Matrix33D Matrix33D::translation(double tx, double ty)
{
    Matrix33D answ = Matrix33D::identity();
    answ[0][2] = tx;
    answ[1][2] = ty;

    return answ;
}


Matrix33D Matrix33D::rotation(double angle)
{
    Matrix33D answ;
    answ[0][0] = std::cos(angle);
    answ[0][1] = -1 * std::sin(angle);
    answ[1][0] = std::sin(angle);
    answ[1][1] = std::cos(angle);

    return answ;
}


Matrix33D Matrix33D::scale(double hx, double hy)
{
    Matrix33D answ;

    answ[0][0] = hx;
    answ[1][1] = hy;

    return answ;
}


Matrix33D& Matrix33D::translate(Matrix33D &translateMatrix)
{
    *this = translateMatrix * *this ;
    return *this;
}


Matrix33D& Matrix33D::translate(double tx, double ty)
{
    Matrix33D translationMatr = Matrix33D::translation(tx, ty);

    return Matrix33D::translate(translationMatr);
}


Matrix33D& Matrix33D::rotate(Matrix33D &rotationMatrix)
{
    *this = rotationMatrix * *this;
    return *this;
}


Matrix33D& Matrix33D::rotate(double angle)
{
    Matrix33D rotationMatr = Matrix33D::rotation(angle);

    return Matrix33D::rotate(rotationMatr);
}


Matrix33D& Matrix33D::addScale(Matrix33D& scaleMatrix)
{
    *this = scaleMatrix * *this;
    return *this;
}


Matrix33D& Matrix33D::addScale(double hx, double hy)
{
    Matrix33D scaleMatr = Matrix33D::scale(hx, hy);

    return Matrix33D::addScale(scaleMatr);
}


Vec3D Matrix33D::operator*(Vec3D& vector)
{
    int i = 0;
    int j = 0;
    Vec3D answ;

    for(i=0; i<3; i++)
    {
        for(j=0; j<3; j++)
        {
            answ[i] += this->data[i][j] * vector[j];
        }
    }

    return answ;
}


Vec2D Matrix33D::operator *(Vec2D& vector)
{
    Vec3D vector3D = {vector[0], vector[1], 1.0};
    Vec2D vector2D;

    vector3D = *this * vector3D;

    vector2D = {vector3D[0], vector3D[1]};

    return vector2D;
}


Vec2D Matrix33D::applyTransformation(double& x, double& y)
{

    Vec2D vector2D = {x, y};

    vector2D = *this * vector2D;

    x = vector2D[0];
    y = vector2D[1];

    vector2D = {x,y};

    return vector2D;
}
