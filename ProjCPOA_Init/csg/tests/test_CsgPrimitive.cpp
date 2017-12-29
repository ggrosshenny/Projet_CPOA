#include <cassert>
#include "CsgDisk.h"
#include "CsgRegularPolygon.h"


int main()
{
    Matrix33D idMatr = Matrix33D::identity();
    Matrix33D invIdMatr = idMatr.inverse();
    Matrix33D scaleMatr = Matrix33D::identity().scale(10, 10);
    Vec2D point00 = {0,0};

    // ===============
    // Test of CsgDisk

        // Test of contructor
    std::cout << "Test of disk constructor" << std::endl;
    CsgDisk disk1;
    assert(disk1.getRadius() == 1.0);
    assert(disk1.getCenter() == point00);
    assert(disk1.getTransformationMatrix() == idMatr);
    assert(disk1.getTransformationMatrix().inverse() == invIdMatr);
    std::cout << "Test of disk constructor passed" << std::endl;

        // Test of addTransformation
    std::cout << "Test of primitive addTransformation" << std::endl;
    CsgDisk disk2;
    disk2.addTransformation(10, 10, scale);
    disk1.addTransformation(scaleMatr);
    assert(disk2.getTransformationMatrix() == disk1.getTransformationMatrix());
    assert( disk2.getTransformationMatrix() == scaleMatr);
    std::cout << "Test of primitive addTransformation passed" << std::endl;

    // Test of apply local transformation
    std::cout << "Test of disk local transformation" << std::endl;
        // Test of scale
    std::cout << "\tTest of disk scale" << std::endl;
    disk1.applyLocalTransformation();
    assert(disk1.getRadius() == 10.0);
    assert(disk1.getCenter() == point00);
    std::cout << "\tTest of disk scale passed" << std::endl;
        // Test of translation
    std::cout << "\tTest of disk translation" << std::endl;
    Vec2D point22(2,2);
    CsgDisk disk3;
    disk3.addTransformation(2,2, translation);
    disk3.applyLocalTransformation();
    assert(disk3.getRadius() == 1.0);
    assert(disk3.getCenter() == point22);
    std::cout << "\tTest of disk translation passed" << std::endl;
        // Test of rotation
    std::cout << "\tTest of disk rotation" << std::endl;
    CsgDisk disk4;
    disk4.addTransformation(2,2, rotation);
    disk4.applyLocalTransformation();
    assert(disk4.getRadius() == 1.0);
    assert(disk4.getCenter() == point00);
    std::cout << "\tTest of disk rotation passed" << std::endl;

    std::cout << "Test of disk local transformation" << std::endl;

    // Test of rotation
    std::cout << "\tTest of disk intersect" << std::endl;
    assert(disk3.intersect(2.5, 2));
    assert(!disk3.intersect(3.5, 2));
    std::cout << "\tTest of disk intersect passed" << std::endl;


    // =====================
    // regular polygon tests

    // Test of default contructor
    std::cout << "Test of regular polygon default constructor" << std::endl;
    CsgRegularPolygon poly1;
    Vec2D* poly1Vertices = poly1.getPtr();
    assert(poly1.getCenter() == point00);
    assert( ((poly1Vertices[0].x() > 0.49) && (poly1Vertices[0].x() < 0.51))  && ((poly1Vertices[0].y() > -0.99) && (poly1Vertices[0].y() < 0.01)));
    assert( ((poly1Vertices[1].x() < -0.24) && (poly1Vertices[1].x() > -0.26))  && ((poly1Vertices[1].y() > 0.43) && (poly1Vertices[1].y() < 0.44)));
    assert( ((poly1Vertices[2].x() < -0.24) && (poly1Vertices[2].x() > -0.26))  && ((poly1Vertices[2].y() < -0.43) && (poly1Vertices[2].y() > -0.44)));
    std::cout << "Test of regular polygon default constructor passed" << std::endl;

    // Test of contructor with given number of vertices
    std::cout << "Test of regular polygon contructor with given number of vertices" << std::endl;
    CsgRegularPolygon poly2(4);
    Vec2D* poly1Vertices2 = poly2.getPtr();
    assert(poly2.getCenter() == point00);
    assert( ((poly1Vertices2[0].x() > 0.49) && (poly1Vertices2[0].x() < 0.51))  && ((poly1Vertices2[0].y() > -0.99) && (poly1Vertices2[0].y() < 0.01)));
    assert( ((poly1Vertices2[1].x() > -0.99) && (poly1Vertices2[1].x() < 0.01))  && ((poly1Vertices2[1].y() > 0.49) && (poly1Vertices2[1].y() < 0.51)));
    assert( ((poly1Vertices2[2].x() < -0.49) && (poly1Vertices2[2].x() > -0.51))  && ((poly1Vertices2[2].y() > -0.99) && (poly1Vertices2[2].y() < 0.01)));
    assert( ((poly1Vertices2[3].x() > -0.99) && (poly1Vertices2[3].x() < 0.01))  && ((poly1Vertices2[3].y() > -0.51) && (poly1Vertices2[3].y() < -0.49)));
    std::cout << "Test of regular polygon contructor with given number of vertices passed" << std::endl;

    // Test of applyLocalTransformation
    std::cout << "Test of regular polygon applyLocalTransformation" << std::endl;

    std::cout << "\tTest of the regular polygon translation" << std::endl;
    poly1.addTransformation(2, 2, translation);
    poly1.applyLocalTransformation();
    poly1Vertices = poly1.getPtr();
    assert(poly1.getCenter() == point00);
    assert( ((poly1Vertices[0].x() > 2.49) && (poly1Vertices[0].x() < 2.51))  && ((poly1Vertices[0].y() > 1.99) && (poly1Vertices[0].y() < 2.01)));
    assert( ((poly1Vertices[1].x() > 1.74) && (poly1Vertices[1].x() < 1.76))  && ((poly1Vertices[1].y() > 2.43) && (poly1Vertices[1].y() < 2.44)));
    assert( ((poly1Vertices[2].x() > 1.74) && (poly1Vertices[2].x() < 1.76))  && ((poly1Vertices[2].y() > 1.55) && (poly1Vertices[2].y() < 1.57)));
    std::cout << "\tTest of the regular polygon translation passed" << std::endl;

    std::cout << "\tTest of the regular polygon scale" << std::endl;
    poly1 = CsgRegularPolygon();
    poly1.addTransformation(2, 2, scale);
    poly1.applyLocalTransformation();
    poly1Vertices = poly1.getPtr();
    assert(poly1.getCenter() == point00);
    assert( ((poly1Vertices[0].x() > 0.99) && (poly1Vertices[0].x() < 1.01))  && ((poly1Vertices[0].y() > -0.99) && (poly1Vertices[0].y() < 0.01)));
    assert( ((poly1Vertices[1].x() > -0.51) && (poly1Vertices[1].x() < -0.49))  && ((poly1Vertices[1].y() > 0.86) && (poly1Vertices[1].y() < 0.87)));
    assert( ((poly1Vertices[2].x() > -0.51) && (poly1Vertices[2].x() < -0.49))  && ((poly1Vertices[2].y() > -0.87) && (poly1Vertices[2].y() < -0.86)));
    std::cout << "\tTest of the regular polygon scale passed" << std::endl;

    std::cout << "\tTest of the regular polygon rotation" << std::endl;
    poly1 = CsgRegularPolygon();
    poly1.addTransformation(90, 2, rotation);
    poly1.applyLocalTransformation();
    poly1Vertices = poly1.getPtr();
    assert(poly1.getCenter() == point00);
    assert( ((poly1Vertices[0].x() > -0.23) && (poly1Vertices[0].x() < -0.22))  && ((poly1Vertices[0].y() > 0.44) && (poly1Vertices[0].y() < 0.45)));
    assert( ((poly1Vertices[1].x() > -0.28) && (poly1Vertices[1].x() < -0.27))  && ((poly1Vertices[1].y() > -0.42) && (poly1Vertices[1].y() < -0.41)));
    assert( ((poly1Vertices[2].x() > 0.49) && (poly1Vertices[2].x() < 0.5))  && ((poly1Vertices[2].y() > -0.03) && (poly1Vertices[2].y() < -0.02)));
    std::cout << "\tTest of the regular polygon rotation passed" << std::endl;

    std::cout << "Test of regular polygon applyLocalTransformation passed" << std::endl;

    // Test of intersect
    std::cout << "Test of the regular polygon intersect" << std::endl;
    CsgRegularPolygon poly3;
    assert(poly3.intersect(0.4, 0.0));
    assert(!poly3.intersect(-0.3, 0.0));
    std::cout << "Test of the regular polygon intersect passed" << std::endl;

    return 0;
}
