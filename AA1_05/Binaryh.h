#pragma once


//1
void SaveVector(std::vector<int> o, std::string fileName) {


	std::ofstream fsalida(fileName, std::ios::out | std::ios::binary);	for (int i = 0; i < o.size(); i++)
		fsalida.write(reinterpret_cast<char*>(&o[i]), sizeof(int));

	fsalida.close();


}

void RecoverVector(std::vector<int> &o, std::string fileName) {
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

void Save(std::vector<Object> o, std::string fileName) {

	std::ofstream  fsalida(fileName, std::ios::in | std::ios::binary);
	fsalida.write((char*) &o[0].x, sizeof(int));
	


	fsalida.close();

}

void Recover(std::vector<Object> &o, std::string fileName) {

	std::ifstream myFileIn(fileName, std::ios::out | std::ios::binary);
	myFileIn.read((char*) &o[0].x , sizeof(int));
	

	myFileIn.close();

}
