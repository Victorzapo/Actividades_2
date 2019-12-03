#pragma once


//1
void saveVector(std::vector<int> o, std::string fileName) {


	std::ofstream fsalida(fileName, std::ios::out | std::ios::binary);	for (int i = 0; i < o.size(); i++)
		fsalida.write(reinterpret_cast<char*>(&o[i]), sizeof(int));

	fsalida.close();


}

void recoverVector(std::vector<int> &o, std::string fileName) {
	std::ifstream myFileIn(fileName, std::ios::in | std::ios::binary);
	for (int i = 0; i < o.size(); i++)
		myFileIn.read(reinterpret_cast<char*>(&o[i]), sizeof(int));

	myFileIn.close();

}


//2 
struct Object {
	char type;
	int x;
	int y;

	Object(char _type, int _x, int _y) { type = _type; x = _x; y = _y; };
};

void save(std::vector<Object> o, std::string fileName) {

	std::ofstream myFileIn(fileName, std::ios::in | std::ios::binary);
	for (int i = 0; i < o.size(); i++)
		myFileIn.write(reinterpret_cast<char*>(&o[i]), sizeof(Object));

	myFileIn.close();

}

void recover(std::vector<Object> &o, std::string fileName) {

	std::ifstream myFileIn(fileName, std::ios::out | std::ios::binary);
	for (int i = 0; i < o.size(); i++)
		myFileIn.read(reinterpret_cast<char*>(&o[i]), sizeof(Object));

	myFileIn.close();

}
