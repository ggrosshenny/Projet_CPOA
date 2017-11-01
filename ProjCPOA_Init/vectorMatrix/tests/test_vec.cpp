#include <iostream>
#include "ProjectVectors.hpp"

int main()
{
    Vec3D v1 = {1.0, 2.0, 3.0};
    Vec3D v2 = {4.0, 5.0, 6.0};
    double scalar = 2.0;
    double dot = v1 * v2;
    Vec3D cross = v1.cross(v2);
    Vec3D prodScal = scalar * v1;
    Vec3D prodScal2 = v2 * scalar;

    std::cout << "v1 : " << v1 << std::endl;
    std::cout << "v2 : " << v2 << std::endl;
    std::cout << "2.0 * v1 = " << prodScal << std::endl;
    std::cout << "v2 * 2.0 = " << prodScal2 << std::endl;
    std::cout << "v1 * v2 = " << dot << std::endl;
    std::cout << "v1 ^ v2 = " << cross << std::endl;



	return 0;
}


