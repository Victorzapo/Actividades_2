#include <iostream>
#include <string>
#include <fstream>
#include <vector>


//1
void saveVector(std::vector<int> o, std::string fileName) {
	

	std::ofstream fsalida(fileName, std::ios::out | std::ios::binary);	for (int i = 0; i < o.size(); i++)
		fsalida.write(reinterpret_cast<char*>(&o[i]), sizeof(o[i]));
	fsalida.close();


}

void recoverVector(std::vector<int> &o, std::string fileName) {
	std::ifstream myFileIn(fileName, std::ios::in | std::ios::binary);
	for(int i = 0; i < o.size(); i++)
		myFileIn.read(reinterpret_cast<char*>(&o[i]), sizeof(o[i]));

	myFileIn.close();

}


//2 
struct Object {
	char type;
	int x;
	int y;

	Object(char _type, int _x, int _y) { type = _type; x = _x; y = _y; };
};

void save(std::vector<Object> o , std::string fileName){

	std::ofstream myFileIn(fileName, std::ios::in | std::ios::binary);
	for (int i = 0; i < o.size(); i++) {
		myFileIn.write(reinterpret_cast<char*>(&o[i].type), sizeof(Object));
		myFileIn.write(reinterpret_cast<char*>(&o[i].x), sizeof(Object));
		myFileIn.write(reinterpret_cast<char*>(&o[i].y), sizeof(Object));
		

	}
	myFileIn.close();

}

void recover(std::vector<Object> &o, std::string fileName) {

	std::ifstream myFileIn(fileName, std::ios::out | std::ios::binary);
	for (int i = 0; i < o.size(); i++) {
		myFileIn.read(reinterpret_cast<char*>(&o[i].type), sizeof(Object));
		myFileIn.read(reinterpret_cast<char*>(&o[i].x), sizeof(Object));
		myFileIn.read(reinterpret_cast<char*>(&o[i].y), sizeof(Object));
	}
	myFileIn.close();

}




int main() {


	//1
	/* 
	//Define
	std::vector<int> a({1,2,3,4,5,6,7,8,9,10});

	//Save vector
	saveVector(a, "TestSaveVector.bin");

	//Mod vector
	for (int i = 0; i < a.size(); i++) { a[i] = 0; }

	//Recover
	recoverVector(a, "TestSaveVector.bin");

	//Print
	for (int i = 0; i < a.size(); i++) { std::cout << a[i] << std::endl; }		*/


	//2
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
		std::cout << objcts[i].type << std::endl;
		std::cout << objcts[i].x << std::endl;
		std::cout << objcts[i].y << std::endl;
	}
	
	return 0;
}