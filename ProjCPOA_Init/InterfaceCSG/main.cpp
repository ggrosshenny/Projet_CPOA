#include <QApplication>
#include "mainwindow.h"
#include "Array.hpp"
#include "ProjectVectors.hpp"
#include <iostream>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	MainWindow w;
	w.show();

    Array<int, 3>test;
    test[0]=0;
    test[1]=1;
    test[2]=2;
    Array<int, 3>test2;
    test2[0]=1;
    test2[1]=2;
    test2[2]=3;
    Array<int, 3>test3 = {4, 5};
    std::cout << "test3 : " << test3.toString() << std::endl;
    bool t1 = test == test;
    bool t2 = test == test2;
    bool t3 = test != test2;
    std::cout << "Valeur de test[0] : " << test[0] << std::endl;
    std::cout << "test == test ? : " << t1 << std::endl;
    std::cout << "test == test2 ? : " << t2 << std::endl;
    std::cout << "test != test2 ? : " << t3 << std::endl;
    std::cout << "test : " << test.toString() << " et test2 : " << test2.toString() << std::endl;
    test = test2;
    std::cout << "test : " << test.toString() << " et test2 : " << test2.toString() << std::endl;


	
	return a.exec();
}
