#include <iostream>
#include "ProjectVectors.hpp"

int main()
{

    // Vec2I

    Vec2I v2i1 = {1, 2, 3};
    Vec2I v2i2 = {4, 5, 6};
    Vec2I v2i3 = {4};
    Vec2I v2i4 = {4, 5, 6, 7};
    int scalar2i = 2;
    int dot2i = v2i1 * v2i2;
    int cross2i = v2i1.cross(v2i2);
    Vec2I prodScal2i = scalar2i * v2i1;
    Vec2I prodScal2i2 = v2i2 * scalar2i;

    std::cout << "=====================================" << std::endl;
    std::cout << " Test with Vec2I" << std::endl;
    std::cout << "v1 : " << v2i1 << std::endl;
    std::cout << "v2 : " << v2i2 << std::endl;
    std::cout << "v3 : " << v2i3 << std::endl;
    std::cout << "v4 : " << v2i4 << std::endl;
    std::cout << "2.0 * v1 = " << prodScal2i << std::endl;
    std::cout << "v2 * 2.0 = " << prodScal2i2 << std::endl;
    std::cout << "v1 * v2 = " << dot2i << std::endl;
    std::cout << "v1 ^ v2 = " << cross2i << std::endl;


    // Vec2D

    Vec2D v2d1 = {1.0, 2.0};
    Vec2D v2d2 = {4.0, 5.0};
    Vec2D v2d3 = {4.0};
    Vec2D v2d4 = {4.0, 5.0, 6.0, 7.0};
    double scalar2d = 2;
    double dot2d = v2d1 * v2d2;
    double cross2d = v2d1.cross(v2d2);
    Vec2D prodScal2d = scalar2d * v2d1;
    Vec2D prodScal2d2 = v2d2 * scalar2d;

    std::cout << "=====================================" << std::endl;
    std::cout << " Test with Vec2D" << std::endl;
    std::cout << "v1 : " << v2d1 << std::endl;
    std::cout << "v2 : " << v2d2 << std::endl;
    std::cout << "v3 : " << v2d3 << std::endl;
    std::cout << "v4 : " << v2d4 << std::endl;
    std::cout << "2.0 * v1 = " << prodScal2d << std::endl;
    std::cout << "v2 * 2.0 = " << prodScal2d2 << std::endl;
    std::cout << "v1 * v2 = " << dot2d << std::endl;
    std::cout << "v1 ^ v2 = " << cross2d << std::endl;


    // Vec3I

    Vec3I v3i1 = {1, 2, 3};
    Vec3I v3i2 = {4, 5, 6};
    Vec3I v3i3 = {4};
    Vec3I v3i4 = {4,5,6,7};
    int scalar3i = 2;
    int dot3i = v3i1 * v3i2;
    Vec3I cross3i = v3i1.cross(v3i2);
    Vec3I prodScal3i = scalar3i * v3i1;
    Vec3I prodScal3i2 = v3i2 * scalar3i;

    std::cout << "=====================================" << std::endl;
    std::cout << " Test with Vec3I" << std::endl;
    std::cout << "v1 : " << v3i1 << std::endl;
    std::cout << "v2 : " << v3i2 << std::endl;
    std::cout << "v3 : " << v3i3 << std::endl;
    std::cout << "v4 : " << v3i4 << std::endl;
    std::cout << "2.0 * v1 = " << prodScal3i << std::endl;
    std::cout << "v2 * 2.0 = " << prodScal3i2 << std::endl;
    std::cout << "v1 * v2 = " << dot3i << std::endl;
    std::cout << "v1 ^ v2 = " << cross3i << std::endl;


    // Vec3D

    Vec3D v1 = {1.0, 2.0, 3.0};
    Vec3D v2 = {4.0, 5.0, 6.0};
    Vec3D v3 = {4.0};
    Vec3D v4 = {4.0,5.0,6.0,7.0};
    double scalar = 2.0;
    double dot = v1 * v2;
    Vec3D cross = v1.cross(v2);
    Vec3D prodScal = scalar * v1;
    Vec3D prodScal2 = v2 * scalar;

    std::cout << "=====================================" << std::endl;
    std::cout << " Test with Vec3D" << std::endl;
    std::cout << "v1 : " << v1 << std::endl;
    std::cout << "v2 : " << v2 << std::endl;
    std::cout << "v3 : " << v3 << std::endl;
    std::cout << "v4 : " << v4 << std::endl;
    std::cout << "2.0 * v1 = " << prodScal << std::endl;
    std::cout << "v2 * 2.0 = " << prodScal2 << std::endl;
    std::cout << "v1 * v2 = " << dot << std::endl;
    std::cout << "v1 ^ v2 = " << cross << std::endl;


    // Vec4I

    Vec4I v4i1 = {1, 2, 3, 4};
    Vec4I v4i2 = {4, 5, 6, 7};
    Vec4I v4i3 = {4};
    Vec4I v4i4 = {4,5,6,7,8};
    int scalar4i = 2;
    int dot4i = v4i1 * v4i2;
    Vec4I prodScal4i = scalar4i * v4i1;
    Vec4I prodScal4i2 = v4i2 * scalar4i;

    std::cout << "=====================================" << std::endl;
    std::cout << " Test with Vec4I" << std::endl;
    std::cout << "v1 : " << v4i1 << std::endl;
    std::cout << "v2 : " << v4i2 << std::endl;
    std::cout << "v3 : " << v4i3 << std::endl;
    std::cout << "v4 : " << v4i4 << std::endl;
    std::cout << "2.0 * v1 = " << prodScal4i << std::endl;
    std::cout << "v2 * 2.0 = " << prodScal4i2 << std::endl;
    std::cout << "v1 * v2 = " << dot4i << std::endl;


    // Vec4I

    Vec4D v4d1 = {1.0, 2.0, 3.0, 4.0};
    Vec4D v4d2 = {4.0, 5.0, 6.0, 7.0};
    Vec4D v4d3 = {4.0};
    Vec4D v4d4 = {4.0,5.0,6.0,7.0,8.0};
    double scalar4d = 2.0;
    double dot4d = v4d1 * v4d2;
    Vec4D prodScal4d = scalar4d * v4d1;
    Vec4D prodScal4d2 = v4d2 * scalar4d;

    std::cout << "=====================================" << std::endl;
    std::cout << " Test with Vec4D" << std::endl;
    std::cout << "v1 : " << v4d1 << std::endl;
    std::cout << "v2 : " << v4d2 << std::endl;
    std::cout << "v3 : " << v4d3 << std::endl;
    std::cout << "v4 : " << v4d4 << std::endl;
    std::cout << "2.0 * v1 = " << prodScal4d << std::endl;
    std::cout << "v2 * 2.0 = " << prodScal4d2 << std::endl;
    std::cout << "v1 * v2 = " << dot4d << std::endl;

	return 0;
}


