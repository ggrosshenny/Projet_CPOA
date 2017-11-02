#include <iostream>
#include "Matrix33d.h"


int main()
{

    Matrix33D m1 = Matrix33D::identity();

    std::cout << m1 << std::endl;
	std::cout << "translate(3.5f,2.4f) "<<  std::endl;
    m1.translate(3.5f,2.4f);
	std::cout << m1 <<  std::endl;

    double x = 0.0;
    double y = 0.0;
	m1.applyTransformation(x,y);
	std::cout << "0,0 => "<< x << "," << y << std::endl;

    m1.rotate(0.4);

    Matrix33D m2 = m1.inverse();

    Matrix33D m3 = m1 * m2;

    std::cout << m1 << std::endl;
    std::cout <<"*"<< std::endl;
    std::cout <<m2<< "=" << std::endl;
    std::cout << m3 << std::endl;


	return 0;
}
