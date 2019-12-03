#include <iostream>
#include <fstream>
#include <vector>
#include "Binaryh.h"




int main() {

	//1
	std::cout << "Ejercicio 1" << std::endl;
	//Define
	std::vector<int> a({1,2,3,4,5,6,7,8,9,10});

	//Save vector
	saveVector(a, "TestSaveVector.bin");

	//Mod vector
	for (int i = 0; i < a.size(); i++) { a[i] = a[i] + 10; }

	//Recover
	recoverVector(a, "TestSaveVector.bin");

	//Print
	for (int i = 0; i < a.size(); i++) { std::cout << a[i] << std::endl; }	
	//2
	std::cout << "Ejercicio 2" << std::endl;
	//Define
	Object obj1('a', 5 ,10);
	Object obj2('b', 7 , 20);
	Object obj3('c', 20, 15);

	std::vector<Object> objcts({obj1, obj2, obj3});
	
	//Save objects
	save(objcts, "ObjectSave");

	//Mod objects
	for (int i = 0; i < objcts.size(); i++)
		objcts[i].x++;

	//Recover
	recover(objcts, "ObjectSave");


	//Print
	for (int i = 0; i < objcts.size(); i++) {
		std::cout << "Object " << i << std::endl;
		std::cout << objcts[i].type << std::endl;
		std::cout << objcts[i].x << std::endl;
		std::cout << objcts[i].y << std::endl;
		
	}

	
	
	
	return 0;
}